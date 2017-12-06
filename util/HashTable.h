#include "LinkedList.h"

typedef void* HashTable;

void createHashTable(HashTable* hashTable, int initialCapacity);
SymbolsTableValue findHash(HashTable* hashTable, char* key);
void insertHash(HashTable* hashTable, char* key, SymbolsTableValue* value);
void clearHashTable(HashTable* hashTable);
void destroyHashTable(HashTable* hashTable);
char** getAllKeys(HashTable* hashTable);