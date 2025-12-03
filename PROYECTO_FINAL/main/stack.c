#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Pila de caracteres 
CharStack* createCharStack() {
    CharStack* s }=(CharStack*)malloc(sizeof(CharStack));
    if (s == NULL){
        return NULL;
    }
    s->top=NULL;
    s->size=0;
    return s;
}
void destroyCharStack(CharStack* s){
    if (s==NULL) return;
        while (!charStackIsEmpty(s)){
        charStackPop(s);
    }
    free(s);
}
bool charStackIsEmpty(CharStack* s){
    return s==NULL || s->top==NULL;
}
void charStackPush(CharStack* s, char value){
    if (s==NULL) return;
    CharNode* newNode=(CharNode*)malloc(sizeof(CharNode));
    if (newNode==NULL){
        printf("Error: Memoria insuficiente\n");
        return;
    }
    newNode->data=value;
    newNode->next=s->top;
    s->top=newNode;
    s->size++;
}
char charStackPop(CharStack* s){
    if (charStackIsEmpty(s)){
        printf("Error: Pila de caracteres vacía\n");
        return '\0';
    }
    CharNode* temp=s->top;
    char value=temp->data;
    s->top=temp->next;
    free(temp);
    s->size--;
    return value;
}
char charStackPeek(CharStack* s){
    if (charStackIsEmpty(s)){
        return '\0';
    }
    return s->top->data;
}
int charStackSize(CharStack* s){
    return (s == NULL) ? 0 : s->size;
}
void charStackDisplay(CharStack* s){
    if (charStackIsEmpty(s)){
        printf("Pila de caracteres: vacía\n");
        return;
    }
    printf("Pila de caracteres (%d elementos): [", s->size);
    CharNode* current = s->top;
    while (current != NULL) {
        printf("%c", current->data);
        if (current->next != NULL) printf(", ");
        current = current->next;
    }
    printf("]\n");
}

// Pila de numeros versión dinamica
DoubleStack* createDoubleStack() {
    DoubleStack* s=(DoubleStack*)malloc(sizeof(DoubleStack));
    if (s == NULL){
        return NULL;
    }
    s->top=NULL;
    s->size=0;
    return s;
}
void destroyDoubleStack(DoubleStack* s){
    if (s==NULL) return;   
    while (!doubleStackIsEmpty(s)){
        doubleStackPop(s);
    }
    free(s);
}
bool doubleStackIsEmpty(DoubleStack* s){
    return s==NULL || s->top==NULL;
}
void doubleStackPush(DoubleStack* s, double value){
    if (s==NULL) return;   
    DoubleNode* newNode=(DoubleNode*)malloc(sizeof(DoubleNode));
    if (newNode==NULL){
        printf("Error: Memoria insuficiente\n");
        return;
    }
    newNode->data=value;
    newNode->next=s->top;
    s->top=newNode;
    s->size++;
}
double doubleStackPop(DoubleStack* s){
    if (doubleStackIsEmpty(s)){
        printf("Error: Pila de números vacía\n");
        return 0.0;
    }   
    DoubleNode* temp=s->top;
    double value=temp->data;
    s->top=temp->next;
    free(temp);
    s->size--;
    return value;
}
double doubleStackPeek(DoubleStack* s){
    if (doubleStackIsEmpty(s)){
        return 0.0;
    }
    return s->top->data;
}
int doubleStackSize(DoubleStack* s){
    return (s==NULL) ? 0 : s->size;
}
void doubleStackDisplay(DoubleStack* s) {
    if (doubleStackIsEmpty(s)) {
        printf("Pila de números: vacía\n");
        return;
    }   
    printf("Pila de números (%d elementos): [", s->size);
    DoubleNode* current = s->top;
    while (current != NULL) {
        printf("%.2f", current->data);
        if (current->next != NULL) printf(", ");
        current = current->next;
    }
    printf("]\n");
}
// pila de cadenas implementacion dinamica
StringStack* createStringStack() {
    StringStack* s=(StringStack*)malloc(sizeof(StringStack));
    if (s==NULL){
        return NULL;
    }
    s->top=NULL;
    s->size=0;
    return s;
}
void destroyStringStack(StringStack* s) {
    if (s==NULL) return;   
    while (!stringStackIsEmpty(s)) {
        char* str = stringStackPop(s);
        if (str != NULL) {
            free(str);
        }
    }
    free(s);
}
bool stringStackIsEmpty(StringStack* s) {
    return s == NULL || s->top == NULL;
}
void stringStackPush(StringStack* s, const char* value) {
    if (s == NULL || value == NULL) return;   
    StringNode* newNode = (StringNode*)malloc(sizeof(StringNode));
    if (newNode == NULL) {
        printf("Error: Memoria insuficiente\n");
        return;
    }
    // Crear copia de la cadena
    newNode->data = (char*)malloc(strlen(value) + 1);
    if (newNode->data == NULL) {
        free(newNode);
        printf("Error: Memoria insuficiente\n");
        return;
    }
    strcpy(newNode->data, value);
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}

char* stringStackPop(StringStack* s) {
    if (stringStackIsEmpty(s)) {
        printf("Error: Pila de cadenas vacía\n");
        return NULL;
    }
    StringNode* temp = s->top;
    char* value = temp->data;
    s->top = temp->next;
    free(temp);
    s->size--;   
    return value;
}
char* stringStackPeek(StringStack* s) {
    if (stringStackIsEmpty(s)) {
        return NULL;
    }
    return s->top->data;
}
int stringStackSize(StringStack* s) {
    return (s==NULL) ? 0 : s->size;
}
