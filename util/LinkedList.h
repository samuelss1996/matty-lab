typedef void* LinkedList;
typedef void* ListNode;
typedef void* ListItem;
typedef void* SymbolsTableValue;

void createList(LinkedList* list);
ListNode firstNode(LinkedList* list);
ListNode nextNode(ListNode baseNode);
ListItem nodeItem(ListNode node);
void createItem(ListItem* item, char* key, SymbolsTableValue* value);
char* itemKey(ListItem item);
SymbolsTableValue itemValue(ListItem item);
void append(LinkedList* list, ListItem item);
void destroyList(LinkedList* list);

void createVariable(SymbolsTableValue* symbolsTableValue, double value);
void createConstant(SymbolsTableValue* symbol, double value);
void createFunction(SymbolsTableValue* symbol, double (*functionPointer)(double*), int argCount);
int getSymbolType(SymbolsTableValue* symbol);
double getSymbolsTableValueAsNumber(SymbolsTableValue* symbolsTableValue);
int getFunctionArgumentCount(SymbolsTableValue *symbols);
double callSymbolFunction(SymbolsTableValue* symbol, double* arguments);
void modifySymbolsTableValue(SymbolsTableValue* target, SymbolsTableValue* source);