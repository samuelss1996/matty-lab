#include <SyntacticDefinitions.tab.h>
#include <SymbolsTable.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    SymbolsTable symbolsTable;

    createSymbolsTable(&symbolsTable);
    yyparse(&symbolsTable);

    return EXIT_SUCCESS;
}