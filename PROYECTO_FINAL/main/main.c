#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "stack.h"
#include "dlist.h"
#include "utils.h"
#include "parser.h"
#include "file_manager.h"
#include "conversion_infix_postfix.h"
#include "conversion_infix_prefix.h"
#include "conversion_postfix_infix.h"
#include "conversion_postfix_prefix.h"
#include "conversion_prefix_infix.h"
#include "conversion_prefix_postfix.h"

#define MAX_EXPRESION 200
#define VERSION "1.0.0"
#define AUTOR "Calculadora de Expresiones"

// Prototipos de funciones
void mostrarAyuda();
void mostrarBienvenida();
void limpiarPantalla();
void mostrarMenuPrincipal();
void procesarOpcion(int opcion);
void evaluarExpresionInfija();
void evaluarExpresionPostfija();
void evaluarExpresionPrefija();
void evaluarPasoAPaso();
void mostrarHistorial();
void mostrarEstadisticas();
void limpiarHistorial();
void salirPrograma();
double calcularExpresionInfija(const char* expresion);
double calcularExpresionPostfija(const char* expresion);
double calcularExpresionPrefija(const char* expresion);

// Variables globales
int ejecutando = 1;

// Función principal
int main(int argc, char* argv[]) {
    // Verificar argumentos de línea de comandos
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            mostrarAyuda();
            return 0;
        }
        else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
            printf("Calculadora de Expresiones v%s\n", VERSION);
            return 0;
        }
        else if (strcmp(argv[1], "-e") == 0 && argc > 2) {
            // Modo evaluación rápida
            char* resultado = convertirInfijaAPostfija(argv[2]);
            printf("Postfija: %s\n", resultado);
            free(resultado);
            return 0;
        }
    }
    
    mostrarBienvenida();
    
    while (ejecutando) {
        mostrarMenuPrincipal();
        
        char entrada[10];
        printf("\nSeleccione una opción: ");
        fgets(entrada, sizeof(entrada), stdin);
        
        int opcion;
        if (sscanf(entrada, "%d", &opcion) != 1) {
            printf("Opción no válida. Intente de nuevo.\n");
            continue;
        }
        
        procesarOpcion(opcion);
    }
    
    return 0;
}

// Mostrar ayuda completa
void mostrarAyuda() {
    printf("\n═══════════════════════════════════════\n");
    printf("        AYUDA - CALCULADORA DE EXPRESIONES\n");
    printf("═══════════════════════════════════════\n\n");
    
    printf("USO:\n");
    printf("  ./calc [OPCIONES]\n\n");
    
    printf("OPCIONES:\n");
    printf("  -h, --help      Mostrar esta ayuda\n");
    printf("  -v, --version   Mostrar versión del programa\n");
    printf("  -e EXPRESIÓN    Evaluar expresión rápidamente\n\n");
    
    printf("EJEMPLOS:\n");
    printf("  ./calc                    Modo interactivo\n");
    printf("  ./calc -h                 Mostrar ayuda\n");
    printf("  ./calc -e \"(3+4)*5\"       Evaluar expresión\n\n");
    
    printf("NOTACIÓN SOPORTADA:\n");
    printf("  Infija:    (a + b) * c\n");
    printf("  Postfija:  a b + c *\n");
    printf("  Prefija:   * + a b c\n\n");
    
    printf("OPERADORES:\n");
    printf("  +   Suma\n");
    printf("  -   Resta\n");
    printf("  *   Multiplicación\n");
    printf("  /   División\n");
    printf("  ^   Potencia\n");
    printf("  ( ) Paréntesis\n\n");
    
    printf("EJEMPLOS DE EXPRESIONES:\n");
    printf("  Infija:    (3+4)*5-2/1\n");
    printf("  Postfija:  3 4 + 5 * 2 1 / -\n");
    printf("  Prefija:   - * + 3 4 5 / 2 1\n");
    printf("═══════════════════════════════════════\n");
}

// Mostrar pantalla de bienvenida
void mostrarBienvenida() {
    limpiarPantalla();
    printf("═══════════════════════════════════════\n");
    printf("   CALCULADORA DE EXPRESIONES %s\n", VERSION);
    printf("═══════════════════════════════════════\n");
    printf("  Convertir y evaluar expresiones en:\n");
    printf("    • Notación Infija\n");
    printf("    • Notación Postfija\n");
    printf("    • Notación Prefija\n");
    printf("═══════════════════════════════════════\n\n");
}

