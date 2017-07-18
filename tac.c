/*
Etapa 5 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include "semantic.h"
#include "tac.h"
#include "ast.h"
#include "hash.h"
#include "y.tab.h"


// local functions
HASH_NODE* makeTemp();
HASH_NODE* makeLabel();
void printTacType(int type);
TAC* makeOpBin(int op, TAC** code);
TAC* makeWhen(TAC** code);
TAC* makeElse(TAC** code);
TAC* makeWhile(TAC** code);
TAC* makeFor(HASH_NODE* identifier, TAC** code);
TAC* makeAtrib(HASH_NODE* identifier, TAC** code);
TAC* makeAtribVec(HASH_NODE* identifier, TAC** code);
TAC* makeFuncDef(HASH_NODE* identifier, TAC** code, AST_NODE *funcDef);
TAC* makeIdCall(AST_NODE *funcCall);
TAC* makeReturn(TAC** code);
TAC* makeRead(HASH_NODE* identifier);
TAC* makePrint(AST_NODE* print, TAC** code);
TAC* makeVar(HASH_NODE* identifier, TAC** code);
TAC* makeVec(AST_NODE* astvec, TAC** code);
TAC* makeIdVec(HASH_NODE* identifier, TAC** code);

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2, int posicaoParam){
	TAC* newTac;

	if(!(newTac = (TAC*) calloc(1, sizeof(TAC))) ){
		fprintf(stderr, "Erro ao criar TAC! \n");
		exit(1);
	}
	newTac->type = type;
	newTac->res = res;
	newTac->op1 = op1;
	newTac->op2 = op2;
	newTac->prev = NULL;
	newTac->next = NULL;
	newTac->posicaoParam = posicaoParam;

	return newTac;
}

TAC* tacJoin(TAC *l1 ,TAC *l2){
	TAC *tac;
	
	if(!l1) { return l2; }	
	if(!l2) { return l1; }
	for(tac = l2; tac->prev; tac=tac->prev){
		; // go to root
	}
	tac->prev = l1;
	l1->next = tac;
	return l2;
}

TAC* tacReverse(TAC *tac){	
	TAC *t = NULL;
	for(t=tac;t->prev;t=t->prev){t->prev->next = t;}
	return t;
}

void tacPrintBack(TAC *last){
	TAC *tac;
	for(tac = last; tac; tac=tac->prev){
		if (tac->type != TAC_SYMBOL){
			fprintf(stderr, "TAC(");
			printTacType(tac->type);

			if(tac->res){ 
				fprintf(stderr, ",%s", tac->res->text); 
			}else if(tac->posicaoParam && tac->type == TAC_ID_CALL){
				fprintf(stderr, ",arg%d", tac->posicaoParam); 
			}else{ 
				fprintf(stderr, ",");
			}

			if(tac->op1){ 
				fprintf(stderr, ",%s", tac->op1->text); 
			}else if(tac->posicaoParam && tac->type == TAC_ARG_RECEIVE){
				fprintf(stderr, ",arg%d", tac->posicaoParam); 
			}else{
				fprintf(stderr, ",");
			}

			if(tac->op2){ 
				fprintf(stderr, ",%s", tac->op2->text); 
			}else{ 
				fprintf(stderr, ",");
			}

			fprintf(stderr, ")\n");
		}
	}
}

void tacPrintForward(TAC *first){
	TAC *tac;
	for(tac = first; tac; tac=tac->next){
		if (tac->type != TAC_SYMBOL){
			fprintf(stderr, "TAC(");
			printTacType(tac->type);

			if(tac->res){ 
				fprintf(stderr, ",%s", tac->res->text); 
			}else if(tac->posicaoParam && tac->type == TAC_ID_CALL){
				fprintf(stderr, ",arg%d", tac->posicaoParam); 
			}else{ 
				fprintf(stderr, ",");
			}

			if(tac->op1){ 
				fprintf(stderr, ",%s", tac->op1->text); 
			}else if(tac->posicaoParam && tac->type == TAC_ARG_RECEIVE){
				fprintf(stderr, ",arg%d", tac->posicaoParam); 
			}else{
				fprintf(stderr, ",");
			}

			if(tac->op2){ 
				fprintf(stderr, ",%s", tac->op2->text); 
			}else{ 
				fprintf(stderr, ",");
			}

			fprintf(stderr, ")\n");
		}
	}
	
}

void printTacType(int type){
	switch(type){
		case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
		case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
		case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
		case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;
		case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
		case TAC_GT: fprintf(stderr, "TAC_GT"); break;
		case TAC_LT: fprintf(stderr, "TAC_LT"); break;
		case TAC_LE: fprintf(stderr, "TAC_LE"); break;
		case TAC_GE: fprintf(stderr, "TAC_GE"); break;
		case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
		case TAC_NE: fprintf(stderr, "TAC_NE"); break;
		case TAC_AND: fprintf(stderr, "TAC_AND"); break;
		case TAC_OR: fprintf(stderr, "TAC_OR"); break;
		case TAC_ATRIB: fprintf(stderr, "TAC_ATRIB"); break;
		case TAC_VEC_WRITE: fprintf(stderr, "TAC_VEC_WRITE"); break; //??
		case TAC_ID_VECTOR: fprintf(stderr, "TAC_ID_VECTOR"); break; //??
		case TAC_RETURN: fprintf(stderr, "TAC_RETURN"); break;
		case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;
		case TAC_READ: fprintf(stderr, "TAC_READ"); break;
		case TAC_CALL: fprintf(stderr, "TAC_CALL"); break;
		case TAC_ID_CALL: fprintf(stderr, "TAC_ID_CALL"); break;
		case TAC_ARG_RECEIVE: fprintf(stderr, "TAC_ARG_RECEIVE"); break;
		case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); break;
		case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
		case TAC_BEGIN_FUNC: fprintf(stderr, "TAC_BEGIN_FUNC"); break;
		case TAC_END_FUNC: fprintf(stderr, "TAC_END_FUNC"); break;
		case TAC_JUMP: fprintf(stderr, "TAC_JUMP"); break;
		case TAC_IFLESSEQ: fprintf(stderr, "TAC_IFLESSEQ"); break;
		case TAC_INC: fprintf(stderr, "TAC_INC"); break;
		case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;
		case TAC_ARRAY_VALUE: fprintf(stderr, "TAC_ARRAY_VALUE"); break;
		case TAC_VAR: fprintf(stderr, "TAC_VAR"); break;
		case TAC_VEC: fprintf(stderr, "TAC_VEC"); break;
		default: fprintf(stderr, "Type not found"); break;
	}
}

TAC* tacGenerate(AST_NODE *node)
{
	TAC *code[NUM_CHILDREN];
	TAC *result = NULL;
	int i = 0;

	if(!node) return NULL; 
	
	for(i=0; i<NUM_CHILDREN; i++) code[i] = tacGenerate(node->children[i]);
	
	switch(node->type)
	{
		case AST_LITERAL: 
		case AST_DEC_ARGS:
		case AST_ID:
			result = tacCreate(TAC_SYMBOL, node->symbol, NULL, NULL, 0); break;

		case AST_ID_VECTOR: result = makeIdVec(node->symbol,code); break;
		case AST_ADD: result = makeOpBin(TAC_ADD, code); break;	
		case AST_SUB: result = makeOpBin(TAC_SUB, code); break;		
		case AST_MUL: result = makeOpBin(TAC_MUL, code); break;	
		case AST_DIV: result = makeOpBin(TAC_DIV, code); break;	
		case AST_GT: result = makeOpBin(TAC_GT, code); break;	
		case AST_LT: result = makeOpBin(TAC_LT, code); break;	
		case AST_LE: result = makeOpBin(TAC_LE, code); break;	
		case AST_GE: result = makeOpBin(TAC_GE, code); break;	
		case AST_EQ: result = makeOpBin(TAC_EQ, code); break;	
		case AST_NE: result = makeOpBin(TAC_NE, code); break;	
		case AST_AND: result = makeOpBin(TAC_AND, code); break;	
		case AST_OR: result = makeOpBin(TAC_OR, code); break;

		case AST_WHEN: result = makeWhen(code); break;
		case AST_WHEN_ELSE: result = makeElse(code); break;
		case AST_WHILE: result = makeWhile(code); break;
		case AST_FOR: result = makeFor(node->symbol,code); break;
		case AST_ATRIB: result = makeAtrib(node->symbol,code); break;
		case AST_ATRIB_VECTOR: result = makeAtribVec(node->symbol,code); break;
		case AST_FUNC_DEC: result = makeFuncDef(node->symbol, code, node); break;
		
		case AST_ID_CALL: result = makeIdCall(node); break;
		case AST_RETURN: result = makeReturn(code); break;
		case AST_READ: result = makeRead(node->symbol); break;
		case AST_PRINT: result = makePrint(node, code); break;
		case AST_VAR_DEC: result = makeVar(node->symbol, code); break;
		case AST_VEC_DEC: result = makeVec(node, code); break;

		case AST_COMMAND_LIST: result = code[0]; break;
		case AST_COMMANDS: result = tacJoin(code[0],code[1]); break;
		case AST_PARENTHESES: result = code[0]; break;	
		default: result = tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]);
	}
	return result;
}

TAC* makeOpBin(int op, TAC** code)
{
	TAC *newTac = tacCreate(op, makeTemp(), code[0] ? code[0]->res : NULL, code[1] ? code[1]->res : NULL, 0);
	return tacJoin(code[0], tacJoin(code[1], newTac));
}

TAC* makeWhen(TAC** code)
{
	HASH_NODE* newLabel = makeLabel();
	TAC* tacIf = tacCreate(TAC_IFZ, newLabel, code[0] ? code[0]->res : NULL, NULL, 0);
	TAC* tacLabel = tacCreate(TAC_LABEL, newLabel, NULL, NULL, 0);
	return tacJoin(tacJoin(tacJoin(code[0], tacIf), code[1]), tacLabel);
}

TAC* makeElse(TAC** code)
{
	HASH_NODE* newLabel1 = makeLabel();
	HASH_NODE* newLabel2 = makeLabel();
	TAC* tacIf = tacCreate(TAC_IFZ, newLabel1, code[0] ? code[0]->res : NULL, NULL, 0);
	TAC* tacLabel1 = tacCreate(TAC_LABEL, newLabel1, NULL, NULL, 0);
	TAC* tacLabel2 = tacCreate(TAC_LABEL, newLabel2, NULL, NULL, 0);
	TAC* tacJmp = tacCreate(TAC_JUMP, newLabel2, NULL, NULL, 0);
	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(code[0], tacIf), code[1]), tacJmp), tacLabel1), code[2]), tacLabel2);
}

TAC* makeWhile(TAC** code)
{
	HASH_NODE* newLabel1 = makeLabel();
	HASH_NODE* newLabel2 = makeLabel();
	TAC* tacIf = tacCreate(TAC_IFZ, newLabel2, code[0] ? code[0]->res : NULL, NULL, 0);
	TAC* tacLabel1 = tacCreate(TAC_LABEL, newLabel1, NULL, NULL, 0);
	TAC* tacLabel2 = tacCreate(TAC_LABEL, newLabel2, NULL, NULL, 0);
	TAC* tacJmp = tacCreate(TAC_JUMP, newLabel1, NULL, NULL, 0);
	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacLabel1, code[0]), tacIf), code[1]), tacJmp), tacLabel2);
}

TAC* makeFor(HASH_NODE* identifier,TAC** code)
{
	HASH_NODE* newLabel1 = makeLabel();
	HASH_NODE* newLabel2 = makeLabel();
	TAC* idLiteral = tacCreate(TAC_SYMBOL, identifier, NULL, NULL, 0);
	TAC* inicializacao = makeAtrib(identifier, code);
	TAC* seMenorIgual = tacCreate(TAC_IFLESSEQ, newLabel2, identifier, code[1]? code[1]->res : NULL, 0);
	TAC* tacLabel1 = tacCreate(TAC_LABEL, newLabel1, NULL, NULL, 0);
	TAC* tacLabel2 = tacCreate(TAC_LABEL, newLabel2, NULL, NULL, 0);
	TAC* incrementa = tacCreate(TAC_INC, identifier, NULL, NULL, 0);
	TAC* tacJmp = tacCreate(TAC_JUMP, newLabel1, NULL, NULL, 0);
	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(idLiteral, inicializacao), tacLabel1), seMenorIgual), code[2]), incrementa), tacJmp), tacLabel2);
}

TAC* makeAtrib(HASH_NODE* identifier, TAC** code)
{
	TAC* tacMov = tacCreate(TAC_MOVE, identifier, code[0]? code[0]-> res : NULL, NULL, 0);
	return tacJoin(code[0], tacMov);
}

TAC* makeAtribVec(HASH_NODE* identifier, TAC** code)
{
	TAC* tacVecWrite = tacCreate(TAC_VEC_WRITE, identifier, code[0] ? code[0]-> res : NULL, code[1] ? code[1]-> res : NULL, 0);
	return tacJoin(code[0], tacJoin(code[1], tacVecWrite)); 
}

TAC* makeFuncDef(HASH_NODE* identifier, TAC** code, AST_NODE *funcDef)
{
	AST_NODE* astFuncArg;
	TAC* tacFuncArg		= NULL;
	TAC* tacArgReceive	= NULL;
	TAC* tacArgList		= NULL;
	TAC* funcBody		= code[2];
	TAC* beginFunc		= tacCreate(TAC_BEGIN_FUNC, identifier, NULL, NULL, 0);
	int i = 1;

	for(astFuncArg = funcDef->children[1]; astFuncArg; astFuncArg = astFuncArg->children[1])
	{
		if (astFuncArg->children[1] != NULL)		
			tacFuncArg = tacGenerate(astFuncArg->children[0]);
		else
			tacFuncArg = tacGenerate(astFuncArg);
		tacArgReceive = tacCreate(TAC_ARG_RECEIVE, tacFuncArg->res, NULL, identifier, i);
		tacArgList = tacJoin(tacJoin(tacArgList, tacFuncArg), tacArgReceive);
		i++;
	}

	TAC* endFunc = tacCreate(TAC_END_FUNC, identifier, NULL, NULL, 0);
	return tacJoin(tacJoin(tacJoin(beginFunc, tacArgList), funcBody), endFunc);
}

TAC* makeIdCall(AST_NODE *callFunc)
{
	AST_NODE* astFuncArg;	
	TAC* tacArgList	= NULL;
	TAC* tacFuncArg	= NULL;
	TAC* tacIdCall	= NULL;
	int i = 1;
	int endForLoop = 0; //boolean var
	HASH_NODE* funcName = callFunc->symbol;

	for(astFuncArg = callFunc->children[0]; astFuncArg; astFuncArg = astFuncArg->children[1])
	{
		if (endForLoop) 
			break;
		if (astFuncArg->type == AST_PARAM_LIST)
		{
			if (astFuncArg->children[0] != NULL)
				tacFuncArg = tacGenerate(astFuncArg->children[0]);
			else
				tacFuncArg = tacGenerate(astFuncArg);
		}
		else
		{
			tacFuncArg = tacGenerate(astFuncArg);
			endForLoop = 1;
		}
		tacIdCall = tacCreate(TAC_ID_CALL, NULL, tacFuncArg->res, funcName, i);
		tacArgList = tacJoin(tacJoin(tacArgList, tacFuncArg), tacIdCall);
		i++;
	}
	HASH_NODE* callTemp = makeTemp();
	TAC* callTac = tacCreate(TAC_CALL, callTemp, callFunc->symbol, NULL, 0);
	return tacJoin(tacArgList, callTac);
}

TAC* makeReturn(TAC** code)
{
	TAC* tacReturn = tacCreate(TAC_RETURN, code[0]? code[0]->res : NULL, NULL, NULL, 0);
	return tacJoin(code[0], tacReturn);
}

TAC* makeRead(HASH_NODE* identifier)
{
	TAC* symbol = tacCreate(TAC_SYMBOL, identifier, NULL, NULL, 0);
	TAC* read = tacCreate(TAC_READ, identifier, NULL, NULL, 0);
	return tacJoin(symbol, read);
}

TAC* makePrint(AST_NODE* print, TAC** code)
{
	AST_NODE* tacPrintArg	= print;
	TAC* tacPrintList	= NULL;
	TAC* tacFuncArg		= NULL;
	TAC* tacPrint		= NULL;
	
	while(tacPrintArg)
	{			
		if(tacPrintArg->symbol)
		{
			tacFuncArg = tacCreate(TAC_SYMBOL, tacPrintArg->symbol, NULL, NULL, 0);
			tacPrintArg = tacPrintArg->children[1];
		}
		else
		{
			tacFuncArg = tacGenerate(tacPrintArg->children[0]);
			tacPrintArg = tacPrintArg->children[1];
		}
		tacPrint = tacCreate(TAC_PRINT, tacFuncArg ? tacFuncArg->res: NULL, NULL, NULL, 0);	
		tacPrintList = tacJoin(tacJoin(tacPrintList, tacFuncArg), tacPrint);
		
	}
	return tacPrintList;
}

TAC* makeVar(HASH_NODE* identifier, TAC** code)
{
	TAC *name = tacCreate(TAC_SYMBOL, identifier, NULL, NULL, 0);
	TAC *var = tacCreate(TAC_VAR, identifier, code[1]->res, NULL, 0);
	return tacJoin(name, tacJoin(code[1], var));
}

TAC* makeVec(AST_NODE* astvec, TAC** code)
{
	HASH_NODE* identifier = astvec->symbol;
	HASH_NODE* length = astvec->children[1]->symbol;

	TAC *tacVec = tacCreate(TAC_VEC, identifier, length, NULL, 0);
	TAC *tacVecInitList		= NULL;
	TAC *tacVecInit		= NULL;	
	TAC *tacArrayVal	= NULL;	

	AST_NODE* astVecInit;
	for (astVecInit = astvec->children[2]; astVecInit; astVecInit = astVecInit->children[1])
	{
		if (astVecInit->children[1] != NULL)		
			tacVecInit = tacGenerate(astVecInit->children[0]);
		else
			tacVecInit = tacGenerate(astVecInit);
	
		tacArrayVal = tacCreate(TAC_ARRAY_VALUE, tacVecInit->res, NULL, identifier, 0);
		tacVecInitList = tacJoin(tacJoin(tacVecInitList, tacVecInit), tacArrayVal);
	}

	return tacJoin(tacJoin(tacVec, tacVecInitList), code[0]);
}

TAC* makeIdVec(HASH_NODE* identifier, TAC** code)
{	
	TAC *value = tacCreate(TAC_ID_VECTOR, makeTemp(), identifier, code[0]? code[0]->res: NULL, 0);
	return tacJoin(code[0], value);
}

HASH_NODE* makeTemp()
{
	static int serial_temp = 0;
	static char buffer[128];

	sprintf(buffer, "temporariaLindha_%d", serial_temp);
	serial_temp++;
	return hash_insert(SYMBOL_SCALAR, buffer);
}

HASH_NODE* makeLabel()
{
	static int serial_label = 0;
	static char buffer[128];

	sprintf(buffer, "labelzinhaLinda_%d", serial_label);
	serial_label++;
	return hash_insert(SYMBOL_LABEL, buffer);
}
