%{
#include "lex.yy.h"
#include "Errors.h"
%}

%token TOKEN_IDENTIFIER
%token TOKEN_INTEGER_LITERAL
%token TOKEN_FLOATING_POINT_LITERAL
%%
input: /* empty */ | input TOKEN_INTEGER_LITERAL ;

%%