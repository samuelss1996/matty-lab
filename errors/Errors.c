#include <stdio.h>

void yyerror(void* symbolsTable, char *string) {
    printf("%s\n", string);
}