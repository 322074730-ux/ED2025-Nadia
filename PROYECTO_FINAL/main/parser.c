#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Función auxiliar para verificar operador (definida aquí para uso interno)
static int esCaracterOperadorLocal(char c) {
    switch (c) {
        case '+': case '-': case '*': case '/': case '^':
            return 1;
        default:
            return 0;
    }
}

// Crear nueva lista de tokens
ListaTokens* nuevaListaTokens() {
    ListaTokens* lista = (ListaTokens*)malloc(sizeof(ListaTokens));
    if (!lista) {
        fprintf(stderr, "Fallo al crear lista de tokens\n");
        return NULL;
    }
    lista->inicio=NULL;
    lista->fin=NULL;
    lista->total=0;
    return lista;
}

// Crear nuevo token
static Token* nuevoToken(const char* texto, int clase, int lugar) {
    if (!texto) return NULL;   
    Token* token = (Token*)malloc(sizeof(Token));
    if (!token) {
        fprintf(stderr, "Fallo al crear token\n");
        return NULL;
    }
    token->texto = strdup(texto);
    if (!token->texto) {
        free(token);
        fprintf(stderr, "Fallo al duplicar texto del token\n");
        return NULL;
    }
    token->clase=clase;
    token->lugar=lugar;
    token->siguiente=NULL;
    token->anterior=NULL;
    return token;
}

// Agregar token a la lista
void agregarToken(ListaTokens* lista, const char* texto, int clase, int lugar) {
    if (!lista || !texto) return;
    Token* token=nuevoToken(texto, clase, lugar);
    if (!token) return;
    if (lista->total==0) {
        lista->inicio=token;
        lista->fin=token;
    } else {
        lista->fin->siguiente=token;
        token->anterior=lista->fin;
        lista->fin=token;
    }
    lista->total++;
}

// Verificar si es operador
int esCaracterOperador(char c) {
    return esCaracterOperadorLocal(c);
}

// Verificar si es paréntesis
int esCaracterParentesis(char c) {
    return c == '(' || c == ')';
}

// Verificar si es letra
int esCaracterLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Verificar si es dígito
int esCaracterDigito(char c) {
    return c >= '0' && c <= '9';
}

// Verificar si es un número válido
int esNumeroValido(const char* str) {
    if (!str || !*str) return 0;
    
    int punto = 0;
    int digitos = 0;
    
    for (int i = 0; str[i]; i++) {
        if (i == 0 && str[i] == '-') {
            continue; // Signo negativo permitido al inicio
        }
        
        if (str[i] == '.') {
            punto++;
            if (punto > 1) return 0;
        } else if (!esCaracterDigito(str[i])) {
            return 0;
        } else {
            digitos++;
        }
    }
    
    return digitos > 0;
}

// Verificar si es un signo negativo válido
int esSignoNegativo(const char* expresion, int pos) {
    if (expresion[pos] != '-') return 0;
    
    // Está al inicio de la expresión
    if (pos == 0) return 1;
    
    // Está después de un operador
    if (pos > 0 && esCaracterOperadorLocal(expresion[pos-1])) return 1;
    
    // Está después de paréntesis izquierdo
    if (pos > 0 && expresion[pos-1] == '(') return 1;
    
    return 0;
}

// Obtener nombre de la clase del token
const char* nombreClaseToken(int clase) {
    switch (clase) {
        case TOKEN_KIND_NUMERO:    return "NUMERO";
        case TOKEN_KIND_OPERADOR:  return "OPERADOR";
        case TOKEN_KIND_PAR_IZQ:   return "PAR_IZQ";
        case TOKEN_KIND_PAR_DER:   return "PAR_DER";
        case TOKEN_KIND_LETRA:     return "LETRA";
        case TOKEN_KIND_BLANCO:    return "BLANCO";
        case TOKEN_KIND_DESCONOCIDO: return "DESCONOCIDO";
        default: return "INDEFINIDO";
    }
}

// ============ FUNCIÓN PRINCIPAL ============

// Función principal de análisis
ListaTokens* analizarExpresion(const char* expresion) {
    if (!expresion) {
        fprintf(stderr, "Expresión nula\n");
        return NULL;
    }
    
    ListaTokens* lista = nuevaListaTokens();
    if (!lista) return NULL;
    
    int i = 0;
    int longitud = strlen(expresion);
    
    while (i < longitud) {
        char actual = expresion[i];
        
        // Espacios en blanco (los ignoramos pero los registramos)
        if (actual == ' ' || actual == '\t') {
            agregarToken(lista, " ", TOKEN_KIND_BLANCO, i);
            i++;
            continue;
        }
        
        // Paréntesis izquierdo
        if (actual == '(') {
            char temp[2] = {actual, '\0'};
            agregarToken(lista, temp, TOKEN_KIND_PAR_IZQ, i);
            i++;
        }
        // Paréntesis derecho
        else if (actual == ')') {
            char temp[2] = {actual, '\0'};
            agregarToken(lista, temp, TOKEN_KIND_PAR_DER, i);
            i++;
        }
        // Operador
        else if (esCaracterOperadorLocal(actual)) {
            char temp[2] = {actual, '\0'};
            agregarToken(lista, temp, TOKEN_KIND_OPERADOR, i);
            i++;
        }
        // Letra
        else if (esCaracterLetra(actual)) {
            char temp[2] = {actual, '\0'};
            agregarToken(lista, temp, TOKEN_KIND_LETRA, i);
            i++;
        }
        // Número (entero, decimal, negativo)
        else if (esCaracterDigito(actual) || 
                esSignoNegativo(expresion, i)) {
            
            int inicio = i;
            
            // Incluir signo negativo si existe
            if (expresion[i] == '-') {
                i++;
            }
            
            // Capturar todos los dígitos y punto decimal
            while (i < longitud && 
                   (esCaracterDigito(expresion[i]) || expresion[i] == '.')) {
                i++;
            }
            
            // Extraer el número
            int tamano = i - inicio;
            if (tamano > 0) {
                char* numero = (char*)malloc(tamano + 1);
                if (numero) {
                    strncpy(numero, expresion + inicio, tamano);
                    numero[tamano] = '\0';
                    
                    // Verificar que sea número válido
                    if (esNumeroValido(numero)) {
                        agregarToken(lista, numero, TOKEN_KIND_NUMERO, inicio);
                    } else {
                        agregarToken(lista, numero, TOKEN_KIND_DESCONOCIDO, inicio);
                    }
                    
                    free(numero);
                }
            }
        }
        // Carácter desconocido
        else {
            char temp[2] = {actual, '\0'};
            agregarToken(lista, temp, TOKEN_KIND_DESCONOCIDO, i);
            i++;
        }
    }
    
    return lista;
}

