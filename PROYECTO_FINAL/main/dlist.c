#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Crear nueva lista doble
ListaDoble* crearListaDoble() {
    ListaDoble* lista = (ListaDoble*)malloc(sizeof(ListaDoble));
    if (!lista) return NULL;
    
    lista->cabeza = NULL;
    lista->cola = NULL;
    lista->cantidad = 0;
    return lista;
}

// Crear nuevo nodo
NodoLista* crearNodo(const char* dato) {
    NodoLista* nodo = (NodoLista*)malloc(sizeof(NodoLista));
    if (!nodo) return NULL;
    
    nodo->dato = strdup(dato);
    if (!nodo->dato) {
        free(nodo);
        return NULL;
    }
    
    nodo->anterior = NULL;
    nodo->siguiente = NULL;
    return nodo;
}

// Agregar al final de la lista
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

// Agregar al inicio de la lista
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

// Mostrar lista
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

// Mostrar lista en reversa
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

// Obtener tamaño de la lista
int tamanoLista(ListaDoble* lista) {
    return lista ? lista->cantidad : 0;
}

// Obtener elemento por índice
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

// Eliminar elemento por índice
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

// Destruir lista completa
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
