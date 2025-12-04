#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Include/utils.h"

char* convertirPostfijaAInfija(const char* postfija);
char* convertirInfijaAPrefija(const char* infija);

char* convertirPostfijaAPrefija(const char* postfija) {
    if (!postfija || strlen(postfija) == 0) {
        return strdup("");
    }
    
    char* infija = convertirPostfijaAInfija(postfija);
    if (!infija) {
        return strdup("ERROR: Conversion postfija a infija fallida");
    }
    
    if (strstr(infija, "ERROR")) {
        char* resultado = strdup(infija);
        free(infija);
        return resultado;
    }
    
    char* prefija = convertirInfijaAPrefija(infija);
    
    free(infija);
    return prefija;
}
