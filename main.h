#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

void leString (char *string, int tamanho){
    fflush (stdin);
    fgets (string, tamanho - 1, stdin);
    string[strcspn (string, "\n")] = '\0';
}