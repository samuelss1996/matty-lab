#include <stdio.h>
#include <math.h>
#include "Definitions.h"

double _sin(double *arguments) {
    return sin(arguments[0]);
}

double _cos(double *arguments) {
    return cos(arguments[0]);
}

double _atan(double *arguments) {
    return atan(arguments[0]);
}

double _log(double *arguments) {
    return log(arguments[0]);
}

double _exp(double *arguments) {
    return exp(arguments[0]);
}

double _sqrt(double *arguments) {
    return sqrt(arguments[0]);
}

double _help(double *arguments) {
    FILE* helpFile = fopen(HELP_MESSAGE_FILE, "rb");
    char helpContent[2048];

    fread(helpContent, 1, 2048, helpFile);
    printf("%s", helpContent);
}

double _who(double *arguments) {

}