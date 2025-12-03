#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// Nodo para pila de caracteres
typedef struct CharNode {
    char data;
    struct CharNode* next;
} CharNode;

// Nodo para pila de números
typedef struct DoubleNode {
    double data;
    struct DoubleNode* next;
} DoubleNode;

// Nodo para pila de cadenas
typedef struct StringNode {
    char* data;
    struct StringNode* next;
} StringNode;

// Estructuras principales de pilas
typedef struct {
    CharNode* top;
    int size;
} CharStack;

typedef struct {
    DoubleNode* top;
    int size;
} DoubleStack;

typedef struct {
    StringNode* top;
    int size;
} StringStack;

// Pila de caracteres
CharStack* createCharStack();
void destroyCharStack(CharStack* s);
bool charStackIsEmpty(CharStack* s);
void charStackPush(CharStack* s, char value);
char charStackPop(CharStack* s);
char charStackPeek(CharStack* s);
int charStackSize(CharStack* s);
void charStackDisplay(CharStack* s);

// Pila de números
DoubleStack* createDoubleStack();
void destroyDoubleStack(DoubleStack* s);
bool doubleStackIsEmpty(DoubleStack* s);
void doubleStackPush(DoubleStack* s, double value);
double doubleStackPop(DoubleStack* s);
double doubleStackPeek(DoubleStack* s);
int doubleStackSize(DoubleStack* s);
void doubleStackDisplay(DoubleStack* s);

// Pila de cadenas
StringStack* createStringStack();
void destroyStringStack(StringStack* s);
bool stringStackIsEmpty(StringStack* s);
void stringStackPush(StringStack* s, const char* value);
char* stringStackPop(StringStack* s);
char* stringStackPeek(StringStack* s);
int stringStackSize(StringStack* s);

#endif
