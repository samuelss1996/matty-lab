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
}

%token <identifier> TOKEN_IDENTIFIER
%token <value> TOKEN_INTEGER_LITERAL
%token <value> TOKEN_FLOATING_POINT_LITERAL

%type <value> expression

%right '='
%left '+' '-'
%left '*' '/'
%left NEGATIVE
%right '^'
%%
input:            /* empty */
                | input line
;

line:             '\n'
                | error '\n'
                | expression '\n'                       { printf("%f\n", $1); }
;

expression:       TOKEN_INTEGER_LITERAL                 { $$ = $1; }
                | TOKEN_IDENTIFIER                      { if(existsVariable(symbolsTable, $1)) { $$ = getVariableValue(symbolsTable, $1); } else { YYERROR; free($1); } }
                | TOKEN_IDENTIFIER '=' expression       { $$ = $3; assignVariable(symbolsTable, $1, $3); }
                | TOKEN_IDENTIFIER '(' expression ')'   { if(existsFunction(symbolsTable, $1)) { $$ = callFunction(symbolsTable, $1, $3); } else { YYERROR; free($1); } }
                | expression '+' expression             { $$ = $1 + $3; }
                | expression '-' expression             { $$ = $1 - $3; }
                | expression '*' expression             { $$ = $1 * $3; }
                | expression '/' expression             { $$ = $1 / $3; }
                | '-' expression %prec NEGATIVE         { $$ = -$2; }
                | expression '^' expression             { $$ = pow($1, $3); }
                | '(' expression ')'                    { $$ = $2; }
;

%%