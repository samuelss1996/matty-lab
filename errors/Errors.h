void yyerror(void* symbolsTable, char *string);
void errorCallingFunction(int errorCode, char* functionName, int suppliedArgsCount);
void errorDisplayingSymbolValue(int errorCode, char* functionName);
void errorLoadingFile(char *filename);