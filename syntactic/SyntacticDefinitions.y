%parse-param {void* symbolsTable}

%{
#include <math.h>
#include "lex.yy.h"
#include "Errors.h"
#include "SymbolsTable.h"
#include "NativeFunctions.h"

int readingFile = 0;
double *stack = NULL;
int stackSize = 0;

void ensureStackCapacity(int capacity);
%}

%union {
    double value;
    char *string;
    struct {
        int argCount;
        double *argValues;
    } arguments;
}

%token <string> IDENTIFIER
%token <string> STRING_LIT
%token <value> INTEGER_LIT
%token <value> FLOATING_LIT
%token <string> KEYWORD
%token <string> LOAD
%token END_OF_FILE;

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
                | input line                    { if(!readingFile) prompt(); }
;

line:             lineEnd
                | error lineEnd
                | statement
                | expression lineEnd            { printf("%.10g\n", $1); }
;

lineEnd:        '\n'
                | END_OF_FILE                   { yy_switch_to_buffer(yy_create_buffer(stdin, YY_BUF_SIZE)); readingFile = 0;}

statement:        expression ';' lineEnd
                | KEYWORD lineEnd               { callFunction(symbolsTable, $1, NULL); free($1); }
                | LOAD STRING_LIT lineEnd       { readingFile = _load($2); free($1); free($2); }
;

expression:       INTEGER_LIT                   { $$ = $1; }
                | FLOATING_LIT                  { $$ = $1; }
                | expression '+' expression     { $$ = $1 + $3; }
                | expression '-' expression     { $$ = $1 - $3; }
                | expression '*' expression     { $$ = $1 * $3; }
                | expression '/' expression     { $$ = $1 / $3; }
                | '-' expression %prec NEGATIVE { $$ = -$2; }
                | expression '^' expression     { $$ = pow($1, $3); }
                | '(' expression ')'            { $$ = $2; }
                | IDENTIFIER                    {
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
                | IDENTIFIER '=' expression     {
                                                    int assignability = getAssignability(symbolsTable, $1);

                                                    if (assignability == ASSIGNABILITY_ASSIGNABLE) {
                                                        assignVariable(symbolsTable, $1, $3);
                                                        free($1);
                                                        $$ = $3;
                                                    } else {
                                                        errorAssigningValue(assignability, $1);
                                                        free($1);
                                                        YYERROR;
                                                    }
                                                }
                | IDENTIFIER arguments          {
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

arguments:        '(' ')'                       { $$.argCount = 0; }
                | '(' argumentList ')'          {
                                                    $$.argValues = (double*) malloc($2.argCount * sizeof(double));
                                                    memcpy($$.argValues, stack, $2.argCount * sizeof(double));
                                                    $$.argCount = $2.argCount;
                                                }
;

argumentList:     argumentList ',' expression   { ensureStackCapacity($1.argCount + 1); stack[$1.argCount] = $3; $$.argCount = $1.argCount + 1; }
                | expression                    { ensureStackCapacity(1); stack[0] = $1; $$.argCount = 1; }
;

%%

void ensureStackCapacity(int capacity) {
    if(capacity > stackSize) {
        stackSize += STACK_SIZE_STEP;
        stack = realloc(stack, stackSize * sizeof(double));
    }
}