#include <stdio.h>
#include <Definitions.h>
#include <util/LinkedList.h>
#include <symbols/SymbolsTable.h>

void yyerror(void* symbolsTable, const char *string) { }


void syntacticError(int handledError) {
    if(!handledError) {
        printf(ANSI_COLOR_ERROR "Error sintáctico. Puedes escribir 'help' para acceder al manual\n" ANSI_COLOR_RESET);
    }
}

void errorAssigningValue(int errorCode, char *symbolName) {
    printf(ANSI_COLOR_ERROR "Error asignando valor: %s es una ", symbolName);

    switch(errorCode) {
        case ASSIGNABILITY_SYMBOL_CONSTANT: printf("constante.\n" ANSI_COLOR_RESET); break;
        case ASSIGNABILITY_SYMBOL_FUNCTION: printf("funcion.\n" ANSI_COLOR_RESET); break;
        default: break;
    }
}

void errorCallingFunction(int errorCode, SymbolsTable* symbolsTable,  char* functionName, int suppliedArgsCount) {
    SymbolsTableValue symbol;
    int expectedArgsCount;

    printf(ANSI_COLOR_ERROR "Error invocando a %s: ", functionName);

    switch(errorCode) {
        case CALLABILITY_SYMBOL_NOT_FOUND: printf("la funcion no existe.\n" ANSI_COLOR_RESET); break;
        case CALLABILITY_SYMBOL_NOT_FUNCTION: printf("el simbolo no es una funcion.\n" ANSI_COLOR_RESET); break;
        case CALLABILITY_ARGUMENT_COUNT_MISMATCH:
            symbol = findSymbol(symbolsTable, functionName);
            expectedArgsCount = getFunctionArgumentCount(&symbol);

            printf("la función necesita exactamente %d argumentos (se han dado %d).\n" ANSI_COLOR_RESET, expectedArgsCount, suppliedArgsCount);
            break;
        default: break;
    }
}

void errorDisplayingSymbolValue(int errorCode, char* symbolName) {
    printf(ANSI_COLOR_ERROR "Error accediendo al valor de %s: ", symbolName);

    switch(errorCode) {
        case READABILITY_SYMBOL_NOT_FOUND: printf("el símbolo no existe.\n" ANSI_COLOR_RESET); break;
        case READABILITY_SYMBOL_FUNCTION: printf("no se puede mostrar el valor de una función.\n" ANSI_COLOR_RESET); break;
        default: break;
    }
}

void errorLoadingFile(char *filename) {
    printf(ANSI_COLOR_ERROR "Error: No ha se ha podido cargar '%s'. Compruebe que existe y tiene los permisos adecuados\n" ANSI_COLOR_RESET, filename);
}