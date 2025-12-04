#include "../Include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Crear nueva lista de tokens
ListaTokens* nuevaListaTokens() {
    ListaTokens* lista = (ListaTokens*)malloc(sizeof(ListaTokens));
    if (!lista) {
        fprintf(stderr, "Fallo al crear lista de tokens\n");
        return NULL;
    }
    lista->inicio = NULL;
    lista->fin = NULL;
    lista->total = 0;
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
    
    token->clase = clase;
    token->lugar = lugar;
    token->siguiente = NULL;
    token->anterior = NULL;
    return token;
}

// Agregar token a la lista
void agregarToken(ListaTokens* lista, const char* texto, int clase, int lugar) {
    if (!lista || !texto) return;
    
    Token* token = nuevoToken(texto, clase, lugar);
    if (!token) return;
    
    if (lista->total == 0) {
        lista->inicio = token;
        lista->fin = token;
    } else {
        lista->fin->siguiente = token;
        token->anterior = lista->fin;
        lista->fin = token;
    }
    
    lista->total++;
}

// ============ NOTA: LAS SIGUIENTES FUNCIONES YA NO ESTÃN AQUÃ ============
// ============ SE MOVIERON A utils.c PARA EVITAR DUPLICACIÃ“N =============

// Verificar si es operador (YA NO ESTÃ - usamos la de utils.h)
// int esCaracterOperador(char c) {
//     return esCaracterOperadorLocal(c);
// }

// Verificar si es parÃ©ntesis
int esCaracterParentesis(char c) {
    return c == '(' || c == ')';
}

// Verificar si es letra
int esCaracterLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Verificar si es dÃ­gito
int esCaracterDigito(char c) {
    return c >= '0' && c <= '9';
}

// ============ NOTA: esNumeroValido TAMPOCO ESTÃ AQUÃ ============
// ============ SE USA LA DE utils.h =============================

// Verificar si es un signo negativo vÃ¡lido
int esSignoNegativo(const char* expresion, int pos) {
    if (expresion[pos] != '-') return 0;
    
    // EstÃ¡ al inicio de la expresiÃ³n
    if (pos == 0) return 1;
    
    // EstÃ¡ despuÃ©s de un operador
    if (pos > 0 && esCaracterOperador(expresion[pos-1])) return 1;
    
    // EstÃ¡ despuÃ©s de parÃ©ntesis izquierdo
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

// ============ FUNCIÃ“N PRINCIPAL ============

// FunciÃ³n principal de anÃ¡lisis
ListaTokens* analizarExpresion(const char* expresion) {
    if (!expresion) {
        fprintf(stderr, "ExpresiÃ³n nula\n");
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
        
        // ParÃ©ntesis izquierdo
        if (actual == '(') {
            char temp[2] = {actual, '\0'};
            agregarToken(lista, temp, TOKEN_KIND_PAR_IZQ, i);
            i++;
        }
        // ParÃ©ntesis derecho
        else if (actual == ')') {
            char temp[2] = {actual, '\0'};
            agregarToken(lista, temp, TOKEN_KIND_PAR_DER, i);
            i++;
        }
        // Operador
        else if (esCaracterOperador(actual)) {
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
        // NÃºmero (entero, decimal, negativo)
        else if (esCaracterDigito(actual) || 
                esSignoNegativo(expresion, i)) {
            
            int inicio = i;
            
            // Incluir signo negativo si existe
            if (expresion[i] == '-') {
                i++;
            }
            
            // Capturar todos los dÃ­gitos y punto decimal
            while (i < longitud && 
                   (esCaracterDigito(expresion[i]) || expresion[i] == '.')) {
                i++;
            }
            
            // Extraer el nÃºmero
            int tamano = i - inicio;
            if (tamano > 0) {
                char* numero = (char*)malloc(tamano + 1);
                if (numero) {
                    strncpy(numero, expresion + inicio, tamano);
                    numero[tamano] = '\0';
                    
                    // Verificar que sea nÃºmero vÃ¡lido
                    if (esNumeroValido(numero)) {
                        agregarToken(lista, numero, TOKEN_KIND_NUMERO, inicio);
                    } else {
                        agregarToken(lista, numero, TOKEN_KIND_DESCONOCIDO, inicio);
                    }
                    
                    free(numero);
                }
            }
        }
        // CarÃ¡cter desconocido
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
        printf("Lista de tokens vacÃ­a\n");
        return;
    }
    
    printf("\nâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•\n");
    printf("       ANÃLISIS DE EXPRESIÃ“N\n");
    printf("â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•\n");
    printf("Total de tokens: %d\n\n", lista->total);
    printf("Pos â”‚ Token       â”‚ Clase\n");
    printf("â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€\n");
    
    Token* actual = lista->inicio;
    while (actual) {
        printf("%3d â”‚ %-11s â”‚ %s\n", 
               actual->lugar, 
               actual->texto, 
               nombreClaseToken(actual->clase));
        actual = actual->siguiente;
    }
    printf("â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€\n");
}

// Verificar validez de los tokens
int verificarTokens(const ListaTokens* lista) {
    if (!lista || lista->total == 0) {
        fprintf(stderr, "Lista de tokens vacÃ­a\n");
        return 0;
    }
    
    // Verificar tokens desconocidos
    Token* actual = lista->inicio;
    while (actual) {
        if (actual->clase == TOKEN_KIND_DESCONOCIDO) {
            fprintf(stderr, "Error: CarÃ¡cter no vÃ¡lido en posiciÃ³n %d: '%s'\n", 
                    actual->lugar, actual->texto);
            return 0;
        }
        actual = actual->siguiente;
    }
    
    // Verificar parÃ©ntesis balanceados
    int contador = 0;
    actual = lista->inicio;
    while (actual) {
        if (actual->clase == TOKEN_KIND_PAR_IZQ) {
            contador++;
        } else if (actual->clase == TOKEN_KIND_PAR_DER) {
            contador--;
            if (contador < 0) {
                fprintf(stderr, "Error: ParÃ©ntesis derecho sin izquierdo en posiciÃ³n %d\n", 
                        actual->lugar);
                return 0;
            }
        }
        actual = actual->siguiente;
    }
    
    if (contador > 0) {
        fprintf(stderr, "Error: Faltan %d parÃ©ntesis derechos\n", contador);
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
            fprintf(stderr, "Error: Dos operadores seguidos en posiciÃ³n %d\n", 
                    actual->lugar);
            return 0;
        }
        
        // Verificar operador despuÃ©s de parÃ©ntesis izquierdo (excepto negativo)
        if (claseAnterior == TOKEN_KIND_PAR_IZQ && 
            claseActual == TOKEN_KIND_OPERADOR) {
            if (strcmp(actual->texto, "-") != 0) {
                fprintf(stderr, "Error: Operador '%s' despuÃ©s de '(' en posiciÃ³n %d\n", 
                        actual->texto, actual->lugar);
                return 0;
            }
        }
        
        // Verificar parÃ©ntesis derecho despuÃ©s de operador
        if (claseAnterior == TOKEN_KIND_OPERADOR && 
            claseActual == TOKEN_KIND_PAR_DER) {
            fprintf(stderr, "Error: ')' despuÃ©s de operador en posiciÃ³n %d\n", 
                    actual->lugar);
            return 0;
        }
        
        claseAnterior = claseActual;
        actual = actual->siguiente;
    }
    
    return 1; // VÃ¡lido
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

// Obtener token en posiciÃ³n especÃ­fica
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
