%{
#include <string.h>
#include "Definitions.h"
#include "SyntacticDefinitions.tab.h"

int charCount(char* string, char character);
void saveIdentifier();
void saveString();

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

String                  \"[^\"\n]*\"

%%

"who"|"clear"|"help"                                    {column += yyleng; saveIdentifier(); return KEYWORD;}
"load"                                                  {column += yyleng; saveIdentifier(); return LOAD;}

{IdLetter}({IdLetter}|[0-9])*							{column += yyleng; saveIdentifier(); return IDENTIFIER;}
{NewLine} 												{column = 0; yylineno++; return '\n';}
{Blank}+												{column += yyleng;}

{DecimalLiteral}|{OctalLiteral}|{HexadecimalLiteral}	{column += yyleng; yylval.value = atof(yytext); return INTEGER_LIT;}
{FloatLit}												{column += yyleng; yylval.value = atof(yytext); return FLOATING_LIT;}
{String}                                                {column += yyleng; saveString(); return STRING_LIT;}

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

.                                                       {column += yyleng; return yytext[0];}

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
    yylval.string = (char*) malloc((yyleng + 1) * sizeof(char));
    strcpy(yylval.string, yytext);
}

void saveString() {
    yylval.string = (char*) malloc((yyleng -1) * sizeof(char));
    memcpy(yylval.string, yytext + 1, (yyleng - 2) * sizeof(char));
}