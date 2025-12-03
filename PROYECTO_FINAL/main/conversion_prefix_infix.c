#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/stack.h"
#include "include/utils.h"

// Declaración explícita para evitar warning
int esCaracterOperador(char c);

char* convertirPrefijaAInfija(const char* prefija) {
    int len = strlen(prefija);
    Stack* stack = createStack(len);
    char* resultado = NULL;
    
    for (int i = len - 1; i >= 0; i--) {
        if (esNumero(prefija[i]) || isalpha(prefija[i])) {
            char* operando = (char*)malloc(2 * sizeof(char));
            operando[0] = prefija[i];
            operando[1] = '\0';
            push(stack, operando);
        } else if (esCaracterOperador(prefija[i])) {
            if (stack->top < 1) {
                // Error
                return NULL;
            }
            
            char* op1 = pop(stack);
            char* op2 = pop(stack);
            
            char* expresion = (char*)malloc(strlen(op1) + strlen(op2) + 4);
            sprintf(expresion, "(%s%c%s)", op1, prefija[i], op2);
            
            push(stack, expresion);
            free(op1);
            free(op2);
        }
    }
    
    if (!isEmpty(stack)) {
        resultado = strdup(pop(stack));
    }
    
    destroyStack(stack);
    return resultado;
}
