#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

// Definición de tipos de tokens usando constantes
#define TOKEN_KIND_NUMERO    1   // Número: 123, 45.67
#define TOKEN_KIND_OPERADOR  2   // Operador: + - * / ^
#define TOKEN_KIND_PAR_IZQ   3   // Paréntesis izquierdo: (
#define TOKEN_KIND_PAR_DER   4   // Paréntesis derecho: )
#define TOKEN_KIND_LETRA     5   // Letra: a, b, c, ...
#define TOKEN_KIND_BLANCO    6   // Espacio en blanco
#define TOKEN_KIND_DESCONOCIDO 7 // Carácter no reconocido

// Estructura para un token
typedef struct _Token {
    char* texto;     
    int clase;        
    int lugar;        
    struct _Token* siguiente;
    struct _Token* anterior;
} Token;

// Lista de tokens
typedef struct {
    Token* inicio;
    Token* fin;
    int total;
} ListaTokens;

// Funciones principales
ListaTokens* analizarExpresion(const char* expresion);
void liberarListaTokens(ListaTokens* lista);
void mostrarTokens(const ListaTokens* lista);
int verificarTokens(const ListaTokens* lista);
const char* nombreClaseToken(int clase);

// Funciones de ayuda
int esCaracterOperador(char c);
int esCaracterParentesis(char c);
int esCaracterLetra(char c);
int esCaracterDigito(char c);
int esNumeroValido(const char* str);
int esSignoNegativo(const char* expresion, int pos);

#endif
