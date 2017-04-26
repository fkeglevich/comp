/*
Etapa 2 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#ifndef HASH_H_
#define HASH_H_

#include <stdio.h>

#define DEBUG_MODE true

#ifdef DEBUG_MODE
const char* getTokenName(int code);
#endif

#define HASH_SIZE 997
#define VAR_LENGTH 64

typedef struct {
	int 	integer_value;
	float 	real_value;
	char 	character_value;
	char	*string_value;
	char	*identifier_value;
}DADOS_TOKEN;

typedef struct hash_node {
	int token;
	DADOS_TOKEN dados;
	struct hash_node *next;
} HASH_NODE;

void hashStart(void);
int hash_code(char *text);
HASH_NODE* hash_insert(int token, char *text);
HASH_NODE* hash_search(int token, char *text);
void hash_print(void);

#endif
