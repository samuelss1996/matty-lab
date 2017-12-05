#include <stdio.h>
#include <math.h>
#include <SymbolsTable.h>

SymbolsTable* symbolsTable;

double _sin(double *arguments) {
    return sin(arguments[0]);
}

double _cos(double *arguments) {
    return cos(arguments[0]);
}

double _atan(double *arguments) {
    return atan(arguments[0]);
}

double _log(double *arguments) {
    return log(arguments[0]);
}

double _exp(double *arguments) {
    return exp(arguments[0]);
}

double _sqrt(double *arguments) {
    return sqrt(arguments[0]);
}

double _help(double *arguments) {
    FILE* helpFile = fopen(HELP_MESSAGE_FILE, "rb");
    char helpContent[2048];

    fread(helpContent, 1, 2048, helpFile);
    printf("%s", helpContent);

    return 0;
}

double _who(double *arguments) {
    char** symbols = getAllSymbols(symbolsTable);
    int i;

    for(i = 0; symbols[i] != NULL; i++) {
        if(getReadability(symbolsTable, symbols[i]) == READABILITY_VARIABLE) {
            printf("%s = %f\n", symbols[i], getVariableValue(symbolsTable, symbols[i]));
        }
    }

    return 0;
}

void setSymbolsTable(SymbolsTable* _symbolsTable) {
    symbolsTable = _symbolsTable;
}