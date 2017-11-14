#include <stdio.h>
#include <stdlib.h>
#include <SyntacticDefinitions.tab.h>

int main() {
    printf("%d", yyparse());

    return EXIT_SUCCESS;
}