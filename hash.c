#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "y.tab.h"

extern int getLineNumber();

HASH_NODE *table[HASH_SIZE];

void hash_init(void)
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
	
	newNode = hash_search(token, text);
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
			newNode->data.integer_value = atoi(text);
			break;
		case SYMBOL_LIT_FLOATING:
			newNode->data.floating_value = atoi(text);
			break;
		case SYMBOL_LIT_TRUE:
			newNode->data.boolean_value = 1;
			break;
		case SYMBOL_LIT_FALSE:
			newNode->data.boolean_value = 0;
			break;
		case SYMBOL_LIT_CHAR:
			newNode->data.character_value = *text;
			break;
		case SYMBOL_LIT_STRING:
			newNode->data.string_value = (char*)malloc(sizeof(strlen(text)) + 1);
			strcpy(newNode->data.string_value, text);
			break;
		case SYMBOL_IDENTIFIER:
			newNode->data.identifier_value = (char*)malloc(sizeof(strlen(text)) + 1);
			strcpy(newNode->data.identifier_value, text);
			break;
		case SYMBOL_UNDEFINED:
			printf("Erro %s na linha: %d\n", text, getLineNumber());
			exit(3);
			break;
		default:
			newNode->data.identifier_value = (char*)malloc(sizeof(strlen(text)) + 1);
			strcpy(newNode->data.identifier_value, text);
	}
	
	return newNode;
}

HASH_NODE* hash_search(int token, char *text)
{
    int adress = hash_code(text);
    HASH_NODE *searchNode = table[adress];
	
	int integer_value;
	float floating_value;
	int boolean_value;
	char character_value;
	char *string_value;
	char *identifier_value;
	
	switch (token)
	{
		case SYMBOL_LIT_INTEGER:
			integer_value = atoi(text);
			break;
		case SYMBOL_LIT_FLOATING:
			floating_value = atoi(text);
			break;
		case SYMBOL_LIT_TRUE:
			boolean_value = 1;
			break;
		case SYMBOL_LIT_FALSE:
			boolean_value = 0;
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
        if (searchNode->data.integer_value == integer_value ||
			searchNode->data.floating_value == floating_value ||
			searchNode->data.boolean_value == boolean_value ||
			searchNode->data.character_value == character_value ||
			searchNode->data.string_value == string_value ||
			searchNode->data.identifier_value == identifier_value)
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

