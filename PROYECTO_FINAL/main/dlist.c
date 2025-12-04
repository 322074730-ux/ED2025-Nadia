#include "dlist.h"
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

ListaDoble* crearListaDoble() {
    ListaDoble* lista = (ListaDoble*)malloc(sizeof(ListaDoble));
    if (!lista) return NULL;
    
    lista->cabeza = NULL;
    lista->cola = NULL;
    lista->cantidad = 0;
    return lista;
}

static NodoLista* crearNodo(const char* dato) {
    NodoLista* nodo = (NodoLista*)malloc(sizeof(NodoLista));
    if (!nodo) return NULL;
    
    nodo->dato = mi_strdup(dato);
    if (!nodo->dato) {
        free(nodo);
        return NULL;
    }
    
    nodo->anterior = NULL;
    nodo->siguiente = NULL;
    return nodo;
}

void agregarFinalLista(ListaDoble* lista, const char* dato) {
    if (!lista || !dato) return;
    
    NodoLista* nuevo = crearNodo(dato);
    if (!nuevo) return;
    
    if (lista->cantidad == 0) {
        lista->cabeza = nuevo;
        lista->cola = nuevo;
    } else {
        lista->cola->siguiente = nuevo;
        nuevo->anterior = lista->cola;
        lista->cola = nuevo;
    }
    
    lista->cantidad++;
}

void agregarInicioLista(ListaDoble* lista, const char* dato) {
    if (!lista || !dato) return;
    
    NodoLista* nuevo = crearNodo(dato);
    if (!nuevo) return;
    
    if (lista->cantidad == 0) {
        lista->cabeza = nuevo;
        lista->cola = nuevo;
    } else {
        nuevo->siguiente = lista->cabeza;
        lista->cabeza->anterior = nuevo;
        lista->cabeza = nuevo;
    }
    
    lista->cantidad++;
}

void mostrarLista(ListaDoble* lista) {
    if (!lista || lista->cantidad == 0) {
        printf("Lista vacía\n");
        return;
    }
    
    NodoLista* actual = lista->cabeza;
    while (actual) {
        printf("%s ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

void mostrarListaReversa(ListaDoble* lista) {
    if (!lista || lista->cantidad == 0) {
        printf("Lista vacía\n");
        return;
    }
    
    NodoLista* actual = lista->cola;
    while (actual) {
        printf("%s ", actual->dato);
        actual = actual->anterior;
    }
    printf("\n");
}

int tamanoLista(ListaDoble* lista) {
    return lista ? lista->cantidad : 0;
}

char* obtenerElemento(ListaDoble* lista, int indice) {
    if (!lista || indice < 0 || indice >= lista->cantidad) {
        return NULL;
    }
    
    NodoLista* actual = lista->cabeza;
    for (int i = 0; i < indice && actual; i++) {
        actual = actual->siguiente;
    }
    
    return actual ? actual->dato : NULL;
}

void eliminarElemento(ListaDoble* lista, int indice) {
    if (!lista || indice < 0 || indice >= lista->cantidad) {
        return;
    }
    
    NodoLista* actual = lista->cabeza;
    for (int i = 0; i < indice && actual; i++) {
        actual = actual->siguiente;
    }
    
    if (!actual) return;
    
    if (actual->anterior) {
        actual->anterior->siguiente = actual->siguiente;
    } else {
        lista->cabeza = actual->siguiente;
    }
    
    if (actual->siguiente) {
        actual->siguiente->anterior = actual->anterior;
    } else {
        lista->cola = actual->anterior;
    }
    
    free(actual->dato);
    free(actual);
    lista->cantidad--;
}

void destruirListaDoble(ListaDoble* lista) {
    if (!lista) return;
    
    NodoLista* actual = lista->cabeza;
    while (actual) {
        NodoLista* siguiente = actual->siguiente;
        free(actual->dato);
        free(actual);
        actual = siguiente;
    }
    
    free(lista);
}
