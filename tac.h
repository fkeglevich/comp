/*
Etapa 5 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#ifndef __TAC_HEADER__
#define __TAC_HEADER__

#include "hash.h"
#include "ast.h"

#define TAC_LITERAL 	1  //ok
#define TAC_ADD    		2  //ok
#define TAC_SUB    		3  //ok
#define TAC_MUL    		4  //ok
#define TAC_DIV    		5  //ok
#define TAC_GT 	   		6  //ok
#define TAC_LT 	   		7  //ok
#define TAC_LE	   		8  //ok
#define TAC_GE     		9  //ok
#define TAC_EQ 	   		10 //ok
#define TAC_NE	   		11 //ok
#define TAC_RETURN		20 //ok
#define TAC_IFZ			28 //ok
#define TAC_LABEL		29
#define TAC_JUMP		30 //ok
#define TAC_IFLESSEQ	31
#define TAC_INC			32 //ok
#define TAC_MOVE		33 //ok
#define TAC_BEGIN_FUNC 	34
#define TAC_END_FUNC 	36
#define TAC_VAR 		24 //ok
#define TAC_VEC_WRITE	18
#define TAC_ATRIB		17 //ok
#define TAC_ID_VECTOR	19
#define TAC_ARRAY_VALUE 23
#define TAC_VEC 		25
#define TAC_PRINT		21
#define TAC_AND	   		12 //ok
#define TAC_OR	   		13 //ok
#define TAC_CALL		26
#define TAC_ID_CALL		27 //ok
#define TAC_ARG_RECEIVE 35

#define TAC_NOT	   		14
#define TAC_READ		22

typedef struct tac_structure{
	int type; //operaçao
	int posicaoParam;
	HASH_NODE *res;
	HASH_NODE *op1;
	HASH_NODE *op2;
	
	//DUPLAMENTCHY ENCADEADA
	struct tac_structure* prev; 
	struct tac_structure* next;
} TAC;

#endif

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2, int posParam);
TAC* tacJoin(TAC *l1 ,TAC *l2);
void tacPrintBack(TAC *last);
void tacPrintForward(TAC *first);
TAC* tacReverse(TAC* tac);
TAC * tacGenerate(AST_NODE *node);