/*
Etapa 5 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "ast.h"
#include "y.tab.h"
#include "semantic.h"

#ifdef DEBUG_MODE

#define TOKEN_MAX 2000

const char* tokens[TOKEN_MAX] = {NULL};
int tokenArrayInit = 0;

const char* getTokenName(int code)
{
	if (!tokenArrayInit) {
		tokens[7] 	= "SYMBOL_IDENTIFIER";
		tokens[1] 	= "SYMBOL_LIT_INT  ";
		tokens[2] 	= "SYMBOL_LIT_REAL  ";
		tokens[3] 	= "SYMBOL_LIT_CHAR  ";
		tokens[4] 	= "SYMBOL_LIT_STRING";
		tokens[5] 	= "SYMBOL_LIT_TRUE  ";
		tokens[6] 	= "SYMBOL_LIT_FALSE";
		tokens[8] 	= "SYMBOL_SCALAR";
		tokens[9] 	= "SYMBOL_LABEL";
		tokenArrayInit = 1;
	}

	if (tokens[code] == NULL)
		return "(token ascii)";

	return tokens[code];
}

#endif

extern int getLineNumber();
extern YYSTYPE yylval;

void hashStart(void)
{
	int i;
	for (i = 0; i < HASH_SIZE; i++)
		table[i] = NULL;
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
		yylval.symbol = newNode;
		return newNode;
	}
    
	int adress = hash_code(text);
	newNode = calloc(1, sizeof(HASH_NODE));

	newNode->next = table[adress];
	table[adress] = newNode;

	newNode->type = type;
	newNode->text = malloc(strlen(text) + 1);
	strcpy(newNode->text, text);

	newNode->dataNature = NATURE_UNKNOWN;
	newNode->dataType = DATATYPE_UNKNOWN;
	newNode->funcParam = NULL;
	yylval.symbol = newNode;

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
			printf("Endereco: %d\t%s\t(%d)\tDatatype: %d\tTexto: %s\n", i, getTokenName(node->type), node->type, node->dataType, node->text);
			node = node->next;
		}
	}
}

HASH_NODE *makeTemp(void){
	static char tempBuffer[256] = "";
	static int nextTemp = 0;

	HASH_NODE *new = 0;

	sprintf(tempBuffer,"__TEMP__%d__", nextTemp);

	++nextTemp;

	new = hash_insert(SYMBOL_SCALAR, tempBuffer);
	//new->type = SYMBOL_SCALAR;

	return new;
}

HASH_NODE *makeLabel(void){
	static char labelBuffer[256] = "";
	static int nextLabel = 0;

	HASH_NODE *new = 0;
	
	sprintf(labelBuffer,"__LABEL__%d__", nextLabel);

	++nextLabel;

	new = hash_insert(SYMBOL_LABEL, labelBuffer);
	//new->type = SYMBOL_LABEL;

	return new;
}