// Limpiar pantalla (portable)
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Mostrar menú principal
void mostrarMenuPrincipal() {
    printf("\n═══════════════════════════════════════\n");
    printf("            MENÚ PRINCIPAL\n");
    printf("═══════════════════════════════════════\n");
    printf(" 1. Infija → Postfija\n");
    printf(" 2. Infija → Prefija\n");
    printf(" 3. Postfija → Infija\n");
    printf(" 4. Postfija → Prefija\n");
    printf(" 5. Prefija → Infija\n");
    printf(" 6. Prefija → Postfija\n");
    printf("═══════════════════════════════════════\n");
    printf(" 7. Evaluar expresión Infija\n");
    printf(" 8. Evaluar expresión Postfija\n");
    printf(" 9. Evaluar expresión Prefija\n");
    printf("10. Evaluar paso a paso\n");
    printf("═══════════════════════════════════════\n");
    printf("11. Ver historial\n");
    printf("12. Ver estadísticas\n");
    printf("13. Limpiar historial\n");
    printf("═══════════════════════════════════════\n");
    printf("14. Mostrar ayuda\n");
    printf(" 0. Salir\n");
    printf("═══════════════════════════════════════\n");
}

// Procesar opción seleccionada
void procesarOpcion(int opcion) {
    char expresion[MAX_EXPRESION];
    
    switch (opcion) {
        case 0:
            salirPrograma();
            break;
            
        case 1: // Infija → Postfija
            printf("\n═══════════════════════════════════════\n");
            printf("      CONVERSIÓN INFIJA → POSTFIJA\n");
            printf("═══════════════════════════════════════\n");
            printf("Ingrese expresión infija (ej: (a+b)*c): ");
            fgets(expresion, sizeof(expresion), stdin);
            expresion[strcspn(expresion, "\n")] = '\0';
            
            if (strlen(expresion) > 0) {
                char* resultado = convertirInfijaAPostfija(expresion);
                if (resultado) {
                    printf("\n Resultado postfija: %s\n", resultado);
                    guardarOperacion(expresion, resultado, "INFIJA→POSTFIJA");
                    free(resultado);
                }
            }
            break;
            
        case 2: // Infija → Prefija
            printf("\n═══════════════════════════════════════\n");
            printf("      CONVERSIÓN INFIJA → PREFIJA\n");
            printf("═══════════════════════════════════════\n");
            printf("Ingrese expresión infija (ej: (a+b)*c): ");
            fgets(expresion, sizeof(expresion), stdin);
            expresion[strcspn(expresion, "\n")] = '\0';
            
            if (strlen(expresion) > 0) {
                char* resultado = convertirInfijaAPrefija(expresion);
                if (resultado) {
                    printf("\n Resultado prefija: %s\n", resultado);
                    guardarOperacion(expresion, resultado, "INFIJA→PREFIJA");
                    free(resultado);
                }
            }
            break;
            
        case 3: // Postfija → Infija
            printf("\n═══════════════════════════════════════\n");
            printf("      CONVERSIÓN POSTFIJA → INFIJA\n");
            printf("═══════════════════════════════════════\n");
            printf("Ingrese expresión postfija (ej: a b + c *): ");
            fgets(expresion, sizeof(expresion), stdin);
            expresion[strcspn(expresion, "\n")] = '\0';
            
            if (strlen(expresion) > 0) {
                char* resultado = convertirPostfijaAInfija(expresion);
                if (resultado) {
                    printf("\n Resultado infija: %s\n", resultado);
                    guardarOperacion(expresion, resultado, "POSTFIJA→INFIJA");
                    free(resultado);
                }
            }
            break;
            
        case 4: // Postfija → Prefija
            printf("\n═══════════════════════════════════════\n");
            printf("      CONVERSIÓN POSTFIJA → PREFIJA\n");
            printf("═══════════════════════════════════════\n");
            printf("Ingrese expresión postfija (ej: a b + c *): ");
            fgets(expresion, sizeof(expresion), stdin);
            expresion[strcspn(expresion, "\n")] = '\0';
            
            if (strlen(expresion) > 0) {
                char* resultado = convertirPostfijaAPrefija(expresion);
                if (resultado) {
                    printf("\n Resultado prefija: %s\n", resultado);
                    guardarOperacion(expresion, resultado, "POSTFIJA→PREFIJA");
                    free(resultado);
                }
            }
            break;
            
        case 5: // Prefija → Infija
            printf("\n═══════════════════════════════════════\n");
            printf("      CONVERSIÓN PREFIJA → INFIJA\n");
            printf("═══════════════════════════════════════\n");
            printf("Ingrese expresión prefija (ej: * + a b c): ");
            fgets(expresion, sizeof(expresion), stdin);
            expresion[strcspn(expresion, "\n")] = '\0';
            
            if (strlen(expresion) > 0) {
                char* resultado = convertirPrefijaAInfija(expresion);
                if (resultado) {
                    printf("\n Resultado infija: %s\n", resultado);
                    guardarOperacion(expresion, resultado, "PREFIJA→INFIJA");
                    free(resultado);
                }
            }
            break;
            
        case 6: // Prefija → Postfija
            printf("\n═══════════════════════════════════════\n");
            printf("      CONVERSIÓN PREFIJA → POSTFIJA\n");
            printf("═══════════════════════════════════════\n");
            printf("Ingrese expresión prefija (ej: * + a b c): ");
            fgets(expresion, sizeof(expresion), stdin);
            expresion[strcspn(expresion, "\n")] = '\0';
            
            if (strlen(expresion) > 0) {
                char* resultado = convertirPrefijaAPostfija(expresion);
                if (resultado) {
                    printf("\n✅ Resultado postfija: %s\n", resultado);
                    guardarOperacion(expresion, resultado, "PREFIJA→POSTFIJA");
                    free(resultado);
                }
            }
            break;
            
        case 7: // Evaluar Infija
            evaluarExpresionInfija();
            break;
            
        case 8: // Evaluar Postfija
            evaluarExpresionPostfija();
            break;
            
        case 9: // Evaluar Prefija
            evaluarExpresionPrefija();
            break;
            
        case 10: // Evaluar paso a paso
            evaluarPasoAPaso();
            break;
            
        case 11: // Ver historial
            mostrarHistorial();
            break;
            
        case 12: // Ver estadísticas
            mostrarEstadisticas();
            break;
            
        case 13: // Limpiar historial
            limpiarHistorial();
            break;
            
        case 14: // Mostrar ayuda
            mostrarAyuda();
            break;
            
        default:
            printf("\n Opción no válida. Intente de nuevo.\n");
            break;
    }
    
    if (opcion >= 1 && opcion <= 13) {
        printf("\nPresione Enter para continuar...");
        getchar();
    }
}

