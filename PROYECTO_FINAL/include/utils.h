#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <ctype.h>

// Prototipos de funciones esenciales
bool esOperador(char c);
bool esOperando(char c);
int precedencia(char operador);
bool esParentesis(char c);
bool esParentesisApertura(char c);
bool esParentesisCierre(char c);
bool caracteresValidos(const char* expresion);
int contarTokens(const char* expresion);
void trimEspacios(char* str);
bool expresionBalanceada(const char* expresion);
bool esNumero(const char* str);
double convertirADouble(const char* str);
void limpiarBuffer();
int leerEntero(const char* mensaje);
double leerDouble(const char* mensaje);
void leerCadena(char* buffer, int tamano, const char* mensaje);
void mostrarError(const char* mensaje);
void mostrarExito(const char* mensaje);
void pausarPantalla();

#endif
