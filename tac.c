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
TAC* makeVecValues(HASH_NODE* identifier, TAC** code);
TAC* makeVariavel(HASH_NODE* identifier, TAC** code);
TAC* makeVec(HASH_NODE* identifier, HASH_NODE* length, TAC** code);
TAC* makeVecExpr(HASH_NODE* identifier, TAC** code);


//tacArg = tacCreate(TAC_ID_CALL, 0, tacBuff->res,func_name, i);
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
	newTac->prev = 0;
	newTac->next = 0;
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
	TAC *t = 0;
	for(t=tac;t->prev;t=t->prev){t->prev->next = t;}
	return t;
}

void tacPrintBack(TAC *last){
	TAC *tac;
	for(tac = last; tac; tac=tac->prev){
		if (tac->type != TAC_LITERAL){
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
		if (tac->type != TAC_LITERAL){
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
		case TAC_LITERAL: fprintf(stderr, "TAC_LITERAL"); break;
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
		default:
			fprintf(stderr, "Type not found"); break;
	}
}

TAC * tacGenerate(AST_NODE *node){
	TAC *code[NUM_CHILDREN];
	TAC *result = 0;
	int i = 0;

	if(!node) { return 0; }
	for(i=0; i<NUM_CHILDREN; i++){
		code[i]= 0;
	}
	for(i=0; i<NUM_CHILDREN; i++){
		code[i]= tacGenerate(node->children[i]);
	}
	switch(node->type){
		case AST_LITERAL: 
		case AST_DEC_ARGS:
			result = tacCreate(TAC_LITERAL, node->symbol, 0, 0, 0); break;
		case AST_ID_VECTOR: result = makeVecExpr(node->symbol,code); break;
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
		// case AST_DEC_FUNC: result = makeFuncDef(node->children[0]->symbol, code, node); break;
		
		case AST_ID_CALL: result = makeIdCall(node); break;
		case AST_RETURN: result = makeReturn(code); break;
		case AST_READ: result = makeRead(node->symbol); break;
		// case AST_PRINT: result = makePrint(node, code); break;
		// case AST_SEQNUM_ELEM: result = makeVecValues(node->symbol, code); break;
		case AST_VAR_DEC: result = makeVariavel(node->symbol, code); break;
		// case AST_DEC_VEC_GLOB: result = makeVec(node->symbol, node->children[0]->symbol, code); break;
	
		case AST_COMMAND_LIST: result = code[0]; break;
		case AST_COMMANDS: result = tacJoin(code[0],code[1]); break;
		case AST_PARENTHESES: result = code[0]; break;	
		default: result = tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]);
	}
	
	return result;
}

TAC* makeOpBin(int op, TAC** code){
	TAC *newTac = tacCreate(op, makeTemp(), code[0] ? code[0]->res : 0,
							  code[1] ? code[1]->res : 0, 0);
	return tacJoin(code[0], tacJoin(code[1], newTac));
}

TAC* makeWhen(TAC** code){
	TAC* setac = 0;
	TAC* tacLabel = 0;
	HASH_NODE* novaLabel = 0;
	novaLabel = makeLabel();
	setac = tacCreate(TAC_IFZ,novaLabel,code[0] ? code[0]->res : 0, 0, 0);
	tacLabel = tacCreate(TAC_LABEL,novaLabel,0,0, 0);
	return tacJoin(tacJoin(tacJoin(code[0],setac),code[1]),tacLabel);
}

TAC* makeElse(TAC** code){
	TAC* setac = 0;
	TAC* tacLabel1 = 0;
	TAC* tacLabel2 = 0;
	TAC* jmp = 0;
	HASH_NODE* novaLabel1 = 0;
	HASH_NODE* novaLabel2 = 0;
	novaLabel1 = makeLabel();
	novaLabel2 = makeLabel();
	setac = tacCreate(TAC_IFZ,novaLabel1,code[0] ? code[0]->res : 0, 0, 0);
	tacLabel1 = tacCreate(TAC_LABEL,novaLabel1,0,0,0);
	tacLabel2 = tacCreate(TAC_LABEL,novaLabel2,0,0,0);
	jmp = tacCreate(TAC_JUMP,novaLabel2,0,0,0);
	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(code[0],setac),code[1]),jmp),tacLabel1),code[2]),tacLabel2);
}

