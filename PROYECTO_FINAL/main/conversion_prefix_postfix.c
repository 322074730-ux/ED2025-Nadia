#include "conversion_prefix_postfix.h"
#include "conversion_prefix_infix.h"
#include "conversion_infix_postfix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convertir prefija a postfija
char* convertirPrefijaAPostfija(const char* prefija) {
    if (!prefija || strlen(prefija) == 0) {
        return strdup("");
    }
    
    // Paso 1: Convertir prefija a infija
    char* infija = convertirPrefijaAInfija(prefija);
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
