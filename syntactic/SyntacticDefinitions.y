%{
#include <math.h>
#include "lex.yy.h"
#include "Errors.h"
%}

%union {
    double value;
}

%token <value> TOKEN_IDENTIFIER
%token <value> TOKEN_INTEGER_LITERAL
%token <value> TOKEN_FLOATING_POINT_LITERAL

%type <value> expression

%left '+' '-'
%left '*' '/'
%left NEGATIVE
%right '^'
%%
input:          /* empty */
                | input line
;

line:           '\n'
                | expression '\n'              { printf("%f\n", $1); }
;

expression:     TOKEN_INTEGER_LITERAL           { $$ = $1; }
                | expression '+' expression     { $$ = $1 + $3; }
                | expression '-' expression     { $$ = $1 - $3; }
                | expression '*' expression     { $$ = $1 * $3; }
                | expression '/' expression     { $$ = $1 / $3; }
                | '-' expression %prec NEGATIVE { $$ = -$2; }
                | expression '^' expression     { $$ = pow($1, $3); }
                | '(' expression ')'            { $$ = $2; }
;

%%