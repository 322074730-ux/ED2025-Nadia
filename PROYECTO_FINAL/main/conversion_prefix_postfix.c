#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Include/utils.h"

char* convertirPrefijaAInfija(const char* prefija);
char* convertirInfijaAPostfija(const char* infija);

char* convertirPrefijaAPostfija(const char* prefija) {
    if (!prefija || strlen(prefija) == 0) {
        return strdup("");
    }
    
    char* infija = convertirPrefijaAInfija(prefija);
    if (!infija) {
        return strdup("ERROR: Conversion prefija a infija fallida");
    }
    
    if (strstr(infija, "ERROR")) {
        char* resultado = strdup(infija);
        free(infija);
        return resultado;
    }
    
    char* postfija = convertirInfijaAPostfija(infija);
    
    free(infija);
    return postfija;
}
