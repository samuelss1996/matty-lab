#include <stdlib.h>
#include <stdio.h>
#include <SyntacticDefinitions.tab.h>
#include <SymbolsTable.h>
#include <NativeFunctions.h>
#include <time.h>

void printWelcome();

// TODO add clear workspace command
// TODO maybe add more operators
// TODO create 'prompt' function, which should perform a fflush
// TODO maybe print as double instead of float
// TODO improve error management
// TODO dynamic argValues array
// TODO handle arithmetic exceptions
// TODO why symbols table is void* in bison file
// TODO multiple statements in one line
// TODO allow ';' after keywords
// TODO allow multiple ';' together
// TODO maybe supply file as argument
// TODO maybe include functions like avg(x,y,z...)
// TODO maybe add data types
int main() {
    SymbolsTable symbolsTable;

    createSymbolsTable(&symbolsTable);
    setSymbolsTable(&symbolsTable);

    printWelcome();
    printf("> ");

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