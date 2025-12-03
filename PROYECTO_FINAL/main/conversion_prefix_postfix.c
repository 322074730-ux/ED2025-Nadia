#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Include/utils.h"

// Declaraciones de funciones externas
char* convertirPrefijaAInfija(const char* prefija);
char* convertirInfijaAPostfija(const char* infija);

char* convertirPrefijaAPostfija(const char* prefija) {
    if (!prefija || strlen(prefija) == 0) {
        return strdup("");
    }
    
    // Paso 1: Convertir prefija a infija
    char* infija = convertirPrefijaAInfija(prefija);
    if (!infija) {
        return strdup("ERROR: Conversion prefija a infija fallida");
    }
    
    // Verificar si hay error
    if (strstr(infija, "ERROR")) {
        char* resultado = strdup(infija);
        free(infija);
        return resultado;
    }
    
    // Paso 2: Convertir infija a postfija
    char* postfija = convertirInfijaAPostfija(infija);
    
    free(infija);
    return postfija;
}
