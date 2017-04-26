/*
Etapa 2 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "tokens.h"

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

HASH_NODE* hash_insert(int token, char *text)
{
	HASH_NODE *newNode;

	newNode = hash_search(text);
	if (newNode != 0)
	{
		return newNode;
	}
    
	int adress = hash_code(text);
	newNode = (HASH_NODE*)malloc(sizeof(HASH_NODE));
	if (!newNode) exit(1);
	if (table[adress] == NULL)
	{
		table[adress] = newNode;
	}
	else
	{
		newNode->next = table[adress];
		table[adress] = newNode;
	}

    	newNode->token = token;

	switch (token)
	{
		case SYMBOL_LIT_INTEGER:
			newNode->dados.integer_value = atoi(text);
			break;
		case SYMBOL_LIT_REAL:
			newNode->dados.real_value = atoi(text);
			break;
		case SYMBOL_LIT_CHAR:
			newNode->dados.character_value = *text;
			break;
		case SYMBOL_LIT_STRING:
			newNode->dados.string_value = (char*)malloc(sizeof(strlen(text)) + 1);
			strcpy(newNode->dados.string_value, text);
			break;
		case SYMBOL_IDENTIFIER:
			newNode->dados.identifier_value = (char*)malloc(sizeof(strlen(text)) + 1);
			strcpy(newNode->dados.identifier_value, text);
			break;
		case SYMBOL_UNDEFINED:
			printf("Erro %s na linha: %d\n", text, getLineNumber());
			exit(3);
			break;
		default:
			newNode->dados.identifier_value = (char*)malloc(sizeof(strlen(text)) + 1);
			strcpy(newNode->dados.identifier_value, text);
	}
	
	return newNode;	
}

HASH_NODE* hash_search(int token, char *text)
{
    int adress = hash_code(text);
    HASH_NODE *searchNode = table[adress];

	int integer_value;
	float real_value;
	int boolean_value;
	char character_value;
	char *string_value;
	char *identifier_value;

	switch (token)
	{
		case SYMBOL_LIT_INTEGER:
			integer_value = atoi(text);
			break;
		case SYMBOL_LIT_REAL:
			real_value = atoi(text);
			break;
		case SYMBOL_LIT_CHAR:
			character_value = *text;
			break;
		case SYMBOL_LIT_STRING:
			string_value = (char*)malloc(sizeof(strlen(text)) + 1);
			strcpy(string_value, text);
			break;
		case SYMBOL_IDENTIFIER:
			identifier_value = (char*)malloc(sizeof(strlen(text)) + 1);
			strcpy(identifier_value, text);
			break;
		default:
			;
	}

    for (searchNode = table[adress]; searchNode != 0; searchNode = searchNode->next)
    {
        if (searchNode->dados.integer_value == integer_value ||
			searchNode->dados.real_value == real_value ||
			searchNode->dados.character_value == character_value ||
			searchNode->dados.string_value == string_value ||
			searchNode->dados.identifier_value == identifier_value)
			return searchNode;
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
		while (node)
		{
			printf("Endereco: %d, token: %d\n", i, node->token);
			node = node->next;
		}
	}
}

