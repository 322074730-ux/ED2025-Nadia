#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h> 

typedef struct CharNode {
    char data;
    struct CharNode* next;
} CharNode;

typedef struct DoubleNode {
    double data;
    struct DoubleNode* next;
} DoubleNode;

typedef struct StringNode {
    char* data;
    struct StringNode* next;
} StringNode;

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

CharStack* createCharStack();
void destroyCharStack(CharStack* s);
bool charStackIsEmpty(CharStack* s);
void charStackPush(CharStack* s, char value);
char charStackPop(CharStack* s);
char charStackPeek(CharStack* s);
int charStackSize(CharStack* s);
void charStackDisplay(CharStack* s);

DoubleStack* createDoubleStack();
void destroyDoubleStack(DoubleStack* s);
bool doubleStackIsEmpty(DoubleStack* s);
void doubleStackPush(DoubleStack* s, double value);
double doubleStackPop(DoubleStack* s);
double doubleStackPeek(DoubleStack* s);
int doubleStackSize(DoubleStack* s);
void doubleStackDisplay(DoubleStack* s);

StringStack* createStringStack();
void destroyStringStack(StringStack* s);
bool stringStackIsEmpty(StringStack* s);
void stringStackPush(StringStack* s, const char* value);
char* stringStackPop(StringStack* s);
char* stringStackPeek(StringStack* s);
int stringStackSize(StringStack* s);

#endif
