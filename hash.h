#ifndef HASH_H_
#define HASH_H_

#include <stdio.h>

#define HASH_SIZE 997
#define VAR_LENGTH 64

typedef struct hash_data {
	int 	integer_value;
	float 	floating_value;
	int 	boolean_value;
	char 	character_value;
	char	*string_value;
	char	*identifier_value;
} HASH_DATA;

typedef struct hash_node {
	int token;
	HASH_DATA data;
	struct hash_node *next;
} HASH_NODE;

void hash_init(void);
int hash_code(char *text);
HASH_NODE* hash_insert(int token, char *text);
HASH_NODE* hash_search(int token, char *text);
void hash_print(void);

#endif
