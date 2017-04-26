/*
Etapa 1 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "y.tab.h"

#ifdef DEBUG_MODE

#define TOKEN_MAX 2000

const char* tokens[TOKEN_MAX] = {NULL};
int tokenArrayInit = 0;

const char* getTokenName(int code)
{
	if (!tokenArrayInit) {
		tokens[KW_BYTE] 	= "KW_BYTE ";
		tokens[KW_SHORT]	= "KW_SHORT";
		tokens[KW_LONG]		= "KW_LONG ";
		tokens[KW_FLOAT] 	= "KW_FLOAT";
		tokens[KW_DOUBLE] 	= "KW_DOUBLE";
		tokens[KW_WHEN] 	= "KW_WHEN ";
		tokens[KW_THEN] 	= "KW_THEN ";
		tokens[KW_ELSE] 	= "KW_ELSE ";
		tokens[KW_WHILE] 	= "KW_WHILE";
		tokens[KW_FOR] 		= "KW_FOR  ";
		tokens[KW_READ] 	= "KW_READ ";
		tokens[KW_RETURN] 	= "KW_RETURN";
		tokens[KW_PRINT] 	= "KW_PRINT";

		tokens[OPERATOR_LE] 	= "OPERATOR_LE";
		tokens[OPERATOR_GE] 	= "OPERATOR_GE";
		tokens[OPERATOR_EQ] 	= "OPERATOR_EQ";
		tokens[OPERATOR_NE] 	= "OPERATOR_NE";
		tokens[OPERATOR_AND] 	= "OPERATOR_AND";
		tokens[OPERATOR_OR] 	= "OPERATOR_OR";

		tokens[TK_IDENTIFIER] 	= "TK_IDENTIFIER";
		tokens[LIT_INTEGER] 	= "LIT_INTEGER";
		tokens[LIT_REAL] 	= "LIT_REAL";
		tokens[LIT_CHAR] 	= "LIT_CHAR";
		tokens[LIT_STRING] 	= "LIT_STRING";
		tokens[TOKEN_ERROR] 	= "TOKEN_ERROR";

		tokenArrayInit = 1;
	}

	if (tokens[code] == NULL)
		return "(token ascii)";

	return tokens[code];
}

#endif

extern int getLineNumber();

HASH_NODE *table[HASH_SIZE];

void hashStart(void)
{
	int i;
	for (i = 0; i < HASH_SIZE; i++)
		table[i] = 0;
}

int hash_code(char *text)
{
	int code = 1, i;
	for (i = 0; text[i] != '\0'; i++)
	{
		code = code * text[i];
		code = code % HASH_SIZE + 1;
	}
	return code;
}

HASH_NODE* hash_insert(int type, char *text)
{
	HASH_NODE *newNode;

	
	newNode = hash_search(text);
	if (newNode != 0)
	{
		return newNode;
	}
    
	int adress = hash_code(text);
	newNode = calloc(1, sizeof(HASH_NODE));
	if (table[adress] == NULL)
	{
		table[adress] = newNode;
	}
	else
	{
		newNode->next = table[adress];
		table[adress] = newNode;
	}

    newNode->type = type;
	newNode->text = malloc(strlen(text) + 1);
	strcpy(newNode->text, text);
    return newNode;
}

HASH_NODE* hash_search(char *text)
{
    int adress = hash_code(text);
    HASH_NODE *searchNode = table[adress];

    for (searchNode = table[adress]; searchNode != 0; searchNode = searchNode->next)
    {
        if (!strcmp(text, searchNode->text)) return searchNode;
    }
    return 0;
}

void hash_print()
{
	HASH_NODE *node;
	int i;
	for (i = 0; i < HASH_SIZE; i++)
	{
		node = table[i];
		while (node != NULL)
		{
			printf("Endereco: %d\t%s\t(%d)\tTexto: %s\n", i, getTokenName(node->type), node->type, node->text);
			node = node->next;
		}
	}
}

