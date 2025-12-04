#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Include/stack.h"
#include "../Include/dlist.h"
#include "../Include/parser.h"
#include "../Include/utils.h"
#include "../Include/file_manager.h"

// Declaraciones de funciones (SOLO DECLARACIONES)
void mostrarMenu();
void procesarOpcion(int opcion);
void mostrarCreditos();

// Funciones de conversión (declaraciones)
char* convertirInfijaAPostfija(const char* infija);
char* convertirInfijaAPrefija(const char* infija);
char* convertirPostfijaAInfija(const char* postfija);
char* convertirPostfijaAPrefija(const char* postfija);
char* convertirPrefijaAInfija(const char* prefija);
char* convertirPrefijaAPostfija(const char* prefija);

// Variables globales
ListaDoble* historial = NULL;

int main() {
    int opcion;
    
    // Inicializaciones
    historial = crearListaDoble();
    
    do {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();
        
        if (opcion >= 1 && opcion <= 8) {
            procesarOpcion(opcion);
        } else if (opcion == 9) {
            mostrarEstadisticas();
        } else if (opcion == 10) {
            limpiarHistorial();
        } else if (opcion == 11) {
            mostrarCreditos();
        } else if (opcion != 0) {
            printf("Opcion no valida. Intente de nuevo.\n");
        }
        
        if (opcion != 0) {
            pausar();
            limpiarPantalla();
        }
    } while (opcion != 0);
    
    // Liberar memoria
    if (historial != NULL) {
        destruirListaDoble(historial);
    }
    
    printf("Gracias por usar la calculadora. ¡Hasta pronto!\n");
    return 0;
}

void mostrarMenu() {
    printf("=========================================\n");
    printf("        CALCULADORA DE EXPRESIONES       \n");
    printf("=========================================\n");
    printf("1. Infija a Postfija\n");
    printf("2. Infija a Prefija\n");
    printf("3. Postfija a Infija\n");
    printf("4. Postfija a Prefija\n");
    printf("5. Prefija a Infija\n");
    printf("6. Prefija a Postfija\n");
    printf("7. Evaluar expresion\n");
    printf("8. Mostrar historial\n");
    printf("9. Mostrar estadisticas\n");
    printf("10. Limpiar historial\n");
    printf("11. Creditos\n");
    printf("0. Salir\n");
    printf("=========================================\n");
}

void procesarOpcion(int opcion) {
    char expresion[100];
    char* resultado;
    
    switch (opcion) {
        case 1:
            printf("Ingrese expresion infija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirInfijaAPostfija(expresion);
            printf("Resultado postfija: %s\n", resultado);
            // GUARDAR EN HISTORIAL
            guardarOperacion(expresion, resultado, "INF->POST");
            if (resultado) free(resultado);
            break;
        case 2:
            printf("Ingrese expresion infija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirInfijaAPrefija(expresion);
            printf("Resultado prefija: %s\n", resultado);
            // GUARDAR EN HISTORIAL
            guardarOperacion(expresion, resultado, "INF->PRE");
            if (resultado) free(resultado);
            break;
        case 3:
            printf("Ingrese expresion postfija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPostfijaAInfija(expresion);
            printf("Resultado infija: %s\n", resultado);
            // GUARDAR EN HISTORIAL
            guardarOperacion(expresion, resultado, "POST->INF");
            if (resultado) free(resultado);
            break;
        case 4:
            printf("Ingrese expresion postfija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPostfijaAPrefija(expresion);
            printf("Resultado prefija: %s\n", resultado);
            // GUARDAR EN HISTORIAL
            guardarOperacion(expresion, resultado, "POST->PRE");
            if (resultado) free(resultado);
            break;
        case 5:
            printf("Ingrese expresion prefija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPrefijaAInfija(expresion);
            printf("Resultado infija: %s\n", resultado);
            // GUARDAR EN HISTORIAL
            guardarOperacion(expresion, resultado, "PRE->INF");
            if (resultado) free(resultado);
            break;
        case 6:
            printf("Ingrese expresion prefija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirPrefijaAPostfija(expresion);
            printf("Resultado postfija: %s\n", resultado);
            // GUARDAR EN HISTORIAL
            guardarOperacion(expresion, resultado, "PRE->POST");
            if (resultado) free(resultado);
            break;
        case 7:
            printf("Funcionalidad de evaluacion no implementada aun.\n");
            break;
        case 8:
            leerHistorial();
            break;
        case 9:
            mostrarEstadisticas();
            break;
        case 10:
            limpiarHistorial();
            break;
        case 11:
            mostrarCreditos();
            break;
        default:
            printf("Opcion no implementada.\n");
            break;
    }
}

void mostrarCreditos() {
    printf("=========================================\n");
    printf("              CREDITOS                   \n");
    printf("=========================================\n");
    printf("Desarrollado por: [Tu Nombre]\n");
    printf("Materia: Estructuras de Datos\n");
    printf("Version: 1.0\n");
    printf("=========================================\n");
}
