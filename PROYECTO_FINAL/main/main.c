#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/utils.h"
#include "include/stack.h"
#include "include/dlist.h"
#include "include/parser.h"

// Declaraciones de funciones (SOLO DECLARACIONES)
void mostrarMenu();
void procesarOpcion(int opcion);
void mostrarEstadisticas();  // SOLO DECLARACIÓN
void limpianHistorical();    // SOLO DECLARACIÓN
void mostrarCreditos();

// Funciones de conversión
char* convertirInfijaAPostfija(const char* infija);
char* convertirInfijaAPrefija(const char* infija);
char* convertirPostfijaAInfija(const char* postfija);
char* convertirPostfijaAPrefija(const char* postfija);
char* convertirPrefijaAInfija(const char* prefija);
char* convertirPrefijaAPostfija(const char* prefija);

// Variables globales (si las hay)
DList* historial = NULL;

int main() {
    int opcion;
    
    // Inicializaciones
    historial = crearDList();
    
    do {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();
        
        if (opcion >= 1 && opcion <= 8) {
            procesarOpcion(opcion);
        } else if (opcion == 9) {
            mostrarEstadisticas();  // LLAMADA A FUNCIÓN EXTERNA
        } else if (opcion == 10) {
            limpianHistorical();    // LLAMADA A FUNCIÓN EXTERNA
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
        // Liberar lista
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
            free(resultado);
            break;
        case 2:
            printf("Ingrese expresion infija: ");
            leerCadena(expresion, sizeof(expresion), NULL);
            resultado = convertirInfijaAPrefija(expresion);
            printf("Resultado prefija: %s\n", resultado);
            free(resultado);
            break;
        // ... otros casos ...
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