TAC* makeWhile(TAC** code){
	TAC* setac = 0;
	TAC* tacLabel1 = 0;
	TAC* tacLabel2 = 0;
	TAC* jmp = 0;
	HASH_NODE* novaLabel1 = 0;
	HASH_NODE* novaLabel2 = 0;
	novaLabel1 = makeLabel();
	novaLabel2 = makeLabel();
	setac = tacCreate(TAC_IFZ,novaLabel2,code[0] ? code[0]->res : 0, 0, 0);
	tacLabel1 = tacCreate(TAC_LABEL,novaLabel1,0,0,0);
	tacLabel2 = tacCreate(TAC_LABEL,novaLabel2,0,0,0);
	jmp = tacCreate(TAC_JUMP,novaLabel1,0,0,0);
	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacLabel1,code[0]),setac),code[1]),jmp),tacLabel2);
}

TAC* makeFor(HASH_NODE* identifier,TAC** code){
	TAC* inicializacao = 0;
	TAC* seMenorIgual = 0;
	TAC* incrementa = 0;
	TAC* jmp = 0;
	TAC* tacLabel1 = 0;
	TAC* tacLabel2 = 0;
	TAC* idLiteral = 0;
	HASH_NODE* novaLabel1 = 0;
	HASH_NODE* novaLabel2 = 0;
	novaLabel1 = makeLabel();
	novaLabel2 = makeLabel();
	idLiteral = tacCreate(TAC_LITERAL,identifier,0,0,0);
	inicializacao = makeAtrib(identifier,code);
	seMenorIgual = tacCreate(TAC_IFLESSEQ,novaLabel2,identifier,code[1]? code[1]->res : 0, 0);
	tacLabel1 = tacCreate(TAC_LABEL,novaLabel1,0,0,0);
	tacLabel2 = tacCreate(TAC_LABEL,novaLabel2,0,0,0);
	incrementa = tacCreate(TAC_INC,identifier,0,0,0);
	jmp = tacCreate(TAC_JUMP,novaLabel1,0,0,0);
	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(idLiteral,inicializacao),tacLabel1),seMenorIgual),code[2]),incrementa),jmp),tacLabel2);
}

TAC* makeAtrib(HASH_NODE* identifier, TAC** code){
	TAC* mov = 0;
	mov = tacCreate(TAC_MOVE, identifier, code[0]? code[0]-> res : 0,0,0);
	return tacJoin(code[0],mov);
}

TAC* makeAtribVec(HASH_NODE* identifier, TAC** code){
	TAC* vecAssign = 0;
	vecAssign = tacCreate(TAC_VEC_WRITE, identifier, code[0]? code[0]-> res : 0,code[1]? code[1]-> res : 0,0);
	return tacJoin(code[0],tacJoin(code[1],vecAssign)); 
}

TAC* makeFuncDef(HASH_NODE* identifier, TAC** code, AST_NODE *funcDef){
	AST_NODE* buff;
	TAC* tacBuff = 0;
	TAC* tacArg = 0;
	TAC* params = 0;
	int i = 1;

	TAC* funcBody = code[1];
	TAC* beginFunc = tacCreate(TAC_BEGIN_FUNC, identifier, 0, 0, 0);

	for(buff = funcDef->children[0]->children[1]; buff; buff = buff->children[1]){
		tacBuff = tacGenerate(buff->children[0]);
		tacArg = tacCreate(TAC_ARG_RECEIVE, tacBuff->res, 0, identifier, i);
		params = tacJoin(tacJoin(params,tacBuff), tacArg);
		i++;
	}

	TAC* endFunc = tacCreate(TAC_END_FUNC, identifier, 0, 0, 0);
	return tacJoin(tacJoin(tacJoin(beginFunc,params),funcBody), endFunc);
}

