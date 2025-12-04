#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Include/stack.h"
#include "../Include/dlist.h"
#include "../Include/parser.h"
#include "../Include/utils.h"
#include "../Include/file_manager.h"
#include "../Include/conversion_infix_postfix.h"
#include "../Include/conversion_infix_prefix.h"
#include "../Include/conversion_postfix_infix.h"
#include "../Include/conversion_postfix_prefix.h"
#include "../Include/conversion_prefix_infix.h"
#include "../Include/conversion_prefix_postfix.h"

// Declaraciones de funciones
void mostrarMenu();
void procesarOpcion(int opcion);
void mostrarCreditos();
void evaluarExpresion();
void analizarExpresionTokens();

// Variables globales
ListaDoble* historial = NULL;

int main() {
    int opcion;
    
    // Inicializaciones
    historial = crearListaDoble();
    
    // Mostrar encabezado
    limpiarPantalla();
    printf("═══════════════════════════════════════════════════════════\n");
    printf("         CALCULADORA DE EXPRESIONES MATEMÁTICAS\n");
    printf("          Con historial en archivo de texto\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    do {
        mostrarMenu();
        printf("\nSeleccione una opcion (0-12): ");
        
        // Leer opción de manera segura
        char input[10];
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &opcion) != 1) {
                printf("Entrada no válida. Intente de nuevo.\n");
                pausar();
                limpiarPantalla();
                continue;
            }
        } else {
            opcion = 0; // Salir si hay error de entrada
        }
        
        procesarOpcion(opcion);
        
        if (opcion != 0) {
            pausar();
            limpiarPantalla();
        }
    } while (opcion != 0);
    
    // Liberar memoria
    if (historial != NULL) {
        destruirListaDoble(historial);
    }
    
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("  Historial guardado en: historial_calculadora.txt\n");
    printf("  ¡Gracias por usar la calculadora! Hasta pronto.\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    return 0;
}

