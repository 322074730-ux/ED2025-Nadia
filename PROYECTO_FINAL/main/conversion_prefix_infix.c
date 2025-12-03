#include "conversion_prefix_infix.h"
#include "stack.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Convertir prefija a infija
char* convertirPrefijaAInfija(const char* prefija) {
    if (!prefija || strlen(prefija) == 0) {
        return strdup("");
    }
    
    StringStack* pila = createStringStack();
    
    // Leer de derecha a izquierda
    for (int i = strlen(prefija) - 1; i >= 0; i--) {
        // Saltar espacios
        while (i >= 0 && prefija[i] == ' ') i--;
        if (i < 0) break;
        
        char token[2] = {prefija[i], '\0'};
        
        // Si es operando
        if (isalnum(prefija[i])) {
            stringStackPush(pila, token);
        }
        // Si es operador
        else if (esOperador(prefija[i])) {
            if (stringStackSize(pila) < 2) {
                destroyStringStack(pila);
                return strdup("ERROR: Expresión prefija inválida");
            }
            
            char* operando1 = stringStackPop(pila);
            char* operando2 = stringStackPop(pila);
            
            // Crear expresión infija
            char* expresion = (char*)malloc(strlen(operando1) + strlen(operando2) + 4);
            if (!expresion) {
                free(operando1);
                free(operando2);
                destroyStringStack(pila);
                return strdup("ERROR: Memoria insuficiente");
            }
            
            sprintf(expresion, "(%s %c %s)", operando1, prefija[i], operando2);
            stringStackPush(pila, expresion);
            
            free(operando1);
            free(operando2);
            free(expresion);
        }
    }
    
    if (stringStackSize(pila) != 1) {
        destroyStringStack(pila);
        return strdup("ERROR: Expresión prefija inválida");
    }
    
    char* resultado = strdup(stringStackPop(pila));
    destroyStringStack(pila);
    
    return resultado;
}
