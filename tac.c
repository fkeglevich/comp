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


FILE *outputTAC;

TAC* tacCreate (int type, HASH_NODE *target, HASH_NODE *op1, HASH_NODE *op2) {
	TAC* tac;
	tac = (TAC*) calloc(1,sizeof(TAC));
	tac->type = type;
	tac->target = target;
	tac->op1 = op1;
	tac->op2 = op2;
	tac->prev = 0;
	tac->next = 0;
    tacPrintSingle(tac);

	return tac;
}

TAC* makeBinOp(TAC *code0, TAC *code1, int type) {
	TAC *result;
	TAC *newTac;
	result = tacJoin(code0, code1);

	newTac = tacCreate(type, makeTemp(), code0?code0->target:0,code1?code1->target:0);
	newTac->prev = result;
	result = newTac;
    tacPrintSingle(result);
	return result;
}

//Profe deu em aula
TAC* tacJoin ( TAC* l1, TAC* l2 ) { //junta duas listas de TACs
	TAC* tac;
	//se uma delas eh nula, retorna a outra.
	if(!l1) return l2;
	if(!l2) return l1;
	
	//percorre toda lista 2 de baixo pra cima.
	for(tac = l2; tac->prev; tac = tac->prev);
	
	tac->prev = l1;

    tacPrintSingle(l2);

	return l2;
}

