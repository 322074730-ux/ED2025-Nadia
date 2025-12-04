#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Include/utils.h"


static void invertirCadena(char* str) {
    if (!str) return;
    
    int longitud = strlen(str);
    for (int i = 0; i < longitud / 2; i++) {
        char temp = str[i];
        str[i] = str[longitud - i - 1];
        str[longitud - i - 1] = temp;
    }
}

static void intercambiarParentesis(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') str[i] = ')';
        else if (str[i] == ')') str[i] = '(';
    }
}

char* convertirInfijaAPostfija(const char* infija);

char* convertirInfijaAPrefija(const char* infija) {
    if (!infija || strlen(infija) == 0) {
        return strdup("");
    }
    
    char* invertida = strdup(infija);
    if (!invertida) return strdup("ERROR: Memoria insuficiente");
    
    invertirCadena(invertida);
    
    intercambiarParentesis(invertida);
    
    char* postfija = convertirInfijaAPostfija(invertida);
    free(invertida);
    
    if (!postfija) {
        return strdup("ERROR: Conversion fallida");
    }
    
    invertirCadena(postfija);
    int longitud = strlen(postfija);
    while (longitud > 0 && postfija[longitud-1] == ' ') {
        postfija[longitud-1] = '\0';
        longitud--;
    }
    
    return postfija;
}
