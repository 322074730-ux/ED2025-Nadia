#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Include/stack.h"
#include "../Include/parser.h"
#include "../Include/utils.h"

int obtenerPrecedencia(char operador) {
    switch (operador) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}
char* convertirInfijaAPostfija(const char* infija){
    if (!infija || strlen(infija)==0){
        return strdup("");
    }
    CharStack* pila = createCharStack();
    if (!pila) return strdup("ERROR: No se pudo crear la pila");
    char* resultado = (char*)malloc(strlen(infija) * 3 + 1);
    if (!resultado) {
        destroyCharStack(pila);
        return strdup("ERROR: Memoria insuficiente");
    }
    
    int indice=0;
    for (int i=0; infija[i] != '\0'; i++) {
        char actual=infija[i];
        
        if (actual==' ') continue;
    
        if (isalnum(actual)){
            resultado[indice++]=actual;
            resultado[indice++] = ' ';
        }
        else if (actual == '(') {
            charStackPush(pila, actual);
        }
        else if (actual == ')') {
            while (!charStackIsEmpty(pila) && charStackPeek(pila) != '(') {
                resultado[indice++] = charStackPop(pila);
                resultado[indice++] = ' ';
            }
            if (!charStackIsEmpty(pila) && charStackPeek(pila) == '(') {
                charStackPop(pila); // Eliminar '('
            }
        }
        else if (esCaracterOperador(actual)) {
            while (!charStackIsEmpty(pila) && 
                   obtenerPrecedencia(charStackPeek(pila)) >= obtenerPrecedencia(actual) &&
                   actual != '^') { // ^ es asociativo derecho
                resultado[indice++] = charStackPop(pila);
                resultado[indice++] = ' ';
            }
            charStackPush(pila, actual);
        }
    }
    
    // Vaciar pila restante
    while (!charStackIsEmpty(pila)) {
        resultado[indice++] = charStackPop(pila);
        resultado[indice++] = ' ';
    }
    
    if (indice > 0 && resultado[indice-1] == ' ') {
        resultado[indice-1] = '\0';
    } else {
        resultado[indice] = '\0';
    }
    destroyCharStack(pila);
    return resultado;
}
