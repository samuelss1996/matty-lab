#include <stdlib.h>
#include <stdio.h>
#include <SyntacticDefinitions.tab.h>
#include <SymbolsTable.h>

void printWelcome();

// TODO include command to print the memory status
// TODO check scientific notation
// TODO check what happens with numbers like "1."
// TODO improve error management
// TODO add constants
// TODO consider native functions with different signatures
// TODO maybe add data types
// TODO dynamic argValues array
// TODO add constants
// TODO prohibit redefinition of constants and functions
// TODO maybe add more operators
// TODO handle arithmetic exceptions
// TODO create delegates to all functions in order to fix the variable arguments problem
// TODO add 'random' function for the lolz
// TODO create 'prompt' function, which should perform a fflush
// TODO why symbols table is void* in bison file
int main() {
    SymbolsTable symbolsTable;

    createSymbolsTable(&symbolsTable);
    printWelcome();
    printf("> ");

    yyparse(&symbolsTable);

    return EXIT_SUCCESS;
}

void handleFunctionCall() {

}

void printWelcome() {
    FILE *welcomeFile = fopen(WELCOME_MESSAGE_FILE, "rb");
    char welcomeContent[2048];

    fread(welcomeContent, 1, 2048, welcomeFile);
    printf("%s", welcomeContent);
}