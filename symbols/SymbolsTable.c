#include <stdlib.h>
#include <math.h>

#include "Definitions.h"
#include "HashTable.h"

typedef struct {
    char *functionName;
    double (*functionPointer)(double);
} NativeFunction;

typedef struct {
    HashTable hashTable;
} SymbolsTableStruct;

typedef SymbolsTableStruct* SymbolsTable;

void addNativeFunctions(SymbolsTable* symbolsTable);
NativeFunction nativeFunctions[] = {"sin", sin, "cos", cos, "atan", atan, "log", log, "exp", exp, "sqrt", sqrt, 0, 0};


/**
 * Crea e inicializa la tabla de símbolos, rellenándola con las palabras reservadas
 * @param symbolsTable La tabla de śimbolos
 */
void createSymbolsTable(SymbolsTable* symbolsTable) {
    *symbolsTable = (SymbolsTable) malloc(sizeof(SymbolsTableStruct));
    createHashTable(&(*symbolsTable)->hashTable, SYMBOLS_HASH_TABLE_CAPACITY);

    addNativeFunctions(symbolsTable);
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

int existsVariable(SymbolsTable* symbolsTable, char *name) {
    SymbolsTableValue symbol = findSymbol(symbolsTable, name);

    return symbol != NULL && getSymbolType(&symbol) == SYMBOL_TYPE_VARIABLE;
}

double getVariableValue(SymbolsTable* symbolsTable, char* variableName) {
    SymbolsTableValue symbol = findSymbol(symbolsTable, variableName);

    return getSymbolsTableValueAsNumber(&symbol);
}

int existsFunction(SymbolsTable* symbolsTable, char *functionName) {
    SymbolsTableValue symbol = findSymbol(symbolsTable, functionName);

    return symbol != NULL && getSymbolType(&symbol) == SYMBOL_TYPE_FUNCTION;
}

double callFunction(SymbolsTable* symbolsTable, char* functionName, double argument) {
    SymbolsTableValue function = findSymbol(symbolsTable, functionName);
    
    return callSymbolFunction(&function, argument);
}

void addNativeFunctions(SymbolsTable* symbolsTable) {
    SymbolsTableValue* symbol;
    int i;

    for(i = 0; nativeFunctions[i].functionName != 0; i++) {
        symbol = malloc(sizeof(SymbolsTableValue));
        createFunction(symbol, nativeFunctions[i].functionPointer);

        addSymbol(symbolsTable, nativeFunctions[i].functionName, symbol);
    }
}

/**
 * Destruye la tabla de símbolos, liberando todos los recursos
 * @param symbolsTable La tabla de śimbolos
 */
void destroySymbolsTable(SymbolsTable* symbolsTable) {
    destroyHashTable(&(*symbolsTable)->hashTable);
    free(*symbolsTable);
}