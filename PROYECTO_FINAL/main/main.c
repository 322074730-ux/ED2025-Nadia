#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Include/stack.h"
#include "../Include/dlist.h"
#include "../Include/parser.h"
#include "../Include/utils.h"
#include "../Include/file_manager.h"

// Declaraciones de funciones (SOLO DECLARACIONES)
void mostrarMenu();
void procesarOpcion(int opcion);
void mostrarCreditos();
void mostrarVersion();
void mostrarAyuda();

// Funciones de conversión (declaraciones)
char* convertirInfijaAPostfija(const char* infija);
char* convertirInfijaAPrefija(const char* infija);
char* convertirPostfijaAInfija(const char* postfija);
char* convertirPostfijaAPrefija(const char* postfija);
char* convertirPrefijaAInfija(const char* prefija);
char* convertirPrefijaAPostfija(const char* prefija);

// Variables globales
ListaDoble* historial = NULL;

// ============ FUNCIONES PARA ARGUMENTOS DE LÍNEA DE COMANDOS ============

void mostrarVersion() {
    printf("=========================================\n");
    printf("        CALCULADORA DE EXPRESIONES       \n");
    printf("             Versión 2.0.0               \n");
    printf("=========================================\n");
    printf("Compilado: %s %s\n", __DATE__, __TIME__);
    printf("Desarrollado por: Nadia\n");
    printf("Materia: Estructuras de Datos\n");
    printf("=========================================\n");
}

void mostrarAyuda() {
    printf("=========================================\n");
    printf("        CALCULADORA DE EXPRESIONES       \n");
    printf("             AYUDA DE USO                \n");
    printf("=========================================\n\n");
    
    printf("SINTAXIS:\n");
    printf("  calc.exe                  - Menú interactivo\n");
    printf("  calc.exe [OPCION]         - Modo no interactivo\n");
    printf("  calc.exe EXPRESIÓN TIPO   - Conversión directa\n\n");
    
    printf("OPCIONES:\n");
    printf("  -h, --help                - Muestra esta ayuda\n");
    printf("  -v, --version             - Muestra información de versión\n");
    printf("  -c, --creditos            - Muestra los créditos\n");
    printf("  -s, --stats               - Muestra estadísticas del historial\n");
    printf("  -l, --list                - Lista el historial de operaciones\n");
    printf("  -cl, --clear              - Limpia el historial\n\n");
    
    printf("MODO DE CONVERSIÓN DIRECTA:\n");
    printf("  calc.exe \"EXPRESIÓN\" TIPO\n\n");
    
    printf("TIPOS DE CONVERSIÓN:\n");
    printf("  inf-post    - Infija a Postfija\n");
    printf("  inf-pre     - Infija a Prefija\n");
    printf("  post-inf    - Postfija a Infija\n");
    printf("  post-pre    - Postfija a Prefija\n");
    printf("  pre-inf     - Prefija a Infija\n");
    printf("  pre-post    - Prefija a Postfija\n\n");
    
    printf("EJEMPLOS:\n");
    printf("  calc.exe \"A+B\" inf-post\n");
    printf("    Resultado: A B +\n\n");
    
    printf("  calc.exe \"A B +\" post-inf\n");
    printf("    Resultado: (A+B)\n\n");
    
    printf("  calc.exe -l\n");
    printf("    Muestra el historial de conversiones\n\n");
    
    printf("  calc.exe -s\n");
    printf("    Muestra estadísticas del historial\n");
    printf("=========================================\n");
}

// Función para procesar conversión directa desde línea de comandos
void procesarConversionDirecta(const char* expresion, const char* tipo) {
    char* resultado = NULL;
    char tipoConversion[50];
    
    printf("Expresión: %s\n", expresion);
    printf("Tipo: %s\n", tipo);
    printf("Resultado: ");
    
    if (strcmp(tipo, "inf-post") == 0) {
        resultado = convertirInfijaAPostfija(expresion);
        strcpy(tipoConversion, "INF->POST");
    } else if (strcmp(tipo, "inf-pre") == 0) {
        resultado = convertirInfijaAPrefija(expresion);
        strcpy(tipoConversion, "INF->PRE");
    } else if (strcmp(tipo, "post-inf") == 0) {
        resultado = convertirPostfijaAInfija(expresion);
        strcpy(tipoConversion, "POST->INF");
    } else if (strcmp(tipo, "post-pre") == 0) {
        resultado = convertirPostfijaAPrefija(expresion);
        strcpy(tipoConversion, "POST->PRE");
    } else if (strcmp(tipo, "pre-inf") == 0) {
        resultado = convertirPrefijaAInfija(expresion);
        strcpy(tipoConversion, "PRE->INF");
    } else if (strcmp(tipo, "pre-post") == 0) {
        resultado = convertirPrefijaAPostfija(expresion);
        strcpy(tipoConversion, "PRE->POST");
    } else {
        printf("ERROR: Tipo de conversión no válido\n");
        printf("Tipos válidos: inf-post, inf-pre, post-inf, post-pre, pre-inf, pre-post\n");
        exit(1);
    }
    
    if (resultado) {
        printf("%s\n", resultado);
        // Guardar en historial
        guardarOperacion(expresion, resultado, tipoConversion);
        free(resultado);
    } else {
        printf("ERROR: No se pudo realizar la conversión\n");
    }
}

// ============ FUNCIÓN MAIN MODIFICADA ============

int main(int argc, char* argv[]) {
    int opcion;
    
    // Inicializaciones
    historial = crearListaDoble();
    
    // Procesar argumentos de línea de comandos
    if (argc > 1) {
        // Modo no interactivo
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            mostrarAyuda();
            return 0;
        } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
            mostrarVersion();
            return 0;
        } else if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--creditos") == 0) {
            mostrarCreditos();
            return 0;
        } else if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--stats") == 0) {
            mostrarEstadisticas();
            return 0;
        } else if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--list") == 0) {
            leerHistorial();
            return 0;
        } else if (strcmp(argv[1], "-cl") == 0 || strcmp(argv[1], "--clear") == 0) {
            limpiarHistorial();
            printf("Historial limpiado correctamente.\n");
            return 0;
        } else if (argc == 3) {
            // Modo conversión directa: calc.exe "expresión" tipo
            procesarConversionDirecta(argv[1], argv[2]);
            return 0;
        } else {
            printf("Error: Argumentos no válidos.\n");
            printf("Use: calc.exe -h para mostrar ayuda\n");
            return 1;
        }
    }
    
    // Modo interactivo (sin argumentos)
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
    printf("Desarrollado por: Nadia\n");
    printf("Materia: Estructuras de Datos\n");
    printf("Version: 2.0.0\n");
    printf("Características:\n");
    printf("  • Conversión entre notaciones\n");
    printf("  • Historial de operaciones\n");
    printf("  • Modo interactivo y por línea de comandos\n");
    printf("  • Validación de expresiones\n");
    printf("=========================================\n");
}
