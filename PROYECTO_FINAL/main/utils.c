#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Verificar si un caracter es operador
bool esOperador(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
// Verificar si es un operando (letra o digito)
bool esOperando(char c){
    return (isalnum(c) != 0);
}
// Obtener precedencia de operador
int precedencia(char operador){
    switch (operador){
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
// Verificar si es paréntesis
bool esParentesis(char c){
    return (c == '(' || c == ')');
}

// Verificar si es paréntesis de apertura
bool esParentesisApertura(char c){
    return (c == '(');
}
// Verificar si es paréntesis de cierre
bool esParentesisCierre(char c) {
    return (c == ')');
}
// Validar caracteres en la expresión
bool caracteresValidos(const char* expresion){
    for (int i=0; expresion[i] != '\0'; i++){
        char c=expresion[i];
        if (!esOperando(c) && !esOperador(c) && !esParentesis(c) && c != ' ' && c != '.'){
            return false;
        }
    }
    return true;
}
// Contar tokens en la expresión
int contarTokens(const char* expresion){
    int count=0;
    int i=0;
    int len=strlen(expresion);
    
    while (i<len){
        // Saltar espacios
        while (i<len && expresion[i] == ' '){
            i++;
        }
        if (i<len){
            count++;
            
            // Si es operando 
            if (esOperando(expresion[i])){
                while (i < len && (esOperando(expresion[i]) || expresion[i] == '.')){
                    i++;
                }
            }
            // Si es operador o parentesis
            else if (esOperador(expresion[i]) || esParentesis(expresion[i])){
                i++;
            }
        }
    }
    return count;
}
// Eliminar espacios al principio y final
void trimEspacios(char* str){
    int i=0, j=0;
    
    // Eliminar espacios al inicio
    while (str[i]==' '){
        i++;
    }
    // Mover caracteres
    while (str[i] != '\0') {
        if (str[i] != ' ' || (str[i] == ' ' && str[i+1] != ' ' && str[i+1] != '\0')){
            str[j]=str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
    // Eliminar espacio final si existe
    if (j>0 && str[j-1] == ' '){
        str[j-1] = '\0';
    }
}
// Verificar si la expresión tiene paréntesis balanceados
bool expresionBalanceada(const char* expresion){
    int balance = 0;
    
    for (int i = 0; expresion[i] != '\0'; i++){
        if (expresion[i] == '('){
            balance++;
        } else if (expresion[i] == ')'){
            balance--;
            if (balance<0){
                return false;
            }
        }
    }
    return (balance == 0);
}
// Verificar si una cadena es un número válido
bool esNumero(const char* str){
    if (str == NULL || *str == '\0'){
        return false;
    }   
    int puntoDecimal=0;
    for (int i=0; str[i] != '\0'; i++){
        if (i==0 && str[i] == '-') {
            continue;
        }
        if (str[i] == '.') {
            puntoDecimal++;
            if (puntoDecimal>1) {
                return false;
            }
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
// Convertir cadena a double
double convertirADouble(const char* str){
    return atof(str);
}
// Limpiar buffer de entrada
void limpiarBuffer(){
    int c;
    while ((c=getchar()) != '\n' && c != EOF);
}
// Leer un entero con mensaje
int leerEntero(const char* mensaje) {
    int valor;
    printf("%s", mensaje);
    scanf("%d", &valor);
    limpiarBuffer();
    return valor;
}
// Leer un double con mensaje
double leerDouble(const char* mensaje) {
    double valor;
    printf("%s", mensaje);
    scanf("%lf", &valor);
    limpiarBuffer();
    return valor;
}
void leerCadena(char* buffer, int tamaño, const char* mensaje) {
    printf("%s", mensaje);
    fgets(buffer, tamaño, stdin);
    // Eliminar salto de línea
    size_t len = strlen(buffer);
    if (len>0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}
void mostrarError(const char* mensaje) {
    printf("\n ERROR: %s\n", mensaje);
}
void mostrarExito(const char* mensaje) {
    printf("\n %s\n", mensaje);
}
void pausarPantalla() {
    printf("\nPresiona Enter para continuar...");
    limpiarBuffer();
    getchar();
}
