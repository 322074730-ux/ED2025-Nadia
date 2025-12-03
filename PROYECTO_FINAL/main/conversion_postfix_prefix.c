#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Include/utils.h"

// Declaraciones de funciones externas
char* convertirPostfijaAInfija(const char* postfija);
char* convertirInfijaAPrefija(const char* infija);

char* convertirPostfijaAPrefija(const char* postfija) {
    if (!postfija || strlen(postfija) == 0) {
        return strdup("");
    }
    
    // Paso 1: Convertir postfija a infija
    char* infija = convertirPostfijaAInfija(postfija);
    if (!infija) {
        return strdup("ERROR: Conversion postfija a infija fallida");
    }
    
    // Verificar si hay error
    if (strstr(infija, "ERROR")) {
        char* resultado = strdup(infija);
        free(infija);
        return resultado;
    }
    
    // Paso 2: Convertir infija a prefija
    char* prefija = convertirInfijaAPrefija(infija);
    
    free(infija);
    return prefija;
}
