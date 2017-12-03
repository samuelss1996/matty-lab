#include <Definitions.h>
#include <util/LinkedList.h>

typedef void* SymbolsTable;

void createSymbolsTable(SymbolsTable* symbolsTable);
void addSymbol(SymbolsTable* symbolsTable, char *token, SymbolsTableValue* value);
SymbolsTableValue findSymbol(SymbolsTable* symbolsTable, char *token);
SymbolsTableValue findOrAdd(SymbolsTable* symbolsTable, char* token, SymbolsTableValue* value);

void assignVariable(SymbolsTable* symbolsTable, char* variableName, double value);
int existsVariable(SymbolsTable* symbolsTable, char *name);
double getVariableValue(SymbolsTable* symbolsTable, char* variableName);
int existsFunction(SymbolsTable* symbolsTable, char *functionName);
double callFunction(SymbolsTable* symbolsTable, char* functionName, double argument);
void destroySymbolsTable(SymbolsTable* symbolsTable);