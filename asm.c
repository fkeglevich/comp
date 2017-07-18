/*
Etapa 6 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include "asm.h"

void asmImpressao(FILE* arquivoSaida, TAC* tacParam);
void asmEnfiaHash(FILE* arquivoSaida);
int nrSeqLabel = 1;
int nrSeqLit = 0;

void asmEnfiaHash(FILE* arquivoSaida){
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

void asmImpressao(FILE* arquivoSaida, TAC* tacParam){
	TAC* tacTemp;
	fprintf(arquivoSaida,	".LC0:\n"
					"\t.string \"%%d\"\n"); 	
	for(tacTemp=tacParam; tacTemp; tacTemp = tacTemp->next){	
		switch(tacTemp->type){
			case TAC_DIV:
				if(tacTemp->op2->type != SYMBOL_LABEL && tacTemp->op1->type != SYMBOL_SCALAR){
					tacTemp->posicaoParam = nrSeqLit;	
				}
				break;
			case TAC_ARG_RECEIVE:
				fprintf(arquivoSaida,	"%s:\n"
									"\t.long 0\n",
									tacTemp->res->text); break;
			case TAC_PRINT:
				if(tacTemp->res->type == SYMBOL_LIT_STRING){
					fprintf(arquivoSaida,	".LC%d:\n"
											"\t.string %s\n",
									nrSeqLabel, tacTemp->res->text); 
					tacTemp->posicaoParam = nrSeqLabel;
					nrSeqLabel++;
				}else{
					tacTemp->posicaoParam = 0;
				}
				break;
			case TAC_VAR:
				fprintf(arquivoSaida,	"%s:\n"
								"\t.long %s\n",
						tacTemp->res->text, tacTemp->op1->text); break;
			default: break;
		}
	}
}

void asmGen(TAC* tacParam, FILE* arquivoSaida){ 
	TAC* tacTemp;
	TAC* tacImpressao = tacParam;	
	asmEnfiaHash(arquivoSaida);
	asmImpressao(arquivoSaida, tacImpressao);
	int posicaoAtual = 0, valorLabel = 0, numeroParamChamada = 0, numparamRec = 0;
	for(tacTemp=tacParam; tacTemp; tacTemp = tacTemp->next){	
		switch(tacTemp->type){
			case TAC_SYMBOL: break;
			case TAC_VAR: break;
			case TAC_VEC:
					if(tacTemp->next->type ==  TAC_ARRAY_VALUE){
						fprintf(arquivoSaida,	"%s:\n", tacTemp->res->text); 
					}else{	
						posicaoAtual = atoi(tacTemp->op1->text) * 4; 
						fprintf(arquivoSaida,	"\n.comm %s, %d\n", tacTemp->res->text, posicaoAtual); 
					}
					break;
			case TAC_ARRAY_VALUE: fprintf(arquivoSaida,	"\t.long %s\n",
									tacTemp->res->text); break;
			case TAC_ADD:	fprintf(arquivoSaida,	"\n\t## + ##\n");
						  	if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tacTemp->op1->text); 
							else
								fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tacTemp->op1->text); 	
							if(tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\taddl %s(%%rip), %%eax\n",  tacTemp->op2->text); 
							else
								fprintf(arquivoSaida,	"\taddl $%s, %%eax\n",  tacTemp->op2->text); 	 								
							fprintf(arquivoSaida,	"\tmovl %%eax, %s(%%rip)\n",  tacTemp->res->text); 	 									
							break;
			case TAC_SUB: fprintf(arquivoSaida,	"\n\t## - ##\n");
						  	if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tacTemp->op1->text); 
							else
								fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tacTemp->op1->text); 	
							if(tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\tsubl %s(%%rip), %%eax\n",  tacTemp->op2->text); 
							else
								fprintf(arquivoSaida,	"\tsubl $%s, %%eax\n",  tacTemp->op2->text); 	 								
							fprintf(arquivoSaida,	"\tmovl %%eax, %s(%%rip)\n",  tacTemp->res->text); 	 									
							break;
			case TAC_MUL: fprintf(arquivoSaida,	"\n\t## * ##\n");
						  	if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tacTemp->op1->text); 
							else
								fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tacTemp->op1->text); 	
							if(tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
						  		fprintf(arquivoSaida,	"\timull %s(%%rip), %%eax\n",  tacTemp->op2->text); 
							else
								fprintf(arquivoSaida,	"\timull $%s, %%eax\n",  tacTemp->op2->text); 	 								
							fprintf(arquivoSaida,	"\tmovl %%eax, %s(%%rip)\n",  tacTemp->res->text); 	 									
							break;
			case TAC_DIV: fprintf(arquivoSaida,	"\n\t## / ##\n");
						  	if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
								fprintf(arquivoSaida,"\tmovl %s(%%rip), %%eax\n", tacTemp->op1->text);
						  	else
								fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tacTemp->op1->text);
							fprintf(arquivoSaida,"\tcltd\n");
							if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
								fprintf(arquivoSaida,"\tidivl %s(%%rip)\n", tacTemp->op2->text);
							else
								fprintf(arquivoSaida,"\tidivl lit%s(%%rip)\n", tacTemp->op2->text);				
							fprintf(arquivoSaida,"\tmovl %%eax, %s(%%rip)\n", tacTemp->res->text); break;
			case TAC_GT: fprintf(arquivoSaida,	"\n\t## > ##\n");
					  	if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tacTemp->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tacTemp->op1->text); 	
						if(tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tacTemp->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tacTemp->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsetg %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tacTemp->res->text); break; 
			case TAC_LT: fprintf(arquivoSaida,	"\n\t## < ##\n");
					  	if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tacTemp->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tacTemp->op1->text); 	
						if(tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tacTemp->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tacTemp->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsetl %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tacTemp->res->text); break; 
			case TAC_GE: fprintf(arquivoSaida,	"\n\t## >= ##\n");
					  	if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tacTemp->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tacTemp->op1->text); 	
						if(tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tacTemp->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tacTemp->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsetge %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tacTemp->res->text); break; 
			case TAC_LE:fprintf(arquivoSaida,	"\n\t## <= ##\n");
					  	if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tacTemp->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tacTemp->op1->text); 	
						if(tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tacTemp->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tacTemp->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsetle %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tacTemp->res->text); break; 
			case TAC_EQ: fprintf(arquivoSaida,	"\n\t## == ##\n");
					  	if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tacTemp->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tacTemp->op1->text); 	
						if(tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tacTemp->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tacTemp->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsete %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tacTemp->res->text); break; 
			case TAC_NE: fprintf(arquivoSaida,	"\n\t## != ##\n");
					  	if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%edx\n",  tacTemp->op1->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%edx\n",  tacTemp->op1->text); 	
						if(tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR)
					  		fprintf(arquivoSaida,	"\tmovl %s(%%rip), %%eax\n",  tacTemp->op2->text); 
						else
							fprintf(arquivoSaida,	"\tmovl $%s, %%eax\n",  tacTemp->op2->text); 		
						fprintf(arquivoSaida,"\tcmpl %%eax, %%edx\n"
										"\tsetne %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tacTemp->res->text); break; 
			case TAC_BEGIN_FUNC: fprintf(arquivoSaida,	"\n\t## Inicio de Funcao ##\n"
											"\t.text\n"
											"\t.globl %s\n"
											"%s:\n"				
								  			"\t.cfi_startproc\n"
											"\tpushq	%%rbp\n",
								  tacTemp->res->text, tacTemp->res->text); break; 
			case TAC_END_FUNC: fprintf(arquivoSaida,	"\n\t## Final de funcao ##\n"
											"\tpopq	%%rbp\n"				
								  			"\tret\n"
											"\t.cfi_endproc\n"); break; 
			case TAC_RETURN: if(tacTemp->res->type == SYMBOL_LABEL || tacTemp->res->type == SYMBOL_SCALAR){ 
							 fprintf(arquivoSaida,"\n\t## Retorno ##\n"
											"\tmovl %s(%%rip), %%eax\n",
								  tacTemp->res->text); 
							}else{
								 fprintf(arquivoSaida,"\n\t## Retorno ##\n"
											"\tmovl $%s, %%eax\n",
								  tacTemp->res->text); 
							}break; 
			case TAC_MOVE: if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR){ 
								fprintf(arquivoSaida,"\n\t## Move ##\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tacTemp->op1->text, tacTemp->res->text);
							}else{
								fprintf(arquivoSaida,"\n\t## Move ##\n"
											"\tmovl $%s, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tacTemp->op1->text, tacTemp->res->text);
							} break; 
			case TAC_PRINT: if(tacTemp->res->type == SYMBOL_LIT_STRING){ //já que tudo é inteiro
								fprintf(arquivoSaida,	"\n\t## Imprimir variavel que seria string ##\n"
											"\tmovl $.LC%d, %%edi\n"
											"\tmovl $0, %%eax\n"
											"\tcall printf\n",
								  tacTemp->posicaoParam); 
							 }else{
								fprintf(arquivoSaida,	"\n\t## Imprimir variavel ##\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\tmovl %%eax, %%esi\n"
											"\tmovl $.LC%d, %%edi\n"
											"\tmovl $0, %%eax\n"
											"\tcall printf\n",
								  tacTemp->res->text, tacTemp->posicaoParam); 
							 } 							
							 break;
			case TAC_READ: fprintf(arquivoSaida, "\n\t## Read ##\n"
											"\tmovl $%s, %%esi\n"
											"\tmovl	$.LC0, %%edi\n"
											"\tmovl	$0, %%eax\n"
											"\tcall	__isoc99_scanf\n"
											"\tmovl	$0, %%eax\n",
											tacTemp->res->text);break;
			case TAC_CALL:  numeroParamChamada = 0;
							fprintf(arquivoSaida,	"\n\t## Chamada ##\n"
											"\tcall %s\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tacTemp->op1->text, tacTemp->res->text); 
			case TAC_ID_CALL:	numeroParamChamada++;
								fprintf(arquivoSaida,	"\n\t## Chamada de identificador ##\n");
								if(tacTemp->op1->type == SYMBOL_LABEL || tacTemp->op1->type == SYMBOL_SCALAR){
									fprintf(arquivoSaida,	"\tmovl %s(%%rip), ", tacTemp->op1->text);
								}else{
									fprintf(arquivoSaida,	"\tmovl $%s, ", tacTemp->op1->text);
								}	
								switch(numeroParamChamada){
									case 1: fprintf(arquivoSaida,	"%%edi\n"); break;
									case 2: fprintf(arquivoSaida,	"%%esi\n"); break;
									case 3: fprintf(arquivoSaida,	"%%edx\n"); break;
									case 4: fprintf(arquivoSaida,	"%%ecx\n"); break;
									case 5: fprintf(arquivoSaida, "%%r8d\n"); break;
									case 6: fprintf(arquivoSaida,	"%%r9d\n"); break;
									default: fprintf(stderr,"[E]rror: max num params exceed\n");  exit(5);
								}
								break;
			case TAC_ARG_RECEIVE:
								numparamRec++;
								fprintf(arquivoSaida,	"\n\t## Atribuicao de argumentos ##\n");
								switch(numparamRec){
									case 1: fprintf(arquivoSaida,	"\tmovl %%edi, "); break;
									case 2: fprintf(arquivoSaida,	"\tmovl %%esi, "); break;
									case 3: fprintf(arquivoSaida,	"\tmovl %%edx, "); break;
									case 4: fprintf(arquivoSaida,	"\tmovl %%ecx, "); break;
									case 5: fprintf(arquivoSaida,	"\tmovl %%r8d, "); break;
									case 6: fprintf(arquivoSaida,	"\tmovl %%r9d, "); break;
									default: fprintf(stderr,"[E]rror: max num params exceed\n"); exit(5);
								}
								if(tacTemp->res->type == SYMBOL_LABEL || tacTemp->res->type == SYMBOL_SCALAR){
								fprintf(arquivoSaida,	"%s(%%rip)\n", tacTemp->res->text);
								}else{
									fprintf(arquivoSaida,	"$%s\n", tacTemp->res->text);
								}
								if(tacTemp->next->next->type != TAC_ARG_RECEIVE) numparamRec = 0;
								break;
			case TAC_IFZ: fprintf(arquivoSaida,	"\n\t## Se zero ##\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tje .%s\n",
								  tacTemp->op1->text, tacTemp->res->text); break;
			case TAC_IFLESSEQ: 	fprintf(arquivoSaida,	"\n\t## Se menor igual ##\n"
											"\tmovl %s(%%rip), %%eax\n",
											tacTemp->op1->text);
							   	if (tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op2->type == SYMBOL_SCALAR)
									fprintf(arquivoSaida, "\tcmpl %s(%%rip), %%eax\n", tacTemp->op2->text);
								else
									fprintf(arquivoSaida, "\tcmpl $%s, %%eax\n", tacTemp->op2->text);
								fprintf(arquivoSaida,"\tjnbe .%s\n",tacTemp->res->text); break;
			case TAC_INC: fprintf(arquivoSaida,	"\n\t## Inc ##\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\taddl $1, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tacTemp->res->text, tacTemp->res->text); break;
			case TAC_LABEL: fprintf(arquivoSaida,	"\n\t## Label ##\n"
											".%s:\n",
								  tacTemp->res->text); break;
			case TAC_JUMP: fprintf(arquivoSaida,	"\n\t## Jump ##\n"
											"\tjmp .%s\n",
								  tacTemp->res->text); break;
			case TAC_VEC_WRITE: posicaoAtual = atoi(tacTemp->op1->text) * 4; 
								if(tacTemp->op2->type == SYMBOL_LABEL || tacTemp->op2->type == SYMBOL_SCALAR){
									fprintf(arquivoSaida,	"\n\t## Escrita em vetor ##\n"
												"\tmovl %s(%%rip), %%eax\n"
												"\tmovl %%eax, %s+%d(%%rip)\n",
									  tacTemp->op2->text, tacTemp->res->text, posicaoAtual); 
								}else{
									fprintf(arquivoSaida,	"\n\t## Escrita em vetor ##\n"
												"\tmovl $%s, %%eax\n"
												"\tmovl %%eax, %s+%d(%%rip)\n",
									  tacTemp->op2->text, tacTemp->res->text, posicaoAtual); 
								}
								break;
			case TAC_ATRIB:  posicaoAtual = atoi(tacTemp->op2->text);
								if(posicaoAtual){
									posicaoAtual*=4;
									fprintf(arquivoSaida,	"\n\t## Atribuicao ##\n"
												"\tmovl %s+%d(%%rip), %%eax\n"
												"\tmovl %%eax, %s(%%rip)\n",
									  tacTemp->op1->text, posicaoAtual, tacTemp->res->text); 
								}else{ 
									fprintf(arquivoSaida,	"\n\t## Atribuicao ##\n"
												"\tmovl %s(%%rip), %%eax\n"
												"\tcltq\n"
												"\tmovl %s(,%%rax, 4), %%eax\n"
												"\tmovl %%eax, %s(%%rip)\n",
									  tacTemp->op2->text, tacTemp->op1->text, tacTemp->res->text); 
								} break;
			case TAC_OR: fprintf(arquivoSaida,	"\n\t## || ##\n"
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
										tacTemp->op1->text, valorLabel, tacTemp->res->text, valorLabel+2, 
										valorLabel, tacTemp->op2->text, valorLabel+1, tacTemp->res->text, valorLabel+2, 
										valorLabel+1, tacTemp->res->text, valorLabel+2); 
										valorLabel = valorLabel + 3; 
										break;
			case TAC_AND: fprintf(arquivoSaida,	"\n\t## && ##\n"
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
										tacTemp->op1->text, valorLabel, tacTemp->res->text, valorLabel+2, 
										valorLabel, tacTemp->op2->text, valorLabel+1, tacTemp->res->text, valorLabel+2, 
										valorLabel+1, tacTemp->res->text, valorLabel+2); 
										valorLabel = valorLabel + 3; 
										break;
			case TAC_NOT: fprintf(arquivoSaida, "\n\t## ! ##\n"
										  "\tcmpl $0, %s(%%rip)\n"
										  "\tsete %%al\n"
	                                      "\tmovzbl %%al, %%eax\n"
	                                      "\tmovl %%eax, %s(%%rip)\n",
										tacTemp->op1->text, tacTemp->res->text);
										break;
			default: break; 
		}
	}
}
