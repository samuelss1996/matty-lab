#include <LinkedList.h>

typedef void* SymbolsTable;

void createSymbolsTable(SymbolsTable* symbolsTable);
void addSymbol(SymbolsTable* symbolsTable, char *token, SymbolsTableValue* value);
SymbolsTableValue findSymbol(SymbolsTable* symbolsTable, char *token);
SymbolsTableValue findOrAdd(SymbolsTable* symbolsTable, char* token, SymbolsTableValue* value);

void assignVariable(SymbolsTable* symbolsTable, char* variableName, double value);
int existsVariable(SymbolsTable* symbolsTable, char *name);
double getVariableValue(SymbolsTable* symbolsTable, char* variableName);
int getCallability(SymbolsTable* symbolsTable, char *functionName, int suppliedArgsCount);
double callFunction(SymbolsTable* symbolsTable, char* functionName, double *arguments);
void destroySymbolsTable(SymbolsTable* symbolsTable);