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
    printf("===========================================================\n");
    printf("         CALCULADORA DE EXPRESIONES MATEMATICAS\n");
    printf("          Con historial en archivo de texto\n");
    printf("===========================================================\n");
    
    do {
        mostrarMenu();
        printf("\nSeleccione una opcion (0-12): ");
        
        // Leer opción de manera segura
        char input[10];
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &opcion) != 1) {
                printf("Entrada no valida. Intente de nuevo.\n");
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
    
    printf("\n===========================================================\n");
    printf("  Historial guardado en: historial_calculadora.txt\n");
    printf("  ¡Gracias por usar la calculadora! Hasta pronto.\n");
    printf("===========================================================\n");
    
    return 0;
}

void mostrarMenu() {
    printf("\n===========================================================\n");
    printf("                     MENU PRINCIPAL\n");
    printf("===========================================================\n");
    printf(" 1. Infija -> Postfija\n");
    printf(" 2. Infija -> Prefija\n");
    printf(" 3. Postfija -> Infija\n");
    printf(" 4. Postfija -> Prefija\n");
    printf(" 5. Prefija -> Infija\n");
    printf(" 6. Prefija -> Postfija\n");
    printf(" 7. Evaluar expresion\n");
    printf(" 8. Analizar expresion (Tokens)\n");
    printf(" 9. Mostrar historial desde archivo\n");
    printf("10. Mostrar estadisticas\n");
    printf("11. Limpiar historial\n");
    printf("12. Creditos\n");
    printf(" 0. Salir\n");
    printf("===========================================================\n");
}

void procesarOpcion(int opcion) {
    char expresion[256];
    char* resultado = NULL;
    const char* tipoOperacion = "";
    
    switch (opcion) {
        case 1:
            printf("\n===========================================================\n");
            printf("               CONVERSION INFIJA -> POSTFIJA\n");
            printf("===========================================================\n");
            printf("Ejemplos: a+b*c, (a+b)*c, a+b-c*d\n\n");
            printf("Ingrese expresion infija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirInfijaAPostfija(expresion);
            printf("\nResultado postfija: %s\n", resultado);
            tipoOperacion = "INFIJAPOSTFIJA";
            break;
            
        case 2:
            printf("\n===========================================================\n");
            printf("               CONVERSION INFIJA -> PREFIJA\n");
            printf("===========================================================\n");
            printf("Ejemplos: a+b*c, (a+b)*c, a+b-c*d\n\n");
            printf("Ingrese expresion infija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirInfijaAPrefija(expresion);
            printf("\nResultado prefija: %s\n", resultado);
            tipoOperacion = "INFIJAPREFIJA";
            break;
            
        case 3:
            printf("\n===========================================================\n");
            printf("               CONVERSION POSTFIJA -> INFIJA\n");
            printf("===========================================================\n");
            printf("Ejemplos: abc*+, ab+c*, abc*+de+*\n\n");
            printf("Ingrese expresion postfija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPostfijaAInfija(expresion);
            printf("\nResultado infija: %s\n", resultado);
            tipoOperacion = "POSTFIJAINFIJA";
            break;
            
        case 4:
            printf("\n===========================================================\n");
            printf("               CONVERSION POSTFIJA -> PREFIJA\n");
            printf("===========================================================\n");
            printf("Ejemplos: abc*+, ab+c*, abc*+de+*\n\n");
            printf("Ingrese expresion postfija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPostfijaAPrefija(expresion);
            printf("\nResultado prefija: %s\n", resultado);
            tipoOperacion = "POSTFIJAPREFIJA";
            break;
            
        case 5:
            printf("\n===========================================================\n");
            printf("               CONVERSION PREFIJA -> INFIJA\n");
            printf("===========================================================\n");
            printf("Ejemplos: +a*bc, *+abc, +-a*bc/de\n\n");
            printf("Ingrese expresion prefija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPrefijaAInfija(expresion);
            printf("\nResultado infija: %s\n", resultado);
            tipoOperacion = "PREFIJAINFIJA";
            break;
            
        case 6:
            printf("\n===========================================================\n");
            printf("               CONVERSION PREFIJA -> POSTFIJA\n");
            printf("===========================================================\n");
            printf("Ejemplos: +a*bc, *+abc, +-a*bc/de\n\n");
            printf("Ingrese expresion prefija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPrefijaAPostfija(expresion);
            printf("\nResultado postfija: %s\n", resultado);
            tipoOperacion = "PREFIJAPOSTFIJA";
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
            printf("\n===========================================================\n");
            printf("                 LIMPIAR HISTORIAL\n");
            printf("===========================================================\n");
            printf("¿Esta seguro de limpiar todo el historial? (s/n): ");
            char confirmacion;
            scanf("%c", &confirmacion);
            limpiarBuffer();
            if (confirmacion == 's' || confirmacion == 'S') {
                limpiarHistorial();
                printf("OK - Historial limpiado correctamente.\n");
            } else {
                printf("X - Operacion cancelada.\n");
            }
            break;
            
        case 12:
            mostrarCreditos();
            break;
            
        case 0:
            printf("\nSaliendo del programa...\n");
            break;
            
        default:
            printf("\nERROR - Opcion no valida. Intente de nuevo.\n");
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
    printf("\n===========================================================\n");
    printf("                 EVALUACION DE EXPRESION\n");
    printf("===========================================================\n");
    printf("Nota: Ingrese expresion con valores numericos\n");
    printf("Ejemplos: 2+3*4, (5+3)*2, 10/2+3\n\n");
    
    char expresion[256];
    printf("Ingrese expresion a evaluar: ");
    leerCadena(expresion, sizeof(expresion), NULL);
    
    // Por ahora solo guardamos la expresión para evaluación futura
    guardarResultadoEvaluacion(expresion, 0.0);
    printf("\nOK - Expresion guardada para evaluacion futura.\n");
    printf("  (La funcionalidad de evaluacion se implementara proximamente)\n");
}

void analizarExpresionTokens() {
    printf("\n===========================================================\n");
    printf("                ANALISIS LEXICO DE EXPRESION\n");
    printf("===========================================================\n");
    printf("Ejemplos: 2+3*4, a+b*c, (x+y)*z\n\n");
    
    char expresion[256];
    printf("Ingrese expresion: ");
    leerCadena(expresion, sizeof(expresion), NULL);
    
    ListaTokens* tokens = analizarExpresion(expresion);
    if (tokens) {
        mostrarTokens(tokens);
        
        // Validar los tokens
        if (verificarTokens(tokens)) {
            printf("\nOK - Expresion valida\n");
        } else {
            printf("\nERROR - Expresion contiene errores\n");
        }
        
        liberarListaTokens(tokens);
    }
}

void mostrarCreditos() {
    printf("\n===========================================================\n");
    printf("                       CREDITOS\n");
    printf("===========================================================\n");
    printf("  Proyecto: Calculadora de Expresiones\n");
    printf("  Desarrollado por: Nadia\n");
    printf("  Materia: Estructuras de Datos\n");
    printf("  Version: 2.0 (con historial en archivo)\n");
    printf("\n  Caracteristicas principales:\n");
    printf("  • 6 tipos de conversiones de notacion\n");
    printf("  • Historial automatico en archivo de texto\n");
    printf("  • Analisis lexico de expresiones\n");
    printf("  • Validacion de sintaxis\n");
    printf("  • Estadisticas de uso\n");
    printf("\n  Archivo de historial: historial_calculadora.txt\n");
    printf("===========================================================\n");
}
