/*
Etapa 4 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include "ast.h"

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4	
#define SYMBOL_LIT_TRUE 5	
#define SYMBOL_LIT_FALSE 6	
#define SYMBOL_IDENTIFIER 7	

void semanticError();
void checkDeclr(AST_NODE *node);
int compareDataTypes(int a, int b);
int getDataTypeFromVarType(AST_NODE *node);
void checkParamPair(AST_NODE *declared, AST_NODE *called);
int getExpressionDataType(AST_NODE *node);
void checkIdentifier(HASH_NODE *node);
void checkChildren(AST_NODE *node);
void checkProgram(AST_NODE *node);

#endif