#include "conversion_infix_prefix.h"
#include "conversion_infix_postfix.h"
#include "stack.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Invertir cadena
void invertirCadena(char* str) {
    if (!str) return;
    
    int longitud = strlen(str);
    for (int i = 0; i < longitud / 2; i++) {
        char temp = str[i];
        str[i] = str[longitud - i - 1];
        str[longitud - i - 1] = temp;
    }
}

// Intercambiar paréntesis
void intercambiarParentesis(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') str[i] = ')';
        else if (str[i] == ')') str[i] = '(';
    }
}

// Convertir infija a prefija
char* convertirInfijaAPrefija(const char* infija) {
    if (!infija || strlen(infija) == 0) {
        return strdup("");
    }
    
    // Paso 1: Invertir la expresión
    char* invertida = strdup(infija);
    invertirCadena(invertida);
    
    // Paso 2: Intercambiar paréntesis
    intercambiarParentesis(invertida);
    
    // Paso 3: Convertir a postfija
    char* postfija = convertirInfijaAPostfija(invertida);
    free(invertida);
    
    // Paso 4: Invertir el resultado
    invertirCadena(postfija);
    
    // Eliminar espacios al final si existen
    int longitud = strlen(postfija);
    while (longitud > 0 && postfija[longitud-1] == ' ') {
        postfija[longitud-1] = '\0';
        longitud--;
    }
    
    return postfija;
}
