/*
Etapa 4 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include "semantic.h"

void semanticError(const char * msg, int lineNumber)
{
	printf("Erro semantico (linha: %d): %s\n", lineNumber, msg);
	exit(4);
}

void checkIdentifierExists(HASH_NODE *node, int lineNumber)
{
	if (node->dataNature == NATURE_UNKNOWN)
		semanticError("Identificador nao-declarado!", lineNumber);
}

void checkNature(HASH_NODE *node, int expectedNature, int lineNumber)
{
	if (node->dataNature != expectedNature)
		semanticError("Atribuicao de tipos incompativeis", lineNumber);
}

/*
#define DATATYPE_UNKNOWN	0
#define DATATYPE_BYTE		1
#define DATATYPE_SHORT		2
#define DATATYPE_LONG		3
#define DATATYPE_FLOAT		4
#define DATATYPE_DOUBLE		5
#define DATATYPE_BOOL		6
#define DATATYPE_STRING		7
*/

int compareDataTypes(int a, int b, int lineNumber)
{
	if (a == DATATYPE_STRING || b == DATATYPE_STRING)
		semanticError("Literal String nao pode ser usada aqui", lineNumber);

	//esse if é uma checagem extra de segurança (em tese não deveria ser necessário, mas NÉ)
	if (a == DATATYPE_UNKNOWN || b == DATATYPE_UNKNOWN)
		semanticError("Datatype invalido!", lineNumber);

	if (a != DATATYPE_BOOL && b != DATATYPE_BOOL)
	{
		if (a > b) 
			return a;
		else
			return b;
	}
	else
	{
		if (a == DATATYPE_BOOL && b == DATATYPE_BOOL)
			return DATATYPE_BOOL;
		else
			semanticError("Valor booleano nao pode ser usado aqui!", lineNumber);
	}
	return DATATYPE_UNKNOWN;
}

int getDataTypeFromVarType(AST_NODE *node)
{
	switch(node->type)
	{
		case AST_BYTE:		return DATATYPE_BYTE;
		case AST_SHORT:		return DATATYPE_SHORT; 
		case AST_LONG:		return DATATYPE_LONG; 
		case AST_FLOAT:		return DATATYPE_FLOAT; 
		case AST_DOUBLE:	return DATATYPE_DOUBLE; 				
		case AST_BOOL:		return DATATYPE_BOOL; 
		default:				semanticError("Tipo de variavel invalido!", node->lineNumber);
	}
	return DATATYPE_UNKNOWN;
}

/*
lista_parametros
		: declara_parametro					{$$ = $1;}
		| declara_parametro ',' lista_parametros		{$$ = ast_insert(AST_ARGS_LIST, NULL, $1, $3, NULL, NULL);}
		|									{$$ = NULL;}
		;

declara_parametro: tipo_variavel TK_IDENTIFIER		{$$ = ast_insert(AST_DEC_ARGS, $2, $1, NULL, NULL, NULL);};

chama_parametros
		: expressao							{$$ = $1;}
		| expressao ',' chama_parametros			{$$ = ast_insert(AST_PARAM_LIST, NULL, $1, $3, NULL, NULL);}
		|									{$$ = NULL;}
		;

*/
void checkParamPair(AST_NODE *declared, AST_NODE *called)
{
	int declaredDataType;

	if (declared == NULL && called == NULL)
		return;

	if (declared == NULL && called != NULL)
		semanticError("Numero de parametros errado!", called->lineNumber);

	if (declared != NULL && called == NULL)
		semanticError("Numero de parametros errado!", called->lineNumber);

	if (declared->type == AST_DEC_ARGS && called->type != AST_PARAM_LIST)
	{
		declaredDataType = getDataTypeFromVarType(declared->children[0]);
		compareDataTypes(declaredDataType, getExpressionDataType(called), called->lineNumber);
		return;
	}

	if (declared->type == AST_ARGS_LIST && called->type == AST_PARAM_LIST)
	{
		checkParamPair(declared->children[0], called->children[0]);
		checkParamPair(declared->children[1], called->children[1]);
		return;
	}

	semanticError("Parametros incompativeis!", called->lineNumber);
}