// Mostrar todos los tokens
void mostrarTokens(const ListaTokens* lista) {
    if (!lista || lista->total == 0) {
        printf("Lista de tokens vacía\n");
        return;
    }
    
    printf("\n═══════════════════════════════════════\n");
    printf("       ANÁLISIS DE EXPRESIÓN\n");
    printf("═══════════════════════════════════════\n");
    printf("Total de tokens: %d\n\n", lista->total);
    printf("Pos │ Token       │ Clase\n");
    printf("────┼─────────────┼─────────────\n");
    
    Token* actual = lista->inicio;
    while (actual) {
        printf("%3d │ %-11s │ %s\n", 
               actual->lugar, 
               actual->texto, 
               nombreClaseToken(actual->clase));
        actual = actual->siguiente;
    }
    printf("────┴─────────────┴─────────────\n");
}

// Verificar validez de los tokens
int verificarTokens(const ListaTokens* lista) {
    if (!lista || lista->total == 0) {
        fprintf(stderr, "Lista de tokens vacía\n");
        return 0;
    }
    
    // Verificar tokens desconocidos
    Token* actual = lista->inicio;
    while (actual) {
        if (actual->clase == TOKEN_KIND_DESCONOCIDO) {
            fprintf(stderr, "Error: Carácter no válido en posición %d: '%s'\n", 
                    actual->lugar, actual->texto);
            return 0;
        }
        actual = actual->siguiente;
    }
    
    // Verificar paréntesis balanceados
    int contador = 0;
    actual = lista->inicio;
    while (actual) {
        if (actual->clase == TOKEN_KIND_PAR_IZQ) {
            contador++;
        } else if (actual->clase == TOKEN_KIND_PAR_DER) {
            contador--;
            if (contador < 0) {
                fprintf(stderr, "Error: Paréntesis derecho sin izquierdo en posición %d\n", 
                        actual->lugar);
                return 0;
            }
        }
        actual = actual->siguiente;
    }
    
    if (contador > 0) {
        fprintf(stderr, "Error: Faltan %d paréntesis derechos\n", contador);
        return 0;
    }
    
    // Verificar secuencia de operadores y operandos
    int claseAnterior = -1;
    actual = lista->inicio;
    
    while (actual) {
        // Saltar espacios en blanco
        if (actual->clase == TOKEN_KIND_BLANCO) {
            actual = actual->siguiente;
            continue;
        }
        
        int claseActual = actual->clase;
        
        // Verificar dos operadores seguidos
        if (claseAnterior == TOKEN_KIND_OPERADOR && 
            claseActual == TOKEN_KIND_OPERADOR) {
            fprintf(stderr, "Error: Dos operadores seguidos en posición %d\n", 
                    actual->lugar);
            return 0;
        }
        
        // Verificar operador después de paréntesis izquierdo (excepto negativo)
        if (claseAnterior == TOKEN_KIND_PAR_IZQ && 
            claseActual == TOKEN_KIND_OPERADOR) {
            if (strcmp(actual->texto, "-") != 0) {
                fprintf(stderr, "Error: Operador '%s' después de '(' en posición %d\n", 
                        actual->texto, actual->lugar);
                return 0;
            }
        }
        
        // Verificar paréntesis derecho después de operador
        if (claseAnterior == TOKEN_KIND_OPERADOR && 
            claseActual == TOKEN_KIND_PAR_DER) {
            fprintf(stderr, "Error: ')' después de operador en posición %d\n", 
                    actual->lugar);
            return 0;
        }
        
        claseAnterior = claseActual;
        actual = actual->siguiente;
    }
    
    return 1; // Válido
}

// Liberar memoria de la lista
void liberarListaTokens(ListaTokens* lista) {
    if (!lista) return;
    
    Token* actual = lista->inicio;
    while (actual) {
        Token* siguiente = actual->siguiente;
        if (actual->texto) {
            free(actual->texto);
        }
        free(actual);
        actual = siguiente;
    }
    
    free(lista);
}

// ============ FUNCIONES ADICIONALES ============

// Contar tokens por clase
int contarTokensClase(const ListaTokens* lista, int clase) {
    if (!lista) return 0;
    
    int contador = 0;
    Token* actual = lista->inicio;
    
    while (actual) {
        if (actual->clase == clase) {
            contador++;
        }
        actual = actual->siguiente;
    }
    
    return contador;
}

// Obtener token en posición específica
Token* obtenerTokenPosicion(const ListaTokens* lista, int indice) {
    if (!lista || indice < 0 || indice >= lista->total) {
        return NULL;
    }
    
    Token* actual = lista->inicio;
    for (int i = 0; i < indice && actual; i++) {
        actual = actual->siguiente;
    }
    
    return actual;
}
