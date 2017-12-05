%parse-param {void* symbolsTable}

%{
#include <math.h>
#include "lex.yy.h"
#include "Errors.h"
#include "SymbolsTable.h"
%}

%union {
    double value;
    char *identifier;
    struct {
        int argCount;
        double argValues[9];
    } arguments;
}

%token <identifier> TOKEN_IDENTIFIER
%token <value> TOKEN_INTEGER_LITERAL
%token <value> TOKEN_FLOATING_POINT_LITERAL
%token <identifier> KEYWORD

%type <value> expression
%type <arguments> arguments
%type <arguments> argumentList

%right '='
%left '+' '-'
%left '*' '/'
%left NEGATIVE
%right '^'
%%
input:            /* empty */
                | input line                            { printf("> "); }
;

line:             '\n'
                | error '\n'
                | statement '\n'
                | expression '\n'                       { printf("%f\n", $1); }
;

statement:        expression ';'
                | KEYWORD '(' ')'                       { callFunction(symbolsTable, $1, NULL); free($1); }
;

expression:       TOKEN_INTEGER_LITERAL                 { $$ = $1; }
                | expression '+' expression             { $$ = $1 + $3; }
                | expression '-' expression             { $$ = $1 - $3; }
                | expression '*' expression             { $$ = $1 * $3; }
                | expression '/' expression             { $$ = $1 / $3; }
                | '-' expression %prec NEGATIVE         { $$ = -$2; }
                | expression '^' expression             { $$ = pow($1, $3); }
                | '(' expression ')'                    { $$ = $2; }
                | TOKEN_IDENTIFIER                      {
                                                            int readability = getReadability(symbolsTable, $1);

                                                            if (readability == READABILITY_VARIABLE || readability == READABILITY_CONSTANT) {
                                                                $$ = getVariableValue(symbolsTable, $1);
                                                                free($1);
                                                            } else {
                                                                errorDisplayingSymbolValue(readability, $1);
                                                                free($1);
                                                                YYERROR;
                                                            }
                                                        }
                | TOKEN_IDENTIFIER '=' expression       { $$ = $3; assignVariable(symbolsTable, $1, $3); }
                | TOKEN_IDENTIFIER arguments            {
                                                            int callability = getCallability(symbolsTable, $1, $2.argCount);

                                                            if (callability == CALLABILITY_CALLABLE) {
                                                                $$ = callFunction(symbolsTable, $1, $2.argValues);
                                                                free($1);
                                                            } else {
                                                                errorCallingFunction(callability, $1, $2.argCount);
                                                                free($1);
                                                                YYERROR;
                                                            }
                                                        }
;

arguments:        '(' ')'                               { $$.argCount = 0; }
                | '(' argumentList ')'                  { memcpy($$.argValues, $2.argValues, 9 * sizeof(double)); $$.argCount = $2.argCount; }
;

argumentList:     argumentList ',' expression           { $$.argValues[$1.argCount] = $3; $$.argCount = $1.argCount + 1; }
                | expression                            { $$.argValues[0] = $1; $$.argCount = 1; }
;

%%