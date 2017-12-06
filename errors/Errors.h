#include <SymbolsTable.h>

void yyerror(void* symbolsTable, const char *string);
void syntacticError(int handledError);
void errorAssigningValue(int errorCode, char* symbolName);
void errorCallingFunction(int errorCode, SymbolsTable* symbolsTable,  char* functionName, int suppliedArgsCount);
void errorDisplayingSymbolValue(int errorCode, char* symbolName);
void errorLoadingFile(char *filename);