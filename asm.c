/*
Etapa 6 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include "asm.h"

void asmPrintFixed(FILE* arquivoSaida, TAC* tacParam);
void asmPushHash(FILE* arquivoSaida);
int numConsLabel = 1;
int numLit = 0;

void asmPushHash(FILE* arquivoSaida){
	HASH_NODE *node;
	int i;	
	fprintf(arquivoSaida, "\n.data\n");
	for(i=0; i<HASH_SIZE; i++){
		for(node=table[i]; node; node=node->next)
		{
			if(node->type == SYMBOL_SCALAR)
				 fprintf(arquivoSaida,	"%s:\n"
											"\t.long 0\n",
									node->text);
			else if(node->type == SYMBOL_LIT_INT || node->type == SYMBOL_LIT_REAL || node->type == SYMBOL_LIT_CHAR )
				fprintf(arquivoSaida, "lit%s:\n"
										"\t.long %s \n", node->text, node->text);
		}
	}
}

void asmPrintFixed(FILE* arquivoSaida, TAC* tacParam){
	TAC* tac;
	fprintf(arquivoSaida,	".LC0:\n"
					"\t.string \"%%d\"\n"); 	
	for(tac=tacParam; tac; tac = tac->next){	
		switch(tac->type){
			case TAC_DIV:
				if(tac->op2->type != SYMBOL_LABEL && tac->op1->type != SYMBOL_SCALAR){
					tac->posicaoParam = numLit;	
				}
				break;
			case TAC_ARG_RECEIVE:
				fprintf(arquivoSaida,	"%s:\n"
									"\t.long 0\n",
									tac->res->text); break;
			case TAC_PRINT:
				if(tac->res->type == SYMBOL_LIT_STRING){
					fprintf(arquivoSaida,	".LC%d:\n"
											"\t.string %s\n",
									numConsLabel, tac->res->text); 
					tac->posicaoParam = numConsLabel;
					numConsLabel++;
				}else{
					tac->posicaoParam = 0;
				}
				break;
			case TAC_VAR:
				fprintf(arquivoSaida,	"%s:\n"
								"\t.long %s\n",
						tac->res->text, tac->op1->text); break;
			default: break;
		}
	}
}

void asmGen(TAC* tacParam, FILE* arquivoSaida){ 
	TAC* tac;
	TAC* tacImpressao = tacParam;	
	asmPushHash(arquivoSaida);
	asmPrintFixed(arquivoSaida, tacImpressao);
	int pos = 0;	
	int numLabel = 0;
	int numParamsCall = 0;	
	int numParamsReceive = 0;	
	for(tac=tacParam; tac; tac = tac->next){	
		//printTacType(tac->type);printf("\n"); //debug
		switch(tac->type){
			case TAC_SYMBOL: break;
			case TAC_VAR: break;
			case TAC_VEC:
					if(tac->next->type ==  TAC_ARRAY_VALUE){
						fprintf(arquivoSaida,	"%s:\n", tac->res->text); 
					}else{	
						pos = atoi(tac->op1->text) * 4; 
						fprintf(arquivoSaida,	"\n.comm %s, %d\n", tac->res->text, pos); 
					}
					break;
			case TAC_ARRAY_VALUE: fprintf(arquivoSaida,	"\t.long %s\n",
									tac->res->text); break;
			case TAC_ADD:	fprintf(arquivoSaida,	"\n\t## TAC_ADD\n");
						  	if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tac->op1->text); 
							else
								fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tac->op1->text); 	
							if(tac->op2->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\taddl %s(%%rip), %%eax\n",  tac->op2->text); 
							else
								fprintf(arquivoSaida,	"\taddl $%s, %%eax\n",  tac->op2->text); 	 								
							fprintf(arquivoSaida,	"\tmovl %%eax, %s(%%rip)\n",  tac->res->text); 	 									
							break;
			case TAC_SUB: fprintf(arquivoSaida,	"\n\t## TAC_SUB\n");
						  	if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tac->op1->text); 
							else
								fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tac->op1->text); 	
							if(tac->op2->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\tsubl %s(%%rip), %%eax\n",  tac->op2->text); 
							else
								fprintf(arquivoSaida,	"\tsubl $%s, %%eax\n",  tac->op2->text); 	 								
							fprintf(arquivoSaida,	"\tmovl %%eax, %s(%%rip)\n",  tac->res->text); 	 									
							break;
			case TAC_MUL: fprintf(arquivoSaida,	"\n\t## TAC_MUL\n");
						  	if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tac->op1->text); 
							else
								fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tac->op1->text); 	
							if(tac->op2->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\timull %s(%%rip), %%eax\n",  tac->op2->text); 
							else
								fprintf(arquivoSaida,	"\timull $%s, %%eax\n",  tac->op2->text); 	 								
							fprintf(arquivoSaida,	"\tmovl %%eax, %s(%%rip)\n",  tac->res->text); 	 									
							break;
			case TAC_DIV: fprintf(arquivoSaida,	"\n\t## TAC_DIV\n");
						  	if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
								fprintf(arquivoSaida,"\tmovl %s(%%rip), %%eax\n", tac->op1->text);
						  	else
								fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tac->op1->text);
							fprintf(arquivoSaida,"\tcltd\n");
							if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
								fprintf(arquivoSaida,"\tidivl %s(%%rip)\n", tac->op2->text);
							else
								fprintf(arquivoSaida,"\tidivl lit%s(%%rip)\n", tac->op2->text);				
							fprintf(arquivoSaida,"\tmovl %%eax, %s(%%rip)\n", tac->res->text); break;
			case TAC_GT: fprintf(arquivoSaida,	"\n\t## TAC_GT\n");
					  	if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsetg %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_LT: fprintf(arquivoSaida,	"\n\t## TAC_LT\n");
					  	if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsetl %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_GE: fprintf(arquivoSaida,	"\n\t## TAC_GE\n");
					  	if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsetge %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_LE:fprintf(arquivoSaida,	"\n\t## TAC_LE\n");
					  	if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsetle %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_EQ: fprintf(arquivoSaida,	"\n\t## TAC_EQ\n");
					  	if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsete %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_NE: fprintf(arquivoSaida,	"\n\t## TAC_NE\n");
					  	if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsetne %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_BEGIN_FUNC: fprintf(arquivoSaida,	"\n\t## TAC_BEGIN_FUNC\n"
											"\t.text\n"
											"\t.globl %s\n"
											"%s:\n"				
								  			"\t.cfi_startproc\n"
											"\tpushq	%%rbp\n",
								  tac->res->text, tac->res->text); break; 
			case TAC_END_FUNC: fprintf(arquivoSaida,	"\n\t## TAC_END_FUNC\n"
											"\tpopq	%%rbp\n"				
								  			"\tret\n"
											"\t.cfi_endproc\n"); break; 
			case TAC_RETURN: if(tac->res->type == SYMBOL_LABEL || tac->res->type == SYMBOL_SCALAR){ 
							 fprintf(arquivoSaida,"\n\t## TAC_RETURN\n"
											"\tmovl %s(%%rip), %%eax\n",
								  tac->res->text); 
							}else{
								 fprintf(arquivoSaida,"\n\t## TAC_RETURN\n"
											"\tmovl $%s, %%eax\n",
								  tac->res->text); 
							}break; 
			case TAC_MOVE: if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR){ 
								fprintf(arquivoSaida,"\n\t## TAC_MOVE\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text, tac->res->text);
							}else{
								fprintf(arquivoSaida,"\n\t## TAC_MOVE\n"
											"\tmovl $%s, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text, tac->res->text);
							} break; 
			case TAC_IFZ: fprintf(arquivoSaida,	"\n\t## TAC_IFZ\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tje .%s\n",
								  tac->op1->text, tac->res->text); break;
			case TAC_IFLESSEQ: 	fprintf(arquivoSaida,	"\n\t## TAC_IFLESSEQ\n"
											"\tmovl %s(%%rip), %%eax\n",
											tac->op1->text);
							   	if (tac->op2->type == SYMBOL_LABEL || tac->op2->type == SYMBOL_SCALAR)
									fprintf(arquivoSaida, "\tcmpl %s(%%rip), %%eax\n", tac->op2->text);
								else
									fprintf(arquivoSaida, "\tcmpl $%s, %%eax\n", tac->op2->text);
								fprintf(arquivoSaida,"\tjnbe .%s\n",tac->res->text); break;
			case TAC_INC: fprintf(arquivoSaida,	"\n\t## TAC_INC\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\taddl $1, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->res->text, tac->res->text); break;
			case TAC_LABEL: fprintf(arquivoSaida,	"\n\t## TAC_LABEL\n"
											".%s:\n",
								  tac->res->text); break;
			case TAC_JUMP: fprintf(arquivoSaida,	"\n\t## TAC_JUMP\n"
											"\tjmp .%s\n",
								  tac->res->text); break;
			case TAC_VEC_WRITE: pos = atoi(tac->op1->text) * 4; 
								if(tac->op2->type == SYMBOL_LABEL || tac->op2->type == SYMBOL_SCALAR){
									fprintf(arquivoSaida,	"\n\t## TAC_VEC_WRITE\n"
												"\tmovl %s(%%rip), %%eax\n"
												"\tmovl %%eax, %s+%d(%%rip)\n",
									  tac->op2->text, tac->res->text, pos); 
								}else{
									fprintf(arquivoSaida,	"\n\t## TAC_VEC_WRITE\n"
												"\tmovl $%s, %%eax\n"
												"\tmovl %%eax, %s+%d(%%rip)\n",
									  tac->op2->text, tac->res->text, pos); 
								}
								break;
			case TAC_ATRIB:  pos = atoi(tac->op2->text);
								// caso em que a chave é um int
								if(pos){
									pos*=4;
									fprintf(arquivoSaida,	"\n\t## TAC_ATRIB\n"
												"\tmovl %s+%d(%%rip), %%eax\n"
												"\tmovl %%eax, %s(%%rip)\n",
									  tac->op1->text, pos, tac->res->text); 
								// caso em que a chave é um temporario
								}else{ 
									fprintf(arquivoSaida,	"\n\t## TAC_ATRIB\n"
												"\tmovl %s(%%rip), %%eax\n"
												"\tcltq\n"
												"\tmovl %s(,%%rax, 4), %%eax\n"
												"\tmovl %%eax, %s(%%rip)\n",
									  tac->op2->text, tac->op1->text, tac->res->text); 
								} break;
			case TAC_OR: fprintf(arquivoSaida,	"\n\t## TAC_OR\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tje .L%d\n"
											"\tmovl $1, %s(%%rip)\n"	
											"\tjmp .L%d\n"
											".L%d:\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tje .L%d\n"
											"\tmovl $1, %s(%%rip)\n"
											"\tjmp .L%d\n"
											".L%d:\n"
											"\tmovl $0, %s(%%rip)\n"
											".L%d:\n",
										tac->op1->text, numLabel, tac->res->text, numLabel+2, 
										numLabel, tac->op2->text, numLabel+1, tac->res->text, numLabel+2, 
										numLabel+1, tac->res->text, numLabel+2); 
										numLabel = numLabel + 3; 
										break;
			case TAC_AND: fprintf(arquivoSaida,	"\n\t## TAC_AND\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tjne .L%d\n"
											"\tmovl $0, %s(%%rip)\n"	
											"\tjmp .L%d\n"
											".L%d:\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tje .L%d\n"
											"\tmovl $1, %s(%%rip)\n"
											"\tjmp .L%d\n"
											".L%d:\n"
											"\tmovl $0, %s(%%rip)\n"
											".L%d:\n",
										tac->op1->text, numLabel, tac->res->text, numLabel+2, 
										numLabel, tac->op2->text, numLabel+1, tac->res->text, numLabel+2, 
										numLabel+1, tac->res->text, numLabel+2); 
										numLabel = numLabel + 3; 
										break;
			case TAC_NOT: fprintf(arquivoSaida, "\n\t## TAC_NOT\n"
										  "\tcmpl $0, %s(%%rip)\n"
										  "\tsete %%al\n"
	                                      "\tmovzbl %%al, %%eax\n"
	                                      "\tmovl %%eax, %s(%%rip)\n",
										tac->op1->text, tac->res->text);
										break;
			case TAC_PRINT: if(tac->res->type == SYMBOL_LIT_STRING){
								fprintf(arquivoSaida,	"\n\t## TAC_PRINT: STRING\n"
											"\tmovl $.LC%d, %%edi\n"
											"\tmovl $0, %%eax\n"
											"\tcall printf\n",
								  tac->posicaoParam); 
							 }else{
								fprintf(arquivoSaida,	"\n\t## TAC_PRINT: VAR\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\tmovl %%eax, %%esi\n"
											"\tmovl $.LC%d, %%edi\n"
											"\tmovl $0, %%eax\n"
											"\tcall printf\n",
								  tac->res->text, tac->posicaoParam); 
							 } 							
							 break;
			case TAC_READ: fprintf(arquivoSaida, "\n\t## TAC_READ\n"
											"\tmovl $%s, %%esi\n"
											"\tmovl	$.LC0, %%edi\n"
											"\tmovl	$0, %%eax\n"
											"\tcall	__isoc99_scanf\n"
											"\tmovl	$0, %%eax\n",
											tac->res->text);break;
			case TAC_CALL:  numParamsCall = 0;
							fprintf(arquivoSaida,	"\n\t## TAC_CALL\n"
											"\tcall %s\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text, tac->res->text); 
			case TAC_ID_CALL:	numParamsCall++;
								fprintf(arquivoSaida,	"\n\t## TAC_ID_CALL\n");
								if(tac->op1->type == SYMBOL_LABEL || tac->op1->type == SYMBOL_SCALAR){
									fprintf(arquivoSaida,	"\tmovl %s(%%rip), ", tac->op1->text);
								}else{
									fprintf(arquivoSaida,	"\tmovl $%s, ", tac->op1->text);
								}	
								switch(numParamsCall){
									case 1: fprintf(arquivoSaida,	"%%edi\n"); break;
									case 2: fprintf(arquivoSaida,	"%%esi\n"); break;
									case 3: fprintf(arquivoSaida,	"%%edx\n"); break;
									case 4: fprintf(arquivoSaida,	"%%ecx\n"); break;
									case 5: fprintf(arquivoSaida, "%%r8d\n"); break;
									case 6: fprintf(arquivoSaida,	"%%r9d\n"); break;
									default: fprintf(stderr,"Erro compilacao: Numero maximo de parametros suportado excedido\n");  exit(5);
								}
								break;
			case TAC_ARG_RECEIVE:
								numParamsReceive++;
								fprintf(arquivoSaida,	"\n\t## TAC_ARG_RECEIVE\n");
								switch(numParamsReceive){
									case 1: fprintf(arquivoSaida,	"\tmovl %%edi, "); break;
									case 2: fprintf(arquivoSaida,	"\tmovl %%esi, "); break;
									case 3: fprintf(arquivoSaida,	"\tmovl %%edx, "); break;
									case 4: fprintf(arquivoSaida,	"\tmovl %%ecx, "); break;
									case 5: fprintf(arquivoSaida,	"\tmovl %%r8d, "); break;
									case 6: fprintf(arquivoSaida,	"\tmovl %%r9d, "); break;
									default: fprintf(stderr,"Erro compilacao: Numero maximo de parametros suportado excedido\n"); exit(5);
								}
								if(tac->res->type == SYMBOL_LABEL || tac->res->type == SYMBOL_SCALAR){
								fprintf(arquivoSaida,	"%s(%%rip)\n", tac->res->text);
								}else{
									fprintf(arquivoSaida,	"$%s\n", tac->res->text);
								}
								if(tac->next->next->type != TAC_ARG_RECEIVE) numParamsReceive = 0;
								break;
			default: break; 
		}
	}
}
