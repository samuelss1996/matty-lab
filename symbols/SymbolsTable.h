#include <Definitions.h>
#include <util/LinkedList.h>

typedef void* SymbolsTable;

void createSymbolsTable(SymbolsTable* symbolsTable);
void addSymbol(SymbolsTable* symbolsTable, char *token, SymbolsTableValue* value);
SymbolsTableValue findSymbol(SymbolsTable* symbolsTable, char *token);
SymbolsTableValue findOrAdd(SymbolsTable* symbolsTable, char* token, SymbolsTableValue* value);
void assignVariable(SymbolsTable* symbolsTable, char* variableName, double value);
void destroySymbolsTable(SymbolsTable* symbolsTable);