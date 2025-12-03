#ifndef DLIST_H
#define DLIST_H

// Nodo de lista doblemente enlazada
typedef struct _NodoLista {
    char* dato;
    struct _NodoLista* anterior;
    struct _NodoLista* siguiente;
} NodoLista;

// Lista doblemente enlazada
typedef struct {
    NodoLista* cabeza;
    NodoLista* cola;
    int cantidad;
} ListaDoble;

// Funciones de lista doble
ListaDoble* crearListaDoble();
void destruirListaDoble(ListaDoble* lista);
void agregarFinalLista(ListaDoble* lista, const char* dato);
void agregarInicioLista(ListaDoble* lista, const char* dato);
void mostrarLista(ListaDoble* lista);
void mostrarListaReversa(ListaDoble* lista);
int tamanoLista(ListaDoble* lista);
char* obtenerElemento(ListaDoble* lista, int indice);
void eliminarElemento(ListaDoble* lista, int indice);

#endif
