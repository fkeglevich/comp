/*
Etapa 4 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include "semantic.h"

void semanticError()
{
	printf("Erro semantico!\n");
	exit(4);
}

void checkDeclr(AST_NODE *node)
{
	if (node->symbol->dataNature != NATURE_UNKNOWN)
		semanticError();

	switch(node->type)
	{
		case AST_VAR_DEC:	node->symbol->dataNature = NATURE_VAR; break;
		case AST_VEC_DEC:	node->symbol->dataNature = NATURE_VEC; break;
		case AST_FUNC_DEC:	node->symbol->dataNature = NATURE_FUNC; break;
	}	
}

void checkChildren(AST_NODE *node)
{
	int i;
	for (i = 0; i < NUM_CHILDREN; i++)
	{
		checkProgram(node->children[i]);	
	}
}

void checkProgram(AST_NODE *node)
{
	if (node == NULL) return;

	switch(node->type)
	{
		case AST_PROGRAM:
			checkChildren(node);
			break;

		case AST_VAR_DEC:
		case AST_VEC_DEC:
		case AST_FUNC_DEC:
			checkDeclr(node);
			break;

		default:
			checkChildren(node);
			break;
	}
}	