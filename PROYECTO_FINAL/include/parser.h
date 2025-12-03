#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

// Estructura para un token
typedef struct {
    char* value;     
    int type;        
    int position;    
} Token;

// Tipos de tokens
typedef enum {
    TOKEN_NUMBER,    // Número (entero o decimal)
    TOKEN_OPERATOR,  // Operador: + - * / ^
    TOKEN_PAREN_OPEN, // Paréntesis abierto: (
    TOKEN_PAREN_CLOSE, // Paréntesis cerrado: )
    TOKEN_VARIABLE,  // Variable (letra)
    TOKEN_SPACE,     // Espacio (ignorar)
    TOKEN_UNKNOWN    // Token desconocido
} TokenType;

// Estructura para lista de tokens
typedef struct {
    Token* tokens;   
    int count;       
    int capacity;    
} TokenList;

// Funciones principales
TokenList* tokenizeExpression(const char* expression);
void freeTokenList(TokenList* list);
void printTokens(const TokenList* list);
bool validateTokens(const TokenList* list);

// Funciones auxiliares
bool isOperatorChar(char c);
bool isParenthesisChar(char c);
bool isVariableChar(char c);
bool isNumberChar(char c, bool first);
TokenType getTokenType(const char* str);
char* tokenTypeToString(TokenType type);

#endif
