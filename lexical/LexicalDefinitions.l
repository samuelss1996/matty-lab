%{
#include "SyntacticDefinitions.tab.h"

int charCount(char* string, char character);

int column = 0;
%}

IdLetter				[a-zA-Z_]
Blank					[ \t\r]
NewLine					\n

SingleLineCommentStart	\/\/
MultiLineCommentStart 	\/\*
MultiLineCommentEnd		\*\/

HexDigit				[0-9a-fA-F]

DecimalLiteral			[1-9]([0-9])*
OctalLiteral			0([0-7])*
HexadecimalLiteral		0(x|X){HexDigit}+

Decimals				[0-9]+
Exponent				(e|E)(\+|-)?{Decimals}
FloatLit				({Decimals}\.{Decimals}?{Exponent}?)|({Decimals}{Exponent})|(\.{Decimals}{Exponent}?)

%%

{IdLetter}({IdLetter}|[0-9])*							{column += yyleng; return TOKEN_IDENTIFIER;}
{NewLine} 												{column = 0; yylineno++; return '\n';}
{Blank}+												{column += yyleng;}

{SingleLineCommentStart}.*								{column += yyleng;}
"/*"([^*\n]|(\*+[^*/\n]))*\*+\/							{column += yyleng;}
{NewLine}*("/*"([^*]|(\*+[^*/]))*\*+\/){NewLine}*		{column = 0; yylineno += charCount(yytext, '\n'); return '\n';}

{DecimalLiteral}|{OctalLiteral}|{HexadecimalLiteral}	{column += yyleng; return TOKEN_INTEGER_LITERAL;}
{FloatLit}												{column += yyleng; return TOKEN_FLOATING_POINT_LITERAL;}

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

<<EOF>>													{column += yyleng; return EOF;}

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