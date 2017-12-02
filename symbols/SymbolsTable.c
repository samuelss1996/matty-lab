#include "Definitions.h"
#include "HashTable.h"

#include <stdlib.h>

typedef struct {
    HashTable hashTable;
} SymbolsTableStruct;

typedef SymbolsTableStruct* SymbolsTable;

/**
 * Crea e inicializa la tabla de símbolos, rellenándola con las palabras reservadas
 * @param symbolsTable La tabla de śimbolos
 */
void createSymbolsTable(SymbolsTable* symbolsTable) {
    *symbolsTable = (SymbolsTable) malloc(sizeof(SymbolsTableStruct));
    createHashTable(&(*symbolsTable)->hashTable, SYMBOLS_HASH_TABLE_CAPACITY);
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
SymbolsTableValue* findSymbol(SymbolsTable* symbolsTable, char *token) {
    return findHash(&(*symbolsTable)->hashTable, token);
}

/**
 * Consultar un símbolo en la tabla de śimbolos, si no existe, añadirlos
 * @param symbolsTable La tabla de símbolos
 * @param token La cadena de texto del símbolo a consultar
 * @param id El identificador del símbolo. En caso de que no exista se insertará con este id
 * @return El identificador del símbolo (el que ya estaba o el que se ha pasado)
 */
SymbolsTableValue* findOrAdd(SymbolsTable* symbolsTable, char* token, SymbolsTableValue* value) {
    SymbolsTableValue* result = findSymbol(symbolsTable, token);

    if(result == NULL) {
        result = value;
        addSymbol(symbolsTable, token, result);
    }

    return result;
}

/**
 * Destruye la tabla de símbolos, liberando todos los recursos
 * @param symbolsTable La tabla de śimbolos
 */
void destroySymbolsTable(SymbolsTable* symbolsTable) {
    destroyHashTable(&(*symbolsTable)->hashTable);
    free(*symbolsTable);
}