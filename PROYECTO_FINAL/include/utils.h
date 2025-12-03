#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Prototipos de funciones
void limpiarBuffer();
int esNumero(char c);
int esCaracterOperador(char c);
int precedencia(char operador);
int esOperadorValido(char c);
int esParentesis(char c);
void leerCadena(char* buffer, int tamano, const char* mensaje);
void formatearExpresion(char* expresion);
int validarExpresion(const char* expresion);
int contarOperandos(const char* expresion);
int contarOperadores(const char* expresion);
void limpiarPantalla();
void pausar();

#endif // UTILS_H
