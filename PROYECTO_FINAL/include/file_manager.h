#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

// Funciones de manejo de archivos
void guardarOperacion(const char* expresion, const char* resultado, const char* tipo);
void leerHistorial();
void limpiarHistorial();
void guardarResultadoEvaluacion(const char* expresion, double resultado);
void mostrarEstadisticas();

#endif
