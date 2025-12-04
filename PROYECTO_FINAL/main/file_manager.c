#include "file_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARCHIVO_HISTORIAL "historial_calculadora.txt"

void guardarOperacion(const char* expresion, const char* resultado, const char* tipo) {
    FILE* archivo = fopen(ARCHIVO_HISTORIAL, "a");
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo de historial\n");
        return;
    }
    
    time_t ahora;
    time(&ahora);
    struct tm* tiempoLocal = localtime(&ahora);
    
    fprintf(archivo, "[%04d-%02d-%02d %02d:%02d:%02d] ",
            tiempoLocal->tm_year + 1900,
            tiempoLocal->tm_mon + 1,
            tiempoLocal->tm_mday,
            tiempoLocal->tm_hour,
            tiempoLocal->tm_min,
            tiempoLocal->tm_sec);
    
    fprintf(archivo, "%s: %s -> %s\n", tipo, expresion, resultado);
    fclose(archivo);
    
    printf("Operacion guardada en el historial\n");
}

// Leer historial completo
void leerHistorial() {
    FILE* archivo = fopen(ARCHIVO_HISTORIAL, "r");
    if (!archivo) {
        printf("No hay historial disponible\n");
        return;
    }
    
    printf("           HISTORIAL DE OPERACIONES\n");
    char linea[256];
    int contador = 1;
    
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%3d. %s", contador++, linea);
    }
    
    if (contador == 1) {
        printf("Historial vacÃ­o\n");
    }
    fclose(archivo);
}

void limpiarHistorial() {
    FILE* archivo = fopen(ARCHIVO_HISTORIAL, "w");
    if (!archivo) {
        printf("Error: No se pudo limpiar el historial\n");
        return;
    }
    
    fclose(archivo);
    printf("Historial limpiado correctamente\n");
}

void guardarResultadoEvaluacion(const char* expresion, double resultado) {
    FILE* archivo = fopen(ARCHIVO_HISTORIAL, "a");
    if (!archivo) return;
    
    time_t ahora;
    time(&ahora);
    struct tm* tiempoLocal = localtime(&ahora);
    
    fprintf(archivo, "[%04d-%02d-%02d %02d:%02d:%02d] ",
            tiempoLocal->tm_year + 1900,
            tiempoLocal->tm_mon + 1,
            tiempoLocal->tm_mday,
            tiempoLocal->tm_hour,
            tiempoLocal->tm_min,
            tiempoLocal->tm_sec);
    
    fprintf(archivo, "EVALUACION: %s = %.4f\n", expresion, resultado);
    fclose(archivo);
}

void mostrarEstadisticas() {
    FILE* archivo = fopen(ARCHIVO_HISTORIAL, "r");
    if (!archivo) {
        printf("No hay estadÃ­sticas disponibles\n");
        return;
    }
    
    int totalOperaciones = 0;
    int conversiones = 0;
    int evaluaciones = 0;
    char linea[256];
    
    while (fgets(linea, sizeof(linea), archivo)) {
        totalOperaciones++;
        if (strstr(linea, "CONVERSACION")) conversiones++;
        if (strstr(linea, "EVALUACION")) evaluaciones++;
    }
    
    fclose(archivo);
    
    printf("            ESTADISTICAS:\n");
    printf("Total de operaciones: %d\n", totalOperaciones);
    printf("Conversiones: %d\n", conversiones);
    printf("Evaluaciones: %d\n", evaluaciones);
}
