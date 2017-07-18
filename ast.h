/*
Etapa 5 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#ifndef AST_H_
#define AST_H_

#include "hash.h"

FILE* OUT_FILE;

#define NUM_CHILDREN 4

#define AST_PARENTHESES		256
#define AST_ADD				'+'
#define AST_SUB				'-'
#define AST_MUL				'*'
#define AST_DIV				'/'
#define AST_GT				'>'
#define AST_LT				'<'
#define AST_LE				260
#define AST_GE				261
#define AST_EQ				262
#define AST_NE				263
#define AST_AND				264
#define AST_OR				265
#define AST_NOT				266

//3 tipos diferentes de identificadores
#define AST_ID				270
#define AST_ID_VECTOR		271
#define AST_ID_CALL			272
//--

//Há	três	tipos	de	literais: inteiros,	caracteres,	strings
#define AST_LITERAL			273
//--

#define AST_PARAM_LIST		280

#define AST_WHEN			290
#define AST_WHEN_ELSE		291
#define AST_WHILE			292
#define AST_FOR				293

#define AST_ATRIB				300
#define AST_ATRIB_VECTOR		301

#define AST_PROGRAM			400

#define AST_VAR_DEC			500 //Variavel declaração
#define AST_VEC_DEC			501 //Vetor declaração 
#define AST_VEC_INIT			502 //Vetor inicialização
#define AST_FUNC_DEC		503 //Função declaração

//5 tipos de dados para declarações
// SEIS TIPOS DE DADOS PARA DECLARAÇÕES MWHAHAHA (droga D:)
#define AST_BYTE				600
#define AST_SHORT			601
#define AST_LONG				602
#define AST_FLOAT			603
#define AST_DOUBLE			604
#define AST_BOOL			605
//--

#define AST_PRINT_ARGS		700
#define AST_ARGS_LIST			701
#define AST_DEC_ARGS			702

#define AST_COMMAND_LIST	800
#define AST_READ				801
#define AST_PRINT			802
#define AST_RETURN			803
#define AST_COMMANDS		804

typedef struct ast_node {
	int type;
	int lineNumber;
	HASH_NODE *symbol;
	struct ast_node *children[NUM_CHILDREN];
} AST_NODE;

AST_NODE* ast;

AST_NODE* ast_insert(int type, HASH_NODE *symbol, AST_NODE* c0, AST_NODE* c1, AST_NODE* c2, AST_NODE* c3);
void ast_print(AST_NODE *node);
void ast_print_tree(AST_NODE *root);

#endif
