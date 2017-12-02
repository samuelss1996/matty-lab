#include <stdio.h>
#include <stdlib.h>
#include <SyntacticDefinitions.tab.h>

int main() {
    yyparse();

    return EXIT_SUCCESS;
}