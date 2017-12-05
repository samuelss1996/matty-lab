%{
#include <string.h>
#include "Definitions.h"
#include "SyntacticDefinitions.tab.h"

int charCount(char* string, char character);
void saveIdentifier();

int column = 0;
%}

IdLetter				[a-zA-Z_]
Blank					[ \t\r]
NewLine					\n

HexDigit				[0-9a-fA-F]

DecimalLiteral			[1-9]([0-9])*
OctalLiteral			0([0-7])*
HexadecimalLiteral		0(x|X){HexDigit}+

Decimals				[0-9]+
Exponent				(e|E)(\+|-)?{Decimals}
FloatLit				({Decimals}\.{Decimals}?{Exponent}?)|({Decimals}{Exponent})|(\.{Decimals}{Exponent}?)

%%

"who"|"help"                                            {column += yyleng; saveIdentifier(); return KEYWORD;}
"load"                                                  {column += yyleng; saveIdentifier(); return LOAD;}

{IdLetter}({IdLetter}|[0-9])*							{column += yyleng; saveIdentifier(); return TOKEN_IDENTIFIER;}
{NewLine} 												{column = 0; yylineno++; return '\n';}
{Blank}+												{column += yyleng;}

{DecimalLiteral}|{OctalLiteral}|{HexadecimalLiteral}	{column += yyleng; yylval.value = atof(yytext); return TOKEN_INTEGER_LITERAL;}
{FloatLit}												{column += yyleng; yylval.value = atof(yytext); return TOKEN_FLOATING_POINT_LITERAL;}

"+"                                                     {column += yyleng; return '+';}
"-"                                                     {column += yyleng; return '-';}
"*"                                                     {column += yyleng; return '*';}
"/"                                                     {column += yyleng; return '/';}
"^"                                                     {column += yyleng; return '^';}
"="                                                     {column += yyleng; return '=';}
","                                                     {column += yyleng; return ',';}
";"                                                     {column += yyleng; return ';';}
"("                                                     {column += yyleng; return '(';}
")"                                                     {column += yyleng; return ')';}

<<EOF>>													{column += yyleng; return END_OF_FILE;}

%%

int charCount(char* string, char character) {
	int result = 0;
	char *pointer;

	for(pointer = string; *pointer != '\0'; pointer++) {
		if(*pointer == character) {
			result++;
		}
	}

	return result;
}

void saveIdentifier() {
    yylval.identifier = (char*) malloc((yyleng + 1) * sizeof(char));
    strcpy(yylval.identifier, yytext);
}