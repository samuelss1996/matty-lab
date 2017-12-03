#include <SyntacticDefinitions.tab.h>
#include <SymbolsTable.h>
#include <stdlib.h>

// TODO include command to print the memory status
// TODO check scientific notation
int main() {
    SymbolsTable symbolsTable;

    createSymbolsTable(&symbolsTable);
    yyparse(&symbolsTable);

    return EXIT_SUCCESS;
}