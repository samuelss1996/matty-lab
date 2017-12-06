#include <stdlib.h>
#include <stdio.h>
#include <SyntacticDefinitions.tab.h>
#include <SymbolsTable.h>
#include <NativeFunctions.h>
#include <time.h>
#include <Definitions.h>

extern int readingFile;

void printWelcome();
void parseArguments(int argc, char **argv);

// TODO maybe supply file as argument
int main(int argc, char **argv) {
    SymbolsTable symbolsTable;

    printWelcome();
    parseArguments(argc, argv);

    createSymbolsTable(&symbolsTable);
    setSymbolsTable(&symbolsTable);

    if(!readingFile) {
        prompt();
    }

    srand((unsigned int) time(NULL));
    yyparse(&symbolsTable);

    destroySymbolsTable(&symbolsTable);

    return EXIT_CODE_SUCCESS;
}

void printWelcome() {
    FILE *welcomeFile = fopen(WELCOME_MESSAGE_FILE, "rb");
    char welcomeContent[2048];

    fread(welcomeContent, 1, 2048, welcomeFile);
    printf("%s", welcomeContent);
}

void parseArguments(int argc, char **argv) {
    switch(argc) {
        case 1: return;
        case 2 :
            readingFile = _load(argv[1]);
            break;
        default:
            printf("Usos:\n\t%s\n\t%s {archivo a ejecutar}", argv[0], argv[0]);
            exit(EXIT_CODE_WRONG_ARGUMENTS);
    }
}