// Evaluar expresión infija
void evaluarExpresionInfija() {
    printf("\n═══════════════════════════════════════\n");
    printf("         EVALUACIÓN INFIJA\n");
    printf("═══════════════════════════════════════\n");
    printf("Ingrese expresión infija con números:\n");
    printf("Ejemplo: (3+4)*5-2/1\n> ");
    
    char expresion[MAX_EXPRESION];
    fgets(expresion, sizeof(expresion), stdin);
    expresion[strcspn(expresion, "\n")] = '\0';
    
    if (strlen(expresion) > 0) {
        double resultado = calcularExpresionInfija(expresion);
        printf("\n Resultado: %.4f\n", resultado);
        
        char resultadoStr[50];
        sprintf(resultadoStr, "%.4f", resultado);
        guardarOperacion(expresion, resultadoStr, "EVALUAR_INFIJA");
    }
}

// Evaluar expresión postfija
void evaluarExpresionPostfija() {
    printf("\n═══════════════════════════════════════\n");
    printf("        EVALUACIÓN POSTFIJA\n");
    printf("═══════════════════════════════════════\n");
    printf("Ingrese expresión postfija con números:\n");
    printf("Ejemplo: 3 4 + 5 * 2 1 / -\n> ");
    
    char expresion[MAX_EXPRESION];
    fgets(expresion, sizeof(expresion), stdin);
    expresion[strcspn(expresion, "\n")] = '\0';
    
    if (strlen(expresion) > 0) {
        double resultado = calcularExpresionPostfija(expresion);
        printf("\n Resultado: %.4f\n", resultado);
        
        char resultadoStr[50];
        sprintf(resultadoStr, "%.4f", resultado);
        guardarOperacion(expresion, resultadoStr, "EVALUAR_POSTFIJA");
    }
}

