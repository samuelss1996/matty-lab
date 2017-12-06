#include <stdio.h>
#include <math.h>
#include <SymbolsTable.h>
#include <lex.yy.h>
#include <Errors.h>
#include <Definitions.h>

SymbolsTable* symbolsTable;

double _acos(double *arguments) {
    return acos(arguments[0]);
}

double _asin(double *arguments) {
    return asin(arguments[0]);
}

double _atan(double *arguments) {
    return atan(arguments[0]);
}

double _atan2(double * arguments) {
    return atan2(arguments[0], arguments[1]);
}

double _cos(double *arguments) {
    return cos(arguments[0]);
}

double _cosh(double *arguments) {
    return cosh(arguments[0]);
}

double _sin(double *arguments) {
    return sin(arguments[0]);
}

double _sinh(double *arguments) {
    return sinh(arguments[0]);
}

double _tanh(double *arguments) {
    return tanh(arguments[0]);
}

double _exp(double *arguments) {
    return exp(arguments[0]);
}

double _ldexp(double * arguments) {
    return ldexp(arguments[0], (int) arguments[1]);
}

double _log(double *arguments) {
    return log(arguments[0]);
}

double _log10(double *arguments) {
    return log10(arguments[0]);
}

double _sqrt(double *arguments) {
    return sqrt(arguments[0]);
}

double _ceil(double *arguments) {
    return ceil(arguments[0]);
}

double _fabs(double *arguments) {
    return fabs(arguments[0]);
}

double _floor(double *arguments) {
    return floor(arguments[0]);
}

double _fmod(double * arguments) {
    return fmod(arguments[0], arguments[1]);
}

double _random(double *arguments) {
    return rand() / (float) RAND_MAX;
}

double _intRandom(double *arguments) {
    double min = arguments[0] < arguments[1]? arguments[0]: arguments[1];
    double max = arguments[0] > arguments[1]? arguments[0]: arguments[1];

    return ((int) min) + floor(_random(arguments) * ((int)(max - min + 1)));
}

double _help(double *arguments) {
    int maxFileSize = 8192;
    FILE* helpFile = fopen(HELP_MESSAGE_FILE, "rb");
    char *helpContent = malloc(maxFileSize * sizeof(char));

    if(helpFile == NULL) {
        printf(ANSI_COLOR_ERROR "No se puede mostrar la ayuda: No se ha encontrado el fichero de ayuda '%s'. Asegurese de que esta ejecutando "
                       "la caluladora en el entorno correcto\n\n" ANSI_COLOR_RESET, HELP_MESSAGE_FILE);

        free(helpContent);
        return 0;
    }

    helpContent[fread(helpContent, 1, 8192, helpFile)] = '\0';
    printf("%s", helpContent);

    free(helpContent);
    return 0;
}

double _who(double *arguments) {
    char** symbols = getAllSymbols(symbolsTable);
    int i;

    for(i = 0; symbols[i] != NULL; i++) {
        if(getReadability(symbolsTable, symbols[i]) == READABILITY_VARIABLE) {
            printf("%s = %.10g\n", symbols[i], getVariableValue(symbolsTable, symbols[i]));
        }
    }

    return 0;
}

double _clear(double *arguments) {
    clearSymbolsTable(symbolsTable);
    return 0;
}

int _load(char *filename) {
    FILE* file = fopen(filename, "r+");

    if(file != NULL) {
        yy_switch_to_buffer(yy_create_buffer(fopen(filename, "r"), YY_BUF_SIZE));
        printf("Archivo cargado.\n");

        return 1;
    }

    errorLoadingFile(filename);
    return 0;
}

void setSymbolsTable(SymbolsTable* _symbolsTable) {
    symbolsTable = _symbolsTable;
}

void prompt() {
    printf("> ");
    fflush(stdout);
}