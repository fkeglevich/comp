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

/*
	REVISAR ESSA LISTA DE TACS
	De acordo com a especificação ele quer algo assim:

	TAC_SYMBOL,	 TAC_MOVE,	 TAC_ADD,	 TAC_MUL,	 ...,	 TAC_LABEL,	 TAC_BEGINFUN,	
	TAC_ENDFUN,	 TAC_IFZ,	 TAC_JUMP,	 TAC_CALL,	 TAC_ARG,	 TAC_RET,	 TAC_PRINT,	
	TAC_READ

	DEIXEI UMAS QUE PEGUEI DO ~~EXEMPLO~~
*/

#define TAC_ADD 	    1
#define TAC_SUB		    2
#define TAC_MUL 	    3
#define TAC_DIV 	    4

#define TAC_DATABYTE 	5 
#define TAC_DATASHORT 	6 
#define TAC_DATALONG 	43 
#define TAC_DATAFLOAT 	44 
#define TAC_DATADOUBLE 	45 
#define TAC_DATABOOL 	7

#define TAC_INTEGER     9 
#define TAC_BOOLEAN     11
#define TAC_CHARACTER   12
#define TAC_STRING 	    13

#define TAC_READ       14
#define TAC_PRINT     15
#define TAC_RETURN      16

#define TAC_LE 		    17
#define TAC_GE 		    18
#define TAC_EQ 		    19
#define TAC_NE 		    20
#define TAC_AND 	    21
#define TAC_OR 		    22

#define TAC_MOV		    23
#define TAC_MOV_VET	    24
#define TAC_MAIOR	    25
#define TAC_MENOR   	26
#define TAC_LABEL	    27
#define TAC_BEGINFUN	28
#define TAC_ENDFUN	    29
#define TAC_CALL	    30
#define TAC_JUMP	    31
#define TAC_VETOR	    32
#define TAC_VARIABLE	33
#define TAC_JFALSE	    34
#define TAC_SALTO	    35
#define TAC_DECLARE 	36
#define TAC_DECLAREVET	37
#define TAC_LISTAPARAM	38
#define TAC_PARAMETRO	39
#define TAC_DEC_POINTER 40
#define TAC_VAR_VET	    41

#define TAC_LITERAL 	    42

typedef struct tac_structure{
	int type; //operaçao
	HASH_NODE *target;
	HASH_NODE *op1;
	HASH_NODE *op2;
	
	//DUPLAMENTCHY ENCADEADA
	struct tac_structure* prev; 
	struct tac_structure* next;
} TAC;

#endif

TAC* tacCreate(int type, HASH_NODE *target, HASH_NODE *op1, HASH_NODE *op2);
TAC* makeBinOp(TAC *code0, TAC *code1,int type);
TAC* tacJoin(TAC* l1, TAC* l2); 
TAC* tacCodeGen(AST_NODE* root);
TAC *tacReverse(TAC *last);
void tacPrintList(TAC* tac);
void tacPrintSingle(TAC* tac);
