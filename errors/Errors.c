#include <stdio.h>

void yyerror(void* symbolsTable, char *string) {
    printf("%s\n", string);
}

// TODO
void errorCallingFunction(int errorCode, char* functionName, int suppliedArgsCount) {
    printf("Error %d\n", errorCode);
}

// TODO
void errorDisplayingSymbolValue(int errorCode, char* functionName) {
    printf("Error %d\n", errorCode);
}