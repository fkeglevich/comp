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

void checkIdentifierExists(HASH_NODE *node)
{
	if (node->dataNature == NATURE_UNKNOWN)
		semanticError();
}

//Função que checa a declaração
void checkDeclr(AST_NODE *node)
{
	//Se a variável for declarada duas vezes dá erro
	if (node->symbol->dataNature != NATURE_UNKNOWN)
		semanticError();
	
	switch(node->type)
	{
		case AST_VAR_DEC: 	node->symbol->dataNature = NATURE_VAR; break;
		case AST_VEC_DEC:	node->symbol->dataNature = NATURE_VEC; break;
		case AST_FUNC_DEC:	node->symbol->dataNature = NATURE_FUNC; break;
	}

	switch(node->children[0]->type)
	{
		case AST_BYTE:		node->symbol->dataType = DATATYPE_BYTE; break;
		case AST_SHORT:		node->symbol->dataType = DATATYPE_SHORT; break;
		case AST_LONG:		node->symbol->dataType = DATATYPE_LONG; break;
		case AST_FLOAT:		node->symbol->dataType = DATATYPE_FLOAT; break;
		case AST_DOUBLE:	node->symbol->dataType = DATATYPE_DOUBLE; break;				
		case AST_BOOL:		node->symbol->dataType = DATATYPE_BOOL; break;
		default:				semanticError(); break;
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

//TK_IDENTIFIER '=' expressao	
//tem que ser var
//tem que existir
//tem que ter tipos compativeis, number/float <--> number/float ou bool <-> bool

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
		
		case AST_READ:
			checkIdentifierExists(node->symbol);
			break;

		default:
			checkChildren(node);
			break;
	}
}	