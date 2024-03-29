#include <stdlib.h>
#include <string.h>
#include <Definitions.h>

typedef struct {
    int type;
    union {
        double numericValue;
        struct {
            double (*functionPointer)(double*);
            int argCount;
        } function;
    } value;
} SymbolsTableValueStruct;

typedef SymbolsTableValueStruct* SymbolsTableValue;

typedef struct {
    char* key;
    SymbolsTableValue* value;
} ListItemStruct;

typedef ListItemStruct* ListItem;

typedef struct listNode {
    ListItem item;
    struct listNode* next;
} ListNodeStruct;

typedef ListNodeStruct* ListNode;

typedef struct {
    ListNode first;
    ListNode last;
} LinkedListStruct;

typedef LinkedListStruct* LinkedList;

/**
 * Crea una lista enlazada vacía. Las listas enlazadas se usan en la tabla hash para gestionar colisiones mediante encadenamiento
 * @param list La lista
 */
void createList(LinkedList* list){
    *list = (LinkedList) malloc(sizeof(LinkedListStruct));

    (*list)->first = NULL;
    (*list)->last = NULL;
}

/**
 * Devuelve el primer nodo de la lista
 * @param list La lista
 * @return El primer nodo
 */
ListNode firstNode(LinkedList* list){
    return (*list)->first;
}

/**
 * Devuelve el siguiente nodo de un nodo dado
 * @param baseNode El nodo del cual se quiere conocer su sucesor
 * @return El nodo sucesor
 */
ListNode nextNode(ListNode baseNode) {
    return baseNode->next;
}

/**
 * Obtiene el valor propiamente dicho de un nodo de la lista, el elemento que almacena la lista de manera útil
 * @param node El nodo
 * @return El valor
 */
ListItem nodeItem(ListNode node) {
    return node->item;
}

/**
 * Crea un ítem de la lista. Los ítems contienen una clave y un valor, que la tabla hash necesita para funcionar
 * @param item El ítem a crear
 * @param key La clave
 * @param value El valor
 */
void createItem(ListItem* item, char* key, SymbolsTableValue* value) {
    *item = (ListItem) malloc(sizeof(ListItemStruct));

    (*item)->key = (char *) malloc((strlen(key) + 1) * sizeof(char));

    strcpy((*item)->key, key);
    (*item)->value = value;
}

/**
 * Destruye un ítem, liberando todos los recursos
 * @param item El ítem a destruir
 */
void destroyItem(ListItem* item) {
    free((*item)->key);
    free(*(*item)->value);
    free(*item);
}

/**
 * Obtiene la clave de un item
 * @param item El item
 * @return La clave
 */
char* itemKey(ListItem item){
    return item->key;
}

/**
 * Obtiene el valor de un item
 * @param item El item
 * @return El valor
 */
SymbolsTableValue itemValue(ListItem item){
    return *item->value;
}

/**
 * Añade un nuevo item al final de la lista
 * @param list La lista
 * @param item El item a añadir
 */
void append(LinkedList* list, ListItem item){
    ListNode newNode = (ListNode) malloc(sizeof(ListNodeStruct));

    newNode->item = item;
    newNode->next = NULL;

    if((*list)->last == NULL) {
        (*list)->first = newNode;
    } else {
        (*list)->last->next = newNode;
    }

    (*list)->last = newNode;
}

/**
 * Destruye la lista, liberando todos los recursos
 * @param list La lista
 */
void destroyList(LinkedList* list){
    ListNode currentNode;

    while((*list)->first != NULL) {
        currentNode = (*list)->first;
        (*list)->first = (*list)->first->next;

        destroyItem(&currentNode->item);
        free(currentNode);
    }

    (*list)->first = (*list)->last = NULL;
    free(*list);
}

void createVariable(SymbolsTableValue* symbolsTableValue, double value) {
    *symbolsTableValue = (SymbolsTableValue) malloc(sizeof(SymbolsTableValueStruct));

    (*symbolsTableValue)->type = SYMBOL_TYPE_VARIABLE;
    (*symbolsTableValue)->value.numericValue = value;
}

void createConstant(SymbolsTableValue* symbol, double value) {
    *symbol = (SymbolsTableValue) malloc(sizeof(SymbolsTableValueStruct));

    (*symbol)->type = SYMBOL_TYPE_CONSTANT;
    (*symbol)->value.numericValue = value;
}

void createFunction(SymbolsTableValue* symbol, double (*functionPointer)(double*), int argCount) {
    *symbol = (SymbolsTableValue) malloc(sizeof(SymbolsTableValueStruct));

    (*symbol)->type = SYMBOL_TYPE_FUNCTION;
    (*symbol)->value.function.functionPointer = functionPointer;
    (*symbol)->value.function.argCount = argCount;
}

int getSymbolType(SymbolsTableValue* symbol) {
    return (*symbol)->type;
}

double getSymbolsTableValueAsNumber(SymbolsTableValue* symbolsTableValue) {
    return (*symbolsTableValue)->value.numericValue;
}

int getFunctionArgumentCount(SymbolsTableValue *symbols) {
    return (*symbols)->value.function.argCount;
}

double callSymbolFunction(SymbolsTableValue* symbol, double* arguments) {
    return (*(*symbol)->value.function.functionPointer)(arguments);
}

void modifySymbolsTableValue(SymbolsTableValue* target, SymbolsTableValue* source) {
    (*target)->type = (*source)->type;
    (*target)->value = (*source)->value;
}