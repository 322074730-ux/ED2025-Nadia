#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Include/utils.h"

// Declaración de función externa
char* convertirInfijaAPostfija(const char* infija);

// Función auxiliar
static void invertirCadena(char* str) {
    if (!str) return;
    
    int longitud = strlen(str);
    for (int i = 0; i < longitud / 2; i++) {
        char temp = str[i];
        str[i] = str[longitud - i - 1];
        str[longitud - i - 1] = temp;
    }
}

// Función auxiliar
static void intercambiarParentesis(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') str[i] = ')';
        else if (str[i] == ')') str[i] = '(';
    }
}

char* convertirInfijaAPrefija(const char* infija) {
    if (!infija || strlen(infija) == 0) {
        return strdup("");
    }
    
    // Paso 1: Invertir la expresión
    char* invertida = strdup(infija);
    if (!invertida) return strdup("ERROR: Memoria insuficiente");
    
    invertirCadena(invertida);
    
    // Paso 2: Intercambiar paréntesis
    intercambiarParentesis(invertida);
    
    // Paso 3: Convertir a postfija
    char* postfija = convertirInfijaAPostfija(invertida);
    free(invertida);
    
    if (!postfija) {
        return strdup("ERROR: Conversion fallida");
    }
    
    // Verificar si es error
    if (strstr(postfija, "ERROR")) {
        return postfija;
    }
    
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
