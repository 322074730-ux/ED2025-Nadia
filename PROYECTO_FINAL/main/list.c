#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* mi_strdup(const char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len * sizeof(char));
    
    if (copy) {
        strcpy(copy, str);
    }
    
    return copy;
}

ListaSimple* crearListaSimple() {
    ListaSimple* lista = (ListaSimple*)malloc(sizeof(ListaSimple));
    if (!lista) return NULL;
    
    lista->inicio = NULL;
    lista->fin = NULL;
    lista->total = 0;
    return lista;
}

static NodoSimple* crearNodoSimple(const char* valor) {
    NodoSimple* nodo = (NodoSimple*)malloc(sizeof(NodoSimple));
    if (!nodo) return NULL;
    
   
    nodo->valor = mi_strdup(valor);
    if (!nodo->valor) {
        free(nodo);
        return NULL;
    }
    
    nodo->proximo = NULL;
    return nodo;
}

// Agregar a lista simple
void agregarListaSimple(ListaSimple* lista, const char* valor) {
    if (!lista || !valor) return;
    
    NodoSimple* nuevo = crearNodoSimple(valor);
    if (!nuevo) return;
    
    if (lista->total == 0) {
        lista->inicio = nuevo;
        lista->fin = nuevo;
    } else {
        lista->fin->proximo = nuevo;
        lista->fin = nuevo;
    }
    
    lista->total++;
}


void imprimirListaSimple(ListaSimple* lista) {
    if (!lista || lista->total == 0) {
        printf("[]\n");
        return;
    }
    
    NodoSimple* actual = lista->inicio;
    printf("[");
    while (actual) {
        printf("%s", actual->valor);
        if (actual->proximo) printf(", ");
        actual = actual->proximo;
    }
    printf("]\n");
}


int contarListaSimple(ListaSimple* lista) {
    return lista ? lista->total : 0;
}


void liberarListaSimple(ListaSimple* lista) {
    if (!lista) return;
    
    NodoSimple* actual = lista->inicio;
    while (actual) {
        NodoSimple* siguiente = actual->proximo;
        free(actual->valor);
        free(actual);
        actual = siguiente;
    }
    
    free(lista);
}
