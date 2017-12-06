#include <stdlib.h>
#include <NativeFunctions.h>
#include <Definitions.h>
#include <math.h>

#include "HashTable.h"

typedef struct {
    char *functionName;
    int argCount;
    double (*functionPointer)(double*);
} NativeFunction;

typedef struct {
    char *constantName;
    double value;
} Constant;

typedef struct {
    HashTable hashTable;
} SymbolsTableStruct;

typedef SymbolsTableStruct* SymbolsTable;

NativeFunction nativeFunctions[] = {"acos", 1, _acos, "asin", 1, _asin, "atan", 1, _atan, "atan2", 2, _atan2, "cos", 1, _cos,
                                    "cosh", 1, _cosh, "sin", 1, _sin, "sinh", 1, _sinh, "tanh", 1, _tanh, "exp", 1, _exp,
                                    "ldexp", 2, _ldexp, "log", 1, _log, "log10", 1, _log10, "sqrt", 1, _sqrt, "ceil", 1, _ceil,
                                    "fabs", 1, _fabs, "floor", 1, _floor, "fmod", 2, _fmod, "random", 0, _random, "intRandom", 2, _intRandom,
                                    "help", 0, _help, "who", 0, _who, 0, 0, 0};

Constant nativeConstants[] = {"e", M_E, "pi", M_PI, 0, 0};

void addNativeValues(SymbolsTable *symbolsTable);

/**
 * Crea e inicializa la tabla de símbolos, rellenándola con las palabras reservadas
 * @param symbolsTable La tabla de śimbolos
 */
void createSymbolsTable(SymbolsTable* symbolsTable) {
    *symbolsTable = (SymbolsTable) malloc(sizeof(SymbolsTableStruct));
    createHashTable(&(*symbolsTable)->hashTable, SYMBOLS_HASH_TABLE_CAPACITY);

    addNativeValues(symbolsTable);
}

/**
 * Añade un símbolo a la tabla de símbolos
 * @param symbolsTable La tabla de śimbolos
 * @param token La cadena de texto que representa al símbolo
 * @param id El identificador
 */
void addSymbol(SymbolsTable* symbolsTable, char *token, SymbolsTableValue* value) {
    insertHash(&(*symbolsTable)->hashTable, token, value);
}

/**
 * Consultar un símbolo a la tabla de símbolos
 * @param symbolsTable La tabla de śimbolos
 * @param token La cadena de texto del símbolo a consultar
 * @return El identificador del śimbolo
 */
SymbolsTableValue findSymbol(SymbolsTable* symbolsTable, char *token) {
    return findHash(&(*symbolsTable)->hashTable, token);
}

/**
 * Consultar un símbolo en la tabla de śimbolos, si no existe, añadirlos
 * @param symbolsTable La tabla de símbolos
 * @param token La cadena de texto del símbolo a consultar
 * @param id El identificador del símbolo. En caso de que no exista se insertará con este id
 * @return El identificador del símbolo (el que ya estaba o el que se ha pasado)
 */
SymbolsTableValue findOrAdd(SymbolsTable* symbolsTable, char* token, SymbolsTableValue* value) {
    SymbolsTableValue result = findSymbol(symbolsTable, token);

    if(result == NULL) {
        result = value;
        addSymbol(symbolsTable, token, result);
    }

    return result;
}

void assignVariable(SymbolsTable* symbolsTable, char* variableName, double value) {
    SymbolsTableValue* tableValue = malloc(sizeof(SymbolsTableValue));

    createVariable(tableValue, value);
    addSymbol(symbolsTable, variableName, tableValue);
}

double getVariableValue(SymbolsTable* symbolsTable, char* variableName) {
    SymbolsTableValue symbol = findSymbol(symbolsTable, variableName);

    return getSymbolsTableValueAsNumber(&symbol);
}

int getReadability(SymbolsTable* symbolsTable, char *name) {
    SymbolsTableValue symbol = findSymbol(symbolsTable, name);
    int symbolType;

    if(symbol == NULL) {
        return READABILITY_SYMBOL_NOT_FOUND;
    } else if((symbolType = getSymbolType(&symbol)) == SYMBOL_TYPE_FUNCTION) {
        return READABILITY_SYMBOL_FUNCTION;
    } else if(symbolType == SYMBOL_TYPE_CONSTANT) {
        return READABILITY_CONSTANT;
    }

    return READABILITY_VARIABLE;
}

int getAssignability(SymbolsTable* symbolsTable, char *name) {
    SymbolsTableValue symbol = findSymbol(symbolsTable, name);
    int symbolType;

    if(symbol != NULL) {
        if((symbolType = getSymbolType(&symbol)) == SYMBOL_TYPE_FUNCTION) {
            return ASSIGNABILITY_SYMBOL_FUNCTION;
        } else if(symbolType == SYMBOL_TYPE_CONSTANT) {
            return ASSIGNABILITY_SYMBOL_CONSTANT;
        }
    }

    return ASSIGNABILITY_ASSIGNABLE;
}

int getCallability(SymbolsTable* symbolsTable, char *functionName, int suppliedArgsCount) {
    SymbolsTableValue symbol = findSymbol(symbolsTable, functionName);

    if(symbol == NULL) {
        return CALLABILITY_SYMBOL_NOT_FOUND;
    } else if(getSymbolType(&symbol) != SYMBOL_TYPE_FUNCTION) {
        return CALLABILITY_SYMBOL_NOT_FUNCTION;
    } else if(getFunctionArgumentCount(&symbol) != suppliedArgsCount) {
        return CALLABILITY_ARGUMENT_COUNT_MISMATCH;
    }

    return CALLABILITY_CALLABLE;
}

double callFunction(SymbolsTable* symbolsTable, char* functionName, double *arguments) {
    SymbolsTableValue function = findSymbol(symbolsTable, functionName);
    
    return callSymbolFunction(&function, arguments);
}

char** getAllSymbols(SymbolsTable* symbolsTable) {
    return getAllKeys(&(*symbolsTable)->hashTable);
}

/**
 * Destruye la tabla de símbolos, liberando todos los recursos
 * @param symbolsTable La tabla de śimbolos
 */
void destroySymbolsTable(SymbolsTable* symbolsTable) {
    destroyHashTable(&(*symbolsTable)->hashTable);
    free(*symbolsTable);
}

void addNativeValues(SymbolsTable *symbolsTable) {
    SymbolsTableValue* symbol;
    int i;

    for(i = 0; nativeConstants[i].constantName != 0; i++) {
        symbol = malloc(sizeof(SymbolsTableValue));
        createConstant(symbol, nativeConstants[i].value);

        addSymbol(symbolsTable, nativeConstants[i].constantName, symbol);
    }

    for(i = 0; nativeFunctions[i].functionName != 0; i++) {
        symbol = malloc(sizeof(SymbolsTableValue));
        createFunction(symbol, nativeFunctions[i].functionPointer, nativeFunctions[i].argCount);

        addSymbol(symbolsTable, nativeFunctions[i].functionName, symbol);
    }
}