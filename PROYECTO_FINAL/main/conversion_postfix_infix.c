#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Include/stack.h"
#include "../Include/utils.h"

// Declaración explícita para evitar warning
int esCaracterOperador(char c);

// Definición de Stack para este archivo (diferente de la pila de cadenas)
typedef struct {
    char** items;
    int top;
    int capacity;
} Stack;

// CAMBIO: Todas las funciones de Stack son static
static Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->items = (char**)malloc(capacity * sizeof(char*));
    return stack;
}

static void destroyStack(Stack* stack) {
    if (stack) {
        for (int i = 0; i <= stack->top; i++) {
            free(stack->items[i]);
        }
        free(stack->items);
        free(stack);
    }
}

static int isEmpty(Stack* stack) {
    return stack->top == -1;
}

static void push(Stack* stack, char* item) {
    if (stack->top < stack->capacity - 1) {
        stack->items[++stack->top] = strdup(item);
    }
}

static char* pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->items[stack->top--];
    }
    return NULL;
}

char* convertirPostfijaAInfija(const char* postfija) {
    int len = strlen(postfija);
    Stack* stack = createStack(len);
    char* resultado = NULL;
    
    for (int i = 0; postfija[i] != '\0'; i++) {
        if (esNumero(postfija[i]) || isalpha(postfija[i])) {
            char* operando = (char*)malloc(2 * sizeof(char));
            operando[0] = postfija[i];
            operando[1] = '\0';
            push(stack, operando);
            free(operando);
        } else if (esCaracterOperador(postfija[i])) {
            if (stack->top < 1) {
                // Error
                destroyStack(stack);
                return strdup("ERROR: Expresion postfija invalida");
            }
            
            char* op2 = pop(stack);
            char* op1 = pop(stack);
            
            // +4 para parentesis, operador y null terminator
            int exp_len = strlen(op1) + strlen(op2) + 4;
            char* expresion = (char*)malloc(exp_len);
            sprintf(expresion, "(%s%c%s)", op1, postfija[i], op2);
            
            push(stack, expresion);
            free(op1);
            free(op2);
            free(expresion);
        }
    }
    
    if (!isEmpty(stack)) {
        resultado = strdup(pop(stack));
    } else {
        resultado = strdup("");
    }
    
    // Limpiar pila restante
    while (!isEmpty(stack)) {
        char* temp = pop(stack);
        free(temp);
    }
    
    destroyStack(stack);
    return resultado;
}
