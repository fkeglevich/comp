/*
Etapa 7 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/


#ifndef OPT_HEADER
#define OPT_HEADER

#include <stdio.h>
#include "asm.h"
	
//void asmGen(TAC* tac, FILE* arquivoSaida);
void optimizeAst(AST_NODE *root);

#endif
