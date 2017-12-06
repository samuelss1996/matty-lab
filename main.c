#include <stdlib.h>
#include <stdio.h>
#include <SyntacticDefinitions.tab.h>
#include <SymbolsTable.h>
#include <NativeFunctions.h>
#include <time.h>

void printWelcome();

// TODO improve error management
// TODO why symbols table is void* in bison file
// TODO maybe supply file as argument
int main() {
    SymbolsTable symbolsTable;

    createSymbolsTable(&symbolsTable);
    setSymbolsTable(&symbolsTable);

    printWelcome();
    prompt();

    srand((unsigned int) time(NULL));
    yyparse(&symbolsTable);

    return EXIT_SUCCESS;
}

void printWelcome() {
    FILE *welcomeFile = fopen(WELCOME_MESSAGE_FILE, "rb");
    char welcomeContent[2048];

    fread(welcomeContent, 1, 2048, welcomeFile);
    printf("%s", welcomeContent);
}