// Evaluar expresión prefija
void evaluarExpresionPrefija() {
    printf("\n═══════════════════════════════════════\n");
    printf("         EVALUACIÓN PREFIJA\n");
    printf("═══════════════════════════════════════\n");
    printf("Ingrese expresión prefija con números:\n");
    printf("Ejemplo: - * + 3 4 5 / 2 1\n> ");
    
    char expresion[MAX_EXPRESION];
    fgets(expresion, sizeof(expresion), stdin);
    expresion[strcspn(expresion, "\n")] = '\0';
    
    if (strlen(expresion) > 0) {
        double resultado = calcularExpresionPrefija(expresion);
        printf("\n Resultado: %.4f\n", resultado);
        
        char resultadoStr[50];
        sprintf(resultadoStr, "%.4f", resultado);
        guardarOperacion(expresion, resultadoStr, "EVALUAR_PREFIJA");
    }
}

// Evaluación paso a paso
void evaluarPasoAPaso() {
    printf("\n═══════════════════════════════════════\n");
    printf("        EVALUACIÓN PASO A PASO\n");
    printf("═══════════════════════════════════════\n");
    printf("Seleccione formato:\n");
    printf("1. Evaluar expresión postfija\n");
    printf("2. Evaluar expresión prefija\n");
    printf("\nOpción: ");
    
    char opcionStr[10];
    fgets(opcionStr, sizeof(opcionStr), stdin);
    int opcion = atoi(opcionStr);
    
    printf("\nIngrese expresión (con números):\n> ");
    char expresion[MAX_EXPRESION];
    fgets(expresion, sizeof(expresion), stdin);
    expresion[strcspn(expresion, "\n")] = '\0';
    
    if (strlen(expresion) == 0) {
        printf(" Expresión vacía\n");
        return;
    }
    
    printf("\n═══════════════════════════════════════\n");
    printf("        PROCESO PASO A PASO\n");
    printf("═══════════════════════════════════════\n");
    
    DoubleStack* pila = createDoubleStack();
    char* token = strtok(expresion, " ");
    int paso = 1;
    
    if (opcion == 1) { // Postfija
        printf("Expresión postfija: %s\n\n", expresion);
        printf("Paso │ Token │ Operación       │ Pila\n");
        printf("─────┼───────┼─────────────────┼─────\n");
        
        while (token != NULL) {
            printf("%4d │ %5s │ ", paso++, token);
            
            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                // Es número
                double valor = atof(token);
                doubleStackPush(pila, valor);
                printf("Push %.2f       │ ", valor);
            } else if (strchr("+-*/^", token[0]) != NULL) {
                // Es operador
                if (doubleStackSize(pila) < 2) {
                    printf("ERROR: Operandos insuficientes │\n");
                    destroyDoubleStack(pila);
                    return;
                }
                
                double b = doubleStackPop(pila);
                double a = doubleStackPop(pila);
                double resultado;
                
                switch (token[0]) {
                    case '+': resultado = a + b; break;
                    case '-': resultado = a - b; break;
                    case '*': resultado = a * b; break;
                    case '/': resultado = a / b; break;
                    case '^': resultado = pow(a, b); break;
                    default: resultado = 0;
                }
                
                doubleStackPush(pila, resultado);
                printf("%.2f %c %.2f = %.2f │ ", a, token[0], b, resultado);
            }
            
            // Mostrar pila
            printf("[");
            for (int i = 0; i <= pila->top; i++) {
                printf("%.2f", pila->items[i]);
                if (i < pila->top) printf(", ");
            }
            printf("]\n");
            
            token = strtok(NULL, " ");
        }
        
        if (doubleStackSize(pila) == 1) {
            double resultadoFinal = doubleStackPop(pila);
            printf("\n Resultado final: %.4f\n", resultadoFinal);
        } else {
            printf("\n Expresión inválida\n");
        }
    }
    else if (opcion == 2) { // Prefija
        // Para prefija, necesitaríamos procesar al revés
        printf("Evaluación prefija no implementada en paso a paso.\n");
        printf("Use evaluación normal para expresiones prefijas.\n");
    }
    
    destroyDoubleStack(pila);
}