void mostrarMenu() {
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("                     MENÚ PRINCIPAL\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf(" 1. Infija → Postfija\n");
    printf(" 2. Infija → Prefija\n");
    printf(" 3. Postfija → Infija\n");
    printf(" 4. Postfija → Prefija\n");
    printf(" 5. Prefija → Infija\n");
    printf(" 6. Prefija → Postfija\n");
    printf(" 7. Evaluar expresión\n");
    printf(" 8. Analizar expresión (Tokens)\n");
    printf(" 9. Mostrar historial desde archivo\n");
    printf("10. Mostrar estadísticas\n");
    printf("11. Limpiar historial\n");
    printf("12. Créditos\n");
    printf(" 0. Salir\n");
    printf("═══════════════════════════════════════════════════════════\n");
}

void procesarOpcion(int opcion) {
    char expresion[256];
    char* resultado = NULL;
    const char* tipoOperacion = "";
    
    switch (opcion) {
        case 1:
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("               CONVERSIÓN INFIJA → POSTFIJA\n");
            printf("═══════════════════════════════════════════════════════════\n");
            printf("Ejemplos: a+b*c, (a+b)*c, a+b-c*d\n\n");
            printf("Ingrese expresión infija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirInfijaAPostfija(expresion);
            printf("\nResultado postfija: %s\n", resultado);
            tipoOperacion = "INFIJA→POSTFIJA";
            break;
            
        case 2:
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("               CONVERSIÓN INFIJA → PREFIJA\n");
            printf("═══════════════════════════════════════════════════════════\n");
            printf("Ejemplos: a+b*c, (a+b)*c, a+b-c*d\n\n");
            printf("Ingrese expresión infija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirInfijaAPrefija(expresion);
            printf("\nResultado prefija: %s\n", resultado);
            tipoOperacion = "INFIJA→PREFIJA";
            break;
            
        case 3:
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("               CONVERSIÓN POSTFIJA → INFIJA\n");
            printf("═══════════════════════════════════════════════════════════\n");
            printf("Ejemplos: abc*+, ab+c*, abc*+de+*\n\n");
            printf("Ingrese expresión postfija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPostfijaAInfija(expresion);
            printf("\nResultado infija: %s\n", resultado);
            tipoOperacion = "POSTFIJA→INFIJA";
            break;
            
        case 4:
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("               CONVERSIÓN POSTFIJA → PREFIJA\n");
            printf("═══════════════════════════════════════════════════════════\n");
            printf("Ejemplos: abc*+, ab+c*, abc*+de+*\n\n");
            printf("Ingrese expresión postfija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPostfijaAPrefija(expresion);
            printf("\nResultado prefija: %s\n", resultado);
            tipoOperacion = "POSTFIJA→PREFIJA";
            break;
            
        case 5:
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("               CONVERSIÓN PREFIJA → INFIJA\n");
            printf("═══════════════════════════════════════════════════════════\n");
            printf("Ejemplos: +a*bc, *+abc, +-a*bc/de\n\n");
            printf("Ingrese expresión prefija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPrefijaAInfija(expresion);
            printf("\nResultado infija: %s\n", resultado);
            tipoOperacion = "PREFIJA→INFIJA";
            break;
            
        case 6:
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("               CONVERSIÓN PREFIJA → POSTFIJA\n");
            printf("═══════════════════════════════════════════════════════════\n");
            printf("Ejemplos: +a*bc, *+abc, +-a*bc/de\n\n");
            printf("Ingrese expresión prefija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPrefijaAPostfija(expresion);
            printf("\nResultado postfija: %s\n", resultado);
            tipoOperacion = "PREFIJA→POSTFIJA";
            break;
            
        case 7:
            evaluarExpresion();
            break;
            
        case 8:
            analizarExpresionTokens();
            break;
            
        case 9:
            leerHistorial();
            break;
            
        case 10:
            mostrarEstadisticas();
            break;
            
        case 11:
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("                 LIMPIAR HISTORIAL\n");
            printf("═══════════════════════════════════════════════════════════\n");
            printf("¿Está seguro de limpiar todo el historial? (s/n): ");
            char confirmacion;
            scanf("%c", &confirmacion);
            limpiarBuffer();
            if (confirmacion == 's' || confirmacion == 'S') {
                limpiarHistorial();
                printf("✓ Historial limpiado correctamente.\n");
            } else {
                printf("✗ Operación cancelada.\n");
            }
            break;
            
        case 12:
            mostrarCreditos();
            break;
            
        case 0:
            printf("\nSaliendo del programa...\n");
            break;
            
        default:
            printf("\n❌ Opción no válida. Intente de nuevo.\n");
            return;
    }
    
    // GUARDAR EN ARCHIVO DE TEXTO si la operación fue exitosa
    if (resultado != NULL && strlen(resultado) > 0) {
        // Verificar que no sea un mensaje de error
        if (strstr(resultado, "ERROR") == NULL) {
            guardarOperacion(expresion, resultado, tipoOperacion);
        }
        free(resultado);
    }
}

void evaluarExpresion() {
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("                 EVALUACIÓN DE EXPRESIÓN\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Nota: Ingrese expresión con valores numéricos\n");
    printf("Ejemplos: 2+3*4, (5+3)*2, 10/2+3\n\n");
    
    char expresion[256];
    printf("Ingrese expresión a evaluar: ");
    leerCadena(expresion, sizeof(expresion), NULL);
    
    // Por ahora solo guardamos la expresión para evaluación futura
    // En una versión futura se implementará la evaluación real
    guardarResultadoEvaluacion(expresion, 0.0);
    printf("\n✓ Expresión guardada para evaluación futura.\n");
    printf("  (La funcionalidad de evaluación se implementará próximamente)\n");
}

void analizarExpresionTokens() {
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("                ANÁLISIS LÉXICO DE EXPRESIÓN\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("Ejemplos: 2+3*4, a+b*c, (x+y)*z\n\n");
    
    char expresion[256];
    printf("Ingrese expresión: ");
    leerCadena(expresion, sizeof(expresion), NULL);
    
    ListaTokens* tokens = analizarExpresion(expresion);
    if (tokens) {
        mostrarTokens(tokens);
        
        // Validar los tokens
        if (verificarTokens(tokens)) {
            printf("\n✓ Expresión válida\n");
        } else {
            printf("\n✗ Expresión contiene errores\n");
        }
        
        liberarListaTokens(tokens);
    }
}

void mostrarCreditos() {
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("                       CRÉDITOS\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("  Proyecto: Calculadora de Expresiones\n");
    printf("  Desarrollado por: Nadia\n");
    printf("  Materia: Estructuras de Datos\n");
    printf("  Versión: 2.0 (con historial en archivo)\n");
    printf("\n  Características principales:\n");
    printf("  • 6 tipos de conversiones de notación\n");
    printf("  • Historial automático en archivo de texto\n");
    printf("  • Análisis léxico de expresiones\n");
    printf("  • Validación de sintaxis\n");
    printf("  • Estadísticas de uso\n");
    printf("\n  Archivo de historial: historial_calculadora.txt\n");
    printf("═══════════════════════════════════════════════════════════\n");
}