int getExpressionDataType(AST_NODE *node)
{
	int res;
	switch(node->type)
	{
		case AST_PARENTHESES:
			return getExpressionDataType(node->children[0]);

		case AST_ADD:
		case AST_SUB:
		case AST_MUL:
		case AST_DIV:
			return compareDataTypes(getExpressionDataType(node->children[0]), getExpressionDataType(node->children[1]), node->lineNumber);

		case AST_GT:
		case AST_LT:
		case AST_LE:
		case AST_GE:
			res = compareDataTypes(getExpressionDataType(node->children[0]), getExpressionDataType(node->children[1]), node->lineNumber);
			if (res == DATATYPE_UNKNOWN || res == DATATYPE_BOOL)
				semanticError("Tipos incompativeis para comparacao", node->lineNumber);
			return DATATYPE_BOOL;

		case AST_EQ:
		case AST_NE:
			return DATATYPE_BOOL;

		case AST_AND:
		case AST_OR:
			if (compareDataTypes(getExpressionDataType(node->children[0]), getExpressionDataType(node->children[1]), node->lineNumber) != DATATYPE_BOOL)
				semanticError("Nao eh possivel fazer essa comparacao!", node->lineNumber);
			return DATATYPE_BOOL;

		case AST_NOT:
			if (getExpressionDataType(node->children[0]) != DATATYPE_BOOL)
				semanticError("Operador NOT em um tipo incompativel", node->lineNumber);
			return DATATYPE_BOOL;

		case AST_ID:
			checkIdentifierExists(node->symbol, node->lineNumber);
			if (node->symbol->dataNature != NATURE_VAR)
				semanticError("O identificador nao eh uma variavel", node->lineNumber);
			return node->symbol->dataType;

		case AST_ID_VECTOR:
			checkIdentifierExists(node->symbol, node->lineNumber);
			if (node->symbol->dataNature != NATURE_VEC)
				semanticError("O identificador nao eh um vetor", node->lineNumber);
			if (compareDataTypes(getExpressionDataType(node->children[0]), DATATYPE_LONG, node->lineNumber) != DATATYPE_LONG)
				semanticError("O indice do vetor precisa ser um inteiro!", node->lineNumber);
			return node->symbol->dataType;
		
		//| TK_IDENTIFIER '(' chama_parametros ')'	{$$ = ast_insert(AST_ID_CALL, $1, $3, NULL, NULL, NULL);}
		case AST_ID_CALL:
			checkIdentifierExists(node->symbol, node->lineNumber);
			if (node->symbol->dataNature != NATURE_FUNC)
				semanticError("O identificador nao eh uma funcao", node->lineNumber);
			checkParamPair(node->symbol->funcParam, node->children[0]);
			return node->symbol->dataType;

		case AST_LITERAL:
			switch(node->symbol->type)
			{
				case SYMBOL_LIT_INT:		return DATATYPE_LONG;
				case SYMBOL_LIT_REAL:	return DATATYPE_DOUBLE;
				case SYMBOL_LIT_CHAR:	return DATATYPE_BYTE;
				case SYMBOL_LIT_STRING:	return DATATYPE_STRING;
				case SYMBOL_LIT_TRUE:
				case SYMBOL_LIT_FALSE:
					return DATATYPE_BOOL;
			}
			break;
	}
}

void checkDeclr(AST_NODE *node)
{
	if (node->symbol->dataNature != NATURE_UNKNOWN)
		semanticError("Indentificador ja foi declarado!", node->lineNumber);
	
	switch(node->type)
	{
		case AST_VAR_DEC: 	node->symbol->dataNature = NATURE_VAR; break;
		case AST_VEC_DEC:	node->symbol->dataNature = NATURE_VEC; break;
		case AST_FUNC_DEC:
			node->symbol->dataNature = NATURE_FUNC;
			node->symbol->funcParam = node->children[1];
			break;
	}

	node->symbol->dataType = getDataTypeFromVarType(node->children[0]);
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
		
		case AST_ATRIB:
			checkIdentifierExists(node->symbol, node->lineNumber);
			checkNature(node->symbol, NATURE_VAR, node->lineNumber);
			break;

		case AST_READ:
			checkIdentifierExists(node->symbol, node->lineNumber);
			break;

		default:
			checkChildren(node);
			break;
	}
}	