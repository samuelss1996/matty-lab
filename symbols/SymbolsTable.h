#include <LinkedList.h>
#include <Definitions.h>

typedef void* SymbolsTable;

void createSymbolsTable(SymbolsTable* symbolsTable);
void addSymbol(SymbolsTable* symbolsTable, char *token, SymbolsTableValue* value);
SymbolsTableValue findSymbol(SymbolsTable* symbolsTable, char *token);
SymbolsTableValue findOrAdd(SymbolsTable* symbolsTable, char* token, SymbolsTableValue* value);

void assignVariable(SymbolsTable* symbolsTable, char* variableName, double value);
double getVariableValue(SymbolsTable* symbolsTable, char* variableName);
int getReadability(SymbolsTable* symbolsTable, char *name);
int getAssignability(SymbolsTable* symbolsTable, char *name);
int getCallability(SymbolsTable* symbolsTable, char *functionName, int suppliedArgsCount);
double callFunction(SymbolsTable* symbolsTable, char* functionName, double *arguments);
char** getAllSymbols(SymbolsTable* symbolsTable);
void destroySymbolsTable(SymbolsTable* symbolsTable);