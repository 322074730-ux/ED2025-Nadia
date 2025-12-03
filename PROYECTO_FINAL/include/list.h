#ifndef LIST_H
#define LIST_H

// Nodo de lista simple
typedef struct _NodoSimple {
    char* valor;
    struct _NodoSimple* proximo;
} NodoSimple;

// Lista simple
typedef struct {
    NodoSimple* inicio;
    NodoSimple* fin;
    int total;
} ListaSimple;

// Funciones de lista simple
ListaSimple* crearListaSimple();
void liberarListaSimple(ListaSimple* lista);
void agregarListaSimple(ListaSimple* lista, const char* valor);
void imprimirListaSimple(ListaSimple* lista);
int contarListaSimple(ListaSimple* lista);

#endif
