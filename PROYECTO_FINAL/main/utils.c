#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int esNumero(char c) {
    return (c >= '0' && c <= '9') || c == '.';
}

int esCaracterOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedencia(char operador) {
    switch (operador) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int esOperadorValido(char c) {
    return esCaracterOperador(c);
}

int esParentesis(char c) {
    return c == '(' || c == ')';
}

void leerCadena(char* buffer, int tamano, const char* mensaje) {
    if (mensaje != NULL) {
        printf("%s", mensaje);
    }
    
    if (fgets(buffer, tamano, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    
    // Eliminar salto de línea
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

void formatearExpresion(char* expresion) {
    int i, j = 0;
    char temp[1000];
    
    for (i = 0; expresion[i] != '\0'; i++) {
        if (expresion[i] != ' ') {
            temp[j++] = expresion[i];
        }
    }
    temp[j] = '\0';
    strcpy(expresion, temp);
}

int validarExpresion(const char* expresion) {
    int parentesis = 0;
    int longitud = strlen(expresion);
    
    if (longitud == 0) return 0;
    
    for (int i = 0; i < longitud; i++) {
        char actual = expresion[i];
        
        if (actual == '(') {
            parentesis++;
        } else if (actual == ')') {
            parentesis--;
            if (parentesis < 0) return 0;
        } else if (esCaracterOperador(actual)) {
            if (i == 0 || i == longitud - 1) return 0;
            if (esCaracterOperador(expresion[i-1]) || expresion[i-1] == '(') return 0;
        }
    }
    
    return parentesis == 0;
}

int contarOperandos(const char* expresion) {
    int count = 0;
    int longitud = strlen(expresion);
    
    for (int i = 0; i < longitud; i++) {
        if (esNumero(expresion[i])) {
            count++;
            while (i < longitud && esNumero(expresion[i])) i++;
            i--;
        } else if (isalpha(expresion[i])) {
            count++;
        }
    }
    
    return count;
}

int contarOperadores(const char* expresion) {
    int count = 0;
    
    for (int i = 0; expresion[i] != '\0'; i++) {
        if (esCaracterOperador(expresion[i])) {
            count++;
        }
    }
    
    return count;
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf("\nPresione Enter para continuar...");
    getchar();
}

// Función faltante
int esNumeroValido(const char* str) {
    if (!str || !*str) return 0;
    
    int punto = 0;
    int digitos = 0;
    
    for (int i = 0; str[i]; i++) {
        if (i == 0 && str[i] == '-') {
            continue; // Signo negativo permitido al inicio
        }
        
        if (str[i] == '.') {
            punto++;
            if (punto > 1) return 0;
        } else if (!isdigit(str[i])) {
            return 0;
        } else {
            digitos++;
        }
    }
    
    return digitos > 0;
}
