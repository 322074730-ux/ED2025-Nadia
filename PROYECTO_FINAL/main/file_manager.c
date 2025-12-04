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
    
    printf("OK - Operacion guardada en el historial\n");
}

// Leer historial completo
void leerHistorial() {
    FILE* archivo = fopen(ARCHIVO_HISTORIAL, "r");
    if (!archivo) {
        printf("No hay historial disponible\n");
        return;
    }
    
    printf("\n===========================================================\n");
    printf("                  HISTORIAL DE OPERACIONES\n");
    printf("===========================================================\n\n");
    
    char linea[256];
    int contador = 1;
    
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%3d. %s", contador++, linea);
    }
    
    if (contador == 1) {
        printf("               Historial vacio\n");
    }
    
    printf("===========================================================\n");
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
    printf("OK - Historial limpiado correctamente\n");
}

// Guardar resultado de evaluación
void guardarResultadoEvaluacion(const char* expresion, double resultado) {
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
    
    if (resultado == 0.0) {
        fprintf(archivo, "EVALUACION (PENDIENTE): %s\n", expresion);
    } else {
        fprintf(archivo, "EVALUACION: %s = %.4f\n", expresion, resultado);
    }
    
    fclose(archivo);
    
    printf("OK - Evaluacion guardada en el historial\n");
}

// Mostrar estadísticas del historial
void mostrarEstadisticas() {
    FILE* archivo = fopen(ARCHIVO_HISTORIAL, "r");
    if (!archivo) {
        printf("No hay estadisticas disponibles\n");
        return;
    }
    
    int totalOperaciones = 0;
    int conversiones = 0;
    int evaluaciones = 0;
    int infijaPostfija = 0, infijaPrefija = 0, postfijaInfija = 0;
    int postfijaPrefija = 0, prefijaInfija = 0, prefijaPostfija = 0;
    int evaluacionesPendientes = 0;
    char linea[256];
    
    while (fgets(linea, sizeof(linea), archivo)) {
        totalOperaciones++;
        
        if (strstr(linea, "INFIJAPOSTFIJA:")) infijaPostfija++;
        else if (strstr(linea, "INFIJAPREFIJA:")) infijaPrefija++;
        else if (strstr(linea, "POSTFIJAINFIJA:")) postfijaInfija++;
        else if (strstr(linea, "POSTFIJAPREFIJA:")) postfijaPrefija++;
        else if (strstr(linea, "PREFIJAINFIJA:")) prefijaInfija++;
        else if (strstr(linea, "PREFIJAPOSTFIJA:")) prefijaPostfija++;
        else if (strstr(linea, "EVALUACION:")) {
            evaluaciones++;
            if (strstr(linea, "(PENDIENTE)")) evaluacionesPendientes++;
        }
        
        // Contar conversiones (todas las que no son evaluaciones)
        if (strstr(linea, "INFIJAPOSTFIJA:") || strstr(linea, "INFIJAPREFIJA:") ||
            strstr(linea, "POSTFIJAINFIJA:") || strstr(linea, "POSTFIJAPREFIJA:") ||
            strstr(linea, "PREFIJAINFIJA:") || strstr(linea, "PREFIJAPOSTFIJA:")) {
            conversiones++;
        }
    }
    
    fclose(archivo);
    
    printf("\n===========================================================\n");
    printf("                     ESTADISTICAS\n");
    printf("===========================================================\n");
    printf("Total de operaciones: %d\n", totalOperaciones);
    
    if (conversiones > 0) {
        printf("\n--- CONVERSIONES (%d) ---\n", conversiones);
        if (infijaPostfija > 0) printf("  Infija -> Postfija:    %d\n", infijaPostfija);
        if (infijaPrefija > 0) printf("  Infija -> Prefija:     %d\n", infijaPrefija);
        if (postfijaInfija > 0) printf("  Postfija -> Infija:    %d\n", postfijaInfija);
        if (postfijaPrefija > 0) printf("  Postfija -> Prefija:   %d\n", postfijaPrefija);
        if (prefijaInfija > 0) printf("  Prefija -> Infija:     %d\n", prefijaInfija);
        if (prefijaPostfija > 0) printf("  Prefija -> Postfija:   %d\n", prefijaPostfija);
    }
    
    if (evaluaciones > 0) {
        printf("\n--- EVALUACIONES (%d) ---\n", evaluaciones);
        printf("  Completadas:          %d\n", evaluaciones - evaluacionesPendientes);
        printf("  Pendientes:           %d\n", evaluacionesPendientes);
    }
    
    printf("\n--- ARCHIVO ---\n");
    printf("  Nombre:               historial_calculadora.txt\n");
    
    // Verificar tamaño del archivo (SIN Ñ)
    archivo = fopen(ARCHIVO_HISTORIAL, "r");
    if (archivo) {
        fseek(archivo, 0, SEEK_END);
        long tamano = ftell(archivo);  // <--- CAMBIÉ "tamaño" por "tamano"
        fclose(archivo);
        printf("  Tamano:               %ld bytes\n", tamano);  // <--- SIN Ñ
    }
    
    printf("===========================================================\n");
}
