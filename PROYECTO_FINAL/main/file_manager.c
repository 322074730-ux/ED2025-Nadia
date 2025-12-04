#include "file_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARCHIVO_HISTORIAL "historial_calculadora.txt"

// Guardar operación en archivo
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
    
    printf("✓ Operación guardada en el historial\n");
}

// Leer historial completo
void leerHistorial() {
    FILE* archivo = fopen(ARCHIVO_HISTORIAL, "r");
    if (!archivo) {
        printf("No hay historial disponible\n");
        return;
    }
    
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("                  HISTORIAL DE OPERACIONES\n");
    printf("═══════════════════════════════════════════════════════════\n\n");
    
    char linea[256];
    int contador = 1;
    
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%3d. %s", contador++, linea);
    }
    
    if (contador == 1) {
        printf("               Historial vacío\n");
    }
    
    printf("═══════════════════════════════════════════════════════════\n");
    fclose(archivo);
}

// Limpiar historial
void limpiarHistorial() {
    FILE* archivo = fopen(ARCHIVO_HISTORIAL, "w");
    if (!archivo) {
        printf("Error: No se pudo limpiar el historial\n");
        return;
    }
    
    fclose(archivo);
    printf("Historial limpiado correctamente\n");
}

// Guardar resultado de evaluación
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
    
    fprintf(archivo, "EVALUACIÓN: %s = %.4f\n", expresion, resultado);
    fclose(archivo);
    
    printf("✓ Evaluación guardada en el historial\n");
}

// Mostrar estadísticas del historial
void mostrarEstadisticas() {
    FILE* archivo = fopen(ARCHIVO_HISTORIAL, "r");
    if (!archivo) {
        printf("No hay estadísticas disponibles\n");
        return;
    }
    
    int totalOperaciones = 0;
    int conversiones = 0;
    int evaluaciones = 0;
    int infijaPostfija = 0, infijaPrefija = 0, postfijaInfija = 0;
    int postfijaPrefija = 0, prefijaInfija = 0, prefijaPostfija = 0;
    char linea[256];
    
    while (fgets(linea, sizeof(linea), archivo)) {
        totalOperaciones++;
        
        if (strstr(linea, "INFIJA→POSTFIJA")) infijaPostfija++;
        else if (strstr(linea, "INFIJA→PREFIJA")) infijaPrefija++;
        else if (strstr(linea, "POSTFIJA→INFIJA")) postfijaInfija++;
        else if (strstr(linea, "POSTFIJA→PREFIJA")) postfijaPrefija++;
        else if (strstr(linea, "PREFIJA→INFIJA")) prefijaInfija++;
        else if (strstr(linea, "PREFIJA→POSTFIJA")) prefijaPostfija++;
        else if (strstr(linea, "EVALUACIÓN")) evaluaciones++;
        
        if (strstr(linea, "→")) conversiones++;
    }
    
    fclose(archivo);
    
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("                     ESTADÍSTICAS\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Total de operaciones: %d\n", totalOperaciones);
    printf("\n--- CONVERSIONES (%d) ---\n", conversiones);
    printf("  Infija → Postfija:    %d\n", infijaPostfija);
    printf("  Infija → Prefija:     %d\n", infijaPrefija);
    printf("  Postfija → Infija:    %d\n", postfijaInfija);
    printf("  Postfija → Prefija:   %d\n", postfijaPrefija);
    printf("  Prefija → Infija:     %d\n", prefijaInfija);
    printf("  Prefija → Postfija:   %d\n", prefijaPostfija);
    printf("\n--- EVALUACIONES (%d) ---\n", evaluaciones);
    printf("═══════════════════════════════════════════════════════════\n");
}