// Mostrar historial
void mostrarHistorial() {
    leerHistorial();
}

// Mostrar estadísticas
void mostrarEstadisticas() {
    mostrarEstadisticas();
}

// Limpiar historial
void limpiarHistorial() {
    printf("\n¿Está seguro de que desea limpiar el historial? (s/n): ");
    char confirmacion;
    scanf(" %c", &confirmacion);
    getchar(); // Limpiar buffer
    
    if (confirmacion == 's' || confirmacion == 'S') {
        limpiarHistorial();
        printf(" Historial limpiado\n");
    } else {
        printf("Operación cancelada\n");
    }
}

// Salir del programa
void salirPrograma() {
    printf("\n═══════════════════════════════════════\n");
    printf("         FIN DEL PROGRAMA\n");
    printf("═══════════════════════════════════════\n");
    printf("Gracias por usar la Calculadora de Expresiones\n");
    printf("Historial guardado en: historial_calculadora.txt\n");
    printf("═══════════════════════════════════════\n\n");
    ejecutando = 0;
}

// Calcular expresión infija
double calcularExpresionInfija(const char* expresion) {
    char* postfija = convertirInfijaAPostfija(expresion);
    double resultado = calcularExpresionPostfija(postfija);
    free(postfija);
    return resultado;
}

// Calcular expresión postfija
double calcularExpresionPostfija(const char* expresion) {
    DoubleStack* pila = createDoubleStack();
    char* copia = strdup(expresion);
    char* token = strtok(copia, " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            // Es número
            double valor = atof(token);
            doubleStackPush(pila, valor);
        } else if (strchr("+-*/^", token[0]) != NULL) {
            // Es operador
            if (doubleStackSize(pila) < 2) {
                destroyDoubleStack(pila);
                free(copia);
                return 0.0;
            }
            
            double b = doubleStackPop(pila);
            double a = doubleStackPop(pila);
            double resultado;
            
            switch (token[0]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/': resultado = a / b; break;
                case '^': resultado = pow(a, b); break;
                default: resultado = 0;
            }
            
            doubleStackPush(pila, resultado);
        }
        
        token = strtok(NULL, " ");
    }
    
    double resultadoFinal = 0.0;
    if (doubleStackSize(pila) == 1) {
        resultadoFinal = doubleStackPop(pila);
    }
    
    destroyDoubleStack(pila);
    free(copia);
    return resultadoFinal;
}

// Calcular expresión prefija
double calcularExpresionPrefija(const char* expresion) {
    DoubleStack* pila = createDoubleStack();
    char* copia = strdup(expresion);
    
    // Procesar al revés para prefija
    int longitud = strlen(copia);
    char** tokens = (char**)malloc(sizeof(char*) * (longitud/2 + 1));
    int numTokens = 0;
    
    char* token = strtok(copia, " ");
    while (token != NULL) {
        tokens[numTokens++] = strdup(token);
        token = strtok(NULL, " ");
    }
    
    // Procesar tokens al revés
    for (int i = numTokens - 1; i >= 0; i--) {
        char* tokenActual = tokens[i];
        
        if (isdigit(tokenActual[0]) || (tokenActual[0] == '-' && isdigit(tokenActual[1]))) {
            // Es número
            double valor = atof(tokenActual);
            doubleStackPush(pila, valor);
        } else if (strchr("+-*/^", tokenActual[0]) != NULL) {
            // Es operador
            if (doubleStackSize(pila) < 2) {
                for (int j = 0; j < numTokens; j++) free(tokens[j]);
                free(tokens);
                free(copia);
                destroyDoubleStack(pila);
                return 0.0;
            }
            
            double a = doubleStackPop(pila);
            double b = doubleStackPop(pila);
            double resultado;
            
            switch (tokenActual[0]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/': resultado = a / b; break;
                case '^': resultado = pow(a, b); break;
                default: resultado = 0;
            }
            
            doubleStackPush(pila, resultado);
        }
        
        free(tokens[i]);
    }
    
    double resultadoFinal = 0.0;
    if (doubleStackSize(pila) == 1) {
        resultadoFinal = doubleStackPop(pila);
    }
    
    free(tokens);
    free(copia);
    destroyDoubleStack(pila);
    return resultadoFinal;
}