TAC* tacCodeGen(AST_NODE* root){
	int i;
    	int aux = 0;
	TAC *code[NUM_CHILDREN];
	//TAC *result;
	TAC *all;
	TAC *label;
	//TAC *end;
	//TAC *begin;
	TAC *tcJump;
	HASH_NODE *beginLabel;
	HASH_NODE *endLabel;
	
	for( i=0; i<NUM_CHILDREN; i++ )
		code[i] = NULL;		
   
	if( root == NULL ) return NULL;	

	for( i=0; i < NUM_CHILDREN; i++)
	{
		if(root->children[i]) {
			code[i] = tacCodeGen(root->children[i]);
        	}
    	}


    //printf("\n%d", root->type);
	switch(root->type){
		case AST_COMMAND_LIST:         return code[0];                                         break;
		case AST_ADD:	        return makeBinOp(code[0],code[1], TAC_ADD);             break;
		case AST_SUB:	        return makeBinOp(code[0],code[1], TAC_SUB);             break;			
		case AST_MUL:	        return makeBinOp(code[0],code[1], TAC_MUL);             break;		
		case AST_DIV:	        return makeBinOp(code[0],code[1], TAC_DIV);             break;
		case AST_LE:	        return makeBinOp(code[0],code[1], TAC_LE);              break;
		case AST_GE:	        return makeBinOp(code[0],code[1], TAC_GE);              break;
		case AST_EQ:	        return makeBinOp(code[0],code[1], TAC_EQ);              break;
		case AST_NE:	        return makeBinOp(code[0],code[1], TAC_NE);              break;
		case AST_AND:	        return makeBinOp(code[0],code[1], TAC_AND);             break;
		case AST_OR:	        return makeBinOp(code[0],code[1], TAC_OR);              break;
		case AST_GT:	    return makeBinOp(code[0],code[1], TAC_MAIOR);           break;
		case AST_LT:	        return makeBinOp(code[0],code[1], TAC_MENOR);           break;

		case AST_BYTE:	        return tacCreate(TAC_DATABYTE, 0, 0, 0);                 break;
		case AST_SHORT:	        return tacCreate(TAC_DATASHORT, 0, 0, 0);                 break;
		case AST_LONG:	        return tacCreate(TAC_DATALONG, 0, 0, 0);                 break;		
		case AST_FLOAT:	        return tacCreate(TAC_DATAFLOAT, 0, 0, 0);                 break;		
		case AST_DOUBLE:	return tacCreate(TAC_DATADOUBLE, 0, 0, 0);                 break;				

		case AST_BOOL:	        return tacCreate(TAC_DATABOOL, 0, 0, 0);                break;

		case AST_LITERAL:	    return tacCreate(TAC_LITERAL, root->symbol, 0, 0);    break;
		case AST_READ:	        return tacCreate(TAC_READ, root->symbol, 0, 0 );       break;
		case AST_ID:	    		return tacCreate(TAC_VARIABLE, root->symbol, 0, 0);     break;            

		case AST_PARAM_LIST:         return tacJoin(code[0],tacCreate( TAC_PARAMETRO, root->symbol, code[0]? code[0]->target:0, 0 ));    break;
		case AST_PRINT:	        return tacJoin(code[0],tacCreate(TAC_PRINT, code[0]? code[0]->target:0, 0, 0 ));   break;
		case AST_RETURN:	    return tacJoin(code[0],tacCreate(TAC_RETURN, code[0]? code[0]->target:0, 0, 0 ));   break;

		case AST_PROGRAM:       return tacJoin(code[0],code[1]);        break;
		case AST_VAR_DEC:          return tacCreate( TAC_DECLARE, root->symbol, code[1]? code[1]->target:0, 0 );       break;              
        	case AST_VEC_DEC:     return tacCreate( TAC_DECLAREVET, root->symbol, code[1]? code[1]->target:0, 0 );    break; 
		
		case AST_ARGS_LIST:
        		all = tacCreate(TAC_ARG, 0, code[0]->target, 0);
			return tacJoin(tacJoin(code[0], all), code[1]);
			break;

		case AST_ATRIB:
		case AST_ATRIB_VECTOR:
			if(root->children[0]->type == AST_ID){
                aux = 0;
                if(code[1]){
                    if (code[1]->target->type == AST_ID_VECTOR){
                        aux = 1;
                    }
                }
                
                if(aux == 1){
                    all = tacCreate( TAC_MOV, code[0]? code[0]->target:0, code[1]? code[1]->target:0, code[1]? code[1]->op1:0 );
                }
                else{
                    all = tacCreate( TAC_MOV, code[0]? code[0]->target:0, code[1]? code[1]->target:0, 0 );
                }
                
				all = tacJoin(code[0],all);
                all = tacJoin(code[1],all);
			}
			else{   
				all = tacCreate( TAC_MOV_VET, code[0]? code[0]->target:0, code[0]? code[0]->op1:0, code[1]? code[1]->target:0 );
				label = tacJoin(code[0],code[1]);
				all = tacJoin(label,all);
			}
            return all;
            break;
            

		case AST_WHEN:
			beginLabel = makeLabel();			
			all = tacCreate(TAC_JFALSE, beginLabel, 0, 0);		
			all = tacJoin(code[0], all);
			all = tacJoin(all, code[1]);
			label = tacCreate(TAC_LABEL, beginLabel, 0, 0);
			all = tacJoin(all, label);			
			return all;
            break;   

		case AST_WHEN_ELSE:
			beginLabel = makeLabel();
			endLabel = makeLabel();
			all = tacCreate(TAC_JFALSE, beginLabel, 0, 0);
			label = tacCreate(TAC_LABEL, beginLabel, 0, 0);
			tcJump = tacCreate(TAC_JUMP, endLabel, 0, 0);
			all = tacJoin(code[0], all);
			all = tacJoin(all, code[1]);
			all = tacJoin(all, tcJump);
			all = tacJoin(all, label);
			all = tacJoin(all,code[2]);
			label = tacCreate(TAC_LABEL, endLabel, 0, 0);
			all = tacJoin(all,label);
			return all;
            break;
		case AST_WHILE:
			beginLabel = makeLabel();
			endLabel = makeLabel();			
			tcJump = tacCreate(TAC_JUMP, beginLabel, 0, 0);
			all = tacCreate( TAC_JFALSE, endLabel, code[0]? code[0]->target:0, 0 );
			label = tacCreate(TAC_LABEL, endLabel, 0, 0);
			tcJump = tacJoin(tcJump, label);
			tcJump = tacJoin(label, code[1]);
			label = tacCreate(TAC_LABEL, beginLabel, 0, 0);
			label = tacJoin(tcJump, label);
			label = tacJoin(label, code[0]);
			all = tacJoin(label, all);		
			return all;
            break;
       
		case AST_FUNC_DEC:
			label = tacCreate(TAC_ENDFUN, root->symbol, 0, 0);
			all = tacCreate(TAC_BEGINFUN, root->symbol, 0, 0);
			label = tacJoin(code[0],label);
			label = tacJoin(code[1],label);
			label = tacJoin(code[2], label);
			label = tacJoin(code[3], label);
			all = tacJoin(all,label);
			return all;
            break;
		default:    break;
	}
	return 0;
}


