/*
Etapa 5 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#ifndef HASH_H_
#define HASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_MODE true

#ifdef DEBUG_MODE
const char* getTokenName(int code);
#endif

#define HASH_SIZE 997
#define VAR_LENGTH 64

#define NATURE_UNKNOWN		0
#define NATURE_VAR			1
#define NATURE_VEC			2
#define NATURE_FUNC			3

#define DATATYPE_UNKNOWN	0
#define DATATYPE_BYTE		1
#define DATATYPE_SHORT		2
#define DATATYPE_LONG		3
#define DATATYPE_FLOAT		4
#define DATATYPE_DOUBLE		5
#define DATATYPE_BOOL		6
#define DATATYPE_STRING		7

typedef struct hash_node {
	int type;
	int dataNature;
	int dataType;
	char *text;
	struct hash_node *next;
	void *funcParam; // Parametros de função
} HASH_NODE;

HASH_NODE *table[HASH_SIZE];

void hashStart(void);
int hash_code(char *text);
HASH_NODE* hash_insert(int type, char *text);
HASH_NODE* hash_search(char *text);
void hash_print(void);

#endif
