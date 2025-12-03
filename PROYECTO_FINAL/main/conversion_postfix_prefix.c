#include "conversion_postfix_prefix.h"
#include "conversion_postfix_infix.h"
#include "conversion_infix_prefix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convertir postfija a prefija
char* convertirPostfijaAPrefija(const char* postfija) {
    if (!postfija || strlen(postfija) == 0) {
        return strdup("");
    }
    
    // Paso 1: Convertir postfija a infija
    char* infija = convertirPostfijaAInfija(postfija);
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