TAC* tacReverse(TAC *last){
	TAC *first;
	if (last == 0)
		return 0;
	
	for (first = last; first->prev; first = first->prev) {
			first->prev->next = first;
    }

	return first;
}

void tacPrintList(TAC* first){
	TAC *tac;

    for(tac = first; tac; tac = tac->next){
		tacPrintSingle(tac);        
    }
}


void tacPrintSingle(TAC* tac){

    printf("TAC(");
	fprintf(outputTAC,"TAC(");
	switch(tac->type){
		case TAC_ADD: 		
			printf("TAC_ADD");
			fprintf(outputTAC,"TAC_ADD");
			break;
		case TAC_SUB:
			printf("TAC_SUB");
			fprintf(outputTAC,"TAC_SUB");
			break;
		case TAC_MUL:
	 		printf("TAC_MUL");
			fprintf(outputTAC,"TAC_MUL");
			break;
		case TAC_DIV:
	 		printf("TAC_DIV");
			fprintf(outputTAC,"TAC_DIV");
			break;
		
		case TAC_LITERAL:
		 	printf("TAC_LITERAL");
			fprintf(outputTAC,"TAC_LITERAL");
			break;

		case TAC_DATABYTE:
		 	printf("TAC_DATABYTE");
			fprintf(outputTAC,"TAC_DATABYTE");
			break;

		case TAC_DATASHORT:
		 	printf("TAC_DATASHORT");
			fprintf(outputTAC,"TAC_DATASHORT");
			break;
		
		case TAC_DATALONG:
		 	printf("TAC_DATALONG");
			fprintf(outputTAC,"TAC_DATALONG");
			break;

		case TAC_DATAFLOAT:
		 	printf("TAC_DATAFLOAT");
			fprintf(outputTAC,"TAC_DATAFLOAT");
			break;

		case TAC_DATADOUBLE:
		 	printf("TAC_DATADOUBLE");
			fprintf(outputTAC,"TAC_DATADOUBLE");
			break;

		case TAC_DATABOOL:
		 	printf("TAC_DATABOOL");
			fprintf(outputTAC,"TAC_DATABOOL");
			break;

		case TAC_INTEGER:
		     	printf("TAC_INTEGER");
			fprintf(outputTAC,"TAC_INTEGER");
			break;
	
		case TAC_BOOLEAN:
		     	printf("TAC_BOOLEAN");
			fprintf(outputTAC,"TAC_BOOLEAN");
			break;
		case TAC_CHARACTER:
		   	printf("TAC_CHARACTER");
			fprintf(outputTAC,"TAC_CHARACTER");
			break;
		case TAC_STRING:
		 	printf("TAC_STRING");
			fprintf(outputTAC,"TAC_STRING");
			break;

		case TAC_READ:
		       	printf("TAC_READ");
			fprintf(outputTAC,"TAC_READ");
			break;
		case TAC_PRINT:
		      	printf("TAC_PRINT");
			fprintf(outputTAC,"TAC_PRINT");
			break;
		case TAC_RETURN:
		      	printf("TAC_RETURN");
			fprintf(outputTAC,"TAC_RETURN");
			break;

		case TAC_LE:
	 		printf("TAC_LE");
			fprintf(outputTAC,"TAC_LE");
			break;
		case TAC_GE:
	 		printf("TAC_GE");
			fprintf(outputTAC,"TAC_GE");
			break;
		case TAC_EQ:
	 		printf("TAC_EQ");
			fprintf(outputTAC,"TAC_EQ");
			break;
		case TAC_NE:
	 		printf("TAC_NE");
			fprintf(outputTAC,"TAC_NE");
			break;
		case TAC_AND:
	 		printf("TAC_AND");
			fprintf(outputTAC,"TAC_AND");
			break;
		case TAC_OR:
	 		printf("TAC_OR");
			fprintf(outputTAC,"TAC_OR");
			break;

		case TAC_MOV:
			printf("TAC_MOV");
			fprintf(outputTAC,"TAC_MOV");
			break;
		case TAC_MOV_VET:
			printf("TAC_MOV_VET");
			fprintf(outputTAC,"TAC_MOV_VET");
			break;
		case TAC_MAIOR:
			printf("TAC_MAIOR");
			fprintf(outputTAC,"TAC_MAIOR");
			break;
		case TAC_MENOR:
		   	printf("TAC_MENOR");
			fprintf(outputTAC,"TAC_MENOR");
			break;

		case TAC_LABEL:
			printf("TAC_LABEL");
			fprintf(outputTAC,"TAC_LABEL");
			break;
		case TAC_BEGINFUN:
			printf("TAC_BEGINFUN");
			fprintf(outputTAC,"TAC_BEGINFUN");
			break;
		case TAC_ENDFUN:
			printf("TAC_ENDFUN");
			fprintf(outputTAC,"TAC_ENDFUN");
			break;
		case TAC_CALL:
			printf("TAC_CALL");
			fprintf(outputTAC,"TAC_CALL");
			break;
		case TAC_JUMP:
			printf("TAC_JUMP");
			fprintf(outputTAC,"TAC_JUMP");
			break;
		case TAC_VETOR:
			printf("TAC_VETOR");
			fprintf(outputTAC,"TAC_VETOR");
			break;
		case TAC_VARIABLE:
			printf("TAC_VARIABLE");
			fprintf(outputTAC,"TAC_VARIABLE");
			break;
        	case TAC_VAR_VET:
			printf("TAC_VAR_VET");
			fprintf(outputTAC,"TAC_VAR_VET");
			break;
		case TAC_JFALSE:
			printf("TAC_JFALSE");
			fprintf(outputTAC,"TAC_JFALSE");
			break;
		case TAC_SALTO:
			printf("TAC_SALTO");
			fprintf(outputTAC,"TAC_SALTO");
			break;
		case TAC_DECLARE:
		 	printf("TAC_DECLARE");
			fprintf(outputTAC,"TAC_DECLARE");
			break;
       	 	case TAC_DEC_POINTER:
		 	printf("TAC_DEC_POINTER");
			fprintf(outputTAC,"TAC_DEC_POINTER");
			break;
		case TAC_DECLAREVET:
			printf("TAC_DECLAREVET");
			fprintf(outputTAC,"TAC_DECLAREVET");
			break;
		case TAC_LISTAPARAM:
			printf("TAC_LISTAPARAM");
			fprintf(outputTAC,"TAC_LISTAPARAM");
			break;
		case TAC_PARAMETRO:
			printf("TAC_PARAMETRO");
			fprintf(outputTAC,"TAC_PARAMETRO");
			break;
		case TAC_ARG:
			printf("TAC_ARG");
			fprintf(outputTAC,"TAC_ARG");
			break;		

		default:
	 		printf("UNKNOWN");
			fprintf(outputTAC,"UNKNOWN");
			break;
	}
	
	if(tac->target){
	 	printf(", %s ",tac->target->text);
		fprintf(outputTAC,", %s ",tac->target->text);
	}
	if(tac->op1){
	 	printf(", %s ",tac->op1->text);
		fprintf(outputTAC,", %s ",tac->op1->text);
	}
	if(tac->op2){
	 	printf(", %s ",tac->op2->text);
		fprintf(outputTAC,", %s ",tac->op2->text);
	}
	printf(")\n");
	fprintf(outputTAC,")\n");

}
