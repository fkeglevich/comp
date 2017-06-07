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

void semanticError();
void checkDeclr(AST_NODE *node);
void checkIdentifier(HASH_NODE *node);
void checkChildren(AST_NODE *node);
void checkProgram(AST_NODE *node);

#endif