TAC* makeIdCall(AST_NODE *callFunc){
	TAC* callTac = 0;	
	TAC* parametros = 0;
	AST_NODE* buffer = 0;
	TAC* tacBuff = 0;
	TAC* tacArg = 0;
	int i = 1;
	HASH_NODE* func_name = callFunc->symbol;
	for(buffer = callFunc->children[0]; buffer; buffer = buffer->children[1]){
		if (buffer->children[0] != NULL)
			tacBuff = tacGenerate(buffer->children[0]);
		else
			tacBuff = tacGenerate(buffer);
		tacArg = tacCreate(TAC_ID_CALL, 0, tacBuff->res,func_name, i);
		parametros = tacJoin(tacJoin(parametros,tacBuff),tacArg);
		i++;
	}
	HASH_NODE* callTemp = makeTemp();
	callTac = tacCreate(TAC_CALL, callTemp, callFunc->symbol,0,0);
	return tacJoin(parametros,callTac);
}

TAC* makeReturn(TAC** code){
	TAC* retorno = 0;
	retorno = tacCreate(TAC_RETURN,code[0]? code[0]->res : 0, 0, 0,0);
	return tacJoin(code[0],retorno);
}

TAC* makeRead(HASH_NODE* identifier){
	TAC* symb = tacCreate(TAC_LITERAL, identifier,0,0,0);
	TAC* ret = tacCreate(TAC_READ,identifier, 0, 0,0);
	return tacJoin(symb,ret);
}

TAC* makePrint(AST_NODE* print, TAC** code){
	AST_NODE* buff = 0;
	TAC* prints = 0;
	TAC* tacBuff = 0;
	TAC* tacPrint = 0;
	buff = print->children[0];
	while(buff){				
		if(buff->symbol){
			tacBuff = tacCreate(TAC_LITERAL,buff->symbol, 0, 0, 0);
			buff = buff->children[0];
		}else{
			tacBuff = tacGenerate(buff->children[0]);
			buff = buff->children[1];
		}
		tacPrint = tacCreate(TAC_PRINT,tacBuff ? tacBuff->res: 0,0,0,0);	
		prints = tacJoin(tacJoin(prints,tacBuff),tacPrint);
	}
	
	return prints;
}

TAC* makeVecValues(HASH_NODE* identifier, TAC** code){
	TAC *vecValue = tacCreate(TAC_ARRAY_VALUE, identifier, 0, 0, 0);
	return tacJoin(vecValue, code[0]);
}

TAC* makeVariavel(HASH_NODE* identifier, TAC** code){
	TAC *name = tacCreate(TAC_LITERAL, identifier,0,0,0);
	TAC *var = tacCreate(TAC_VAR, identifier, code[1]->res, 0, 0);
	return tacJoin(name,tacJoin(code[1],var));
}

TAC* makeVec(HASH_NODE* identifier, HASH_NODE* length, TAC** code){
	TAC *vec = tacCreate(TAC_VEC, identifier, length, 0, 0);
	return tacJoin(vec, code[0]);
}

TAC* makeVecExpr(HASH_NODE* identifier, TAC** code){	
	TAC *value = tacCreate(TAC_ID_VECTOR, makeTemp(), identifier, code[0]? code[0]->res: 0, 0);
	return tacJoin(code[0],value);
}

HASH_NODE* makeTemp(){
	static int serial_temp = 0;
	static char buffer[128];

	sprintf(buffer, "temporariaLindha_%d", serial_temp);
	serial_temp++;
	return hash_insert(NATURE_VAR, buffer);
}

HASH_NODE* makeLabel(){
	static int serial_label = 0;
	static char buffer[128];

	sprintf(buffer, "labelzinhaLinda_%d", serial_label);
	serial_label++;
	return hash_insert(NATURE_VAR, buffer);
}
