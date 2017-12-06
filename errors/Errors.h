void yyerror(void* symbolsTable, char *string);
void errorAssigningValue(int errorCode, char* symbolName);
void errorCallingFunction(int errorCode, char* functionName, int suppliedArgsCount);
void errorDisplayingSymbolValue(int errorCode, char* functionName);
void errorLoadingFile(char *filename);