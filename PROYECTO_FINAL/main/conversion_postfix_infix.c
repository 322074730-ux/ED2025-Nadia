#include "conversion_postfix_infix.h"
#include "stack.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Convertir postfija a infija
char* convertirPostfijaAInfija(const char* postfija) {
    if (!postfija || strlen(postfija) == 0) {
        return strdup("");
    }
    
    StringStack* pila = createStringStack();
    
    for (int i = 0; postfija[i] != '\0'; i++) {
        // Saltar espacios
        while (postfija[i] == ' ') i++;
        if (postfija[i] == '\0') break;
        
        char token[2] = {postfija[i], '\0'};
        
        // Si es operando
        if (isalnum(postfija[i])) {
            stringStackPush(pila, token);
        }
        // Si es operador
        else if (esOperador(postfija[i])) {
            if (stringStackSize(pila) < 2) {
                destroyStringStack(pila);
                return strdup("ERROR: Expresión postfija inválida");
            }
            
            char* operando2 = stringStackPop(pila);
            char* operando1 = stringStackPop(pila);
            
            // Crear expresión infija con paréntesis
            char* expresion = (char*)malloc(strlen(operando1) + strlen(operando2) + 4);
            if (!expresion) {
                free(operando1);
                free(operando2);
                destroyStringStack(pila);
                return strdup("ERROR: Memoria insuficiente");
            }
            
            sprintf(expresion, "(%s %c %s)", operando1, postfija[i], operando2);
            stringStackPush(pila, expresion);
            
            free(operando1);
            free(operando2);
            free(expresion);
        }
    }
    
    if (stringStackSize(pila) != 1) {
        destroyStringStack(pila);
        return strdup("ERROR: Expresión postfija inválida");
    }
    
    char* resultado = strdup(stringStackPop(pila));
    destroyStringStack(pila);
    
    return resultado;
}
