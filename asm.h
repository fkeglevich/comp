/*
Etapa 6 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/


#ifndef ASM_HEADER
#define ASM_HEADER

#include <stdio.h>
#include "hash.h"
#include "ast.h"
#include "tac.h"

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4	
#define SYMBOL_LIT_TRUE 5	
#define SYMBOL_LIT_FALSE 6	
#define SYMBOL_IDENTIFIER 7	

void asmGen(TAC* tac, FILE* arquivoSaida);

#endif
