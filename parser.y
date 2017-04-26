/*
Etapa 2 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

%{
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int getLineNumber(void);
extern int yylex();

%}  

%union
  {
  HASH_NODE* symbol;
  };

%token KW_BYTE       256
%token KW_SHORT      257
%token KW_LONG       258
%token KW_FLOAT      259
%token KW_DOUBLE     260
%token KW_WHEN       261
%token KW_THEN       262
%token KW_ELSE       263
%token KW_WHILE      264
%token KW_FOR        265
%token KW_READ       266
%token KW_RETURN     267
%token KW_PRINT      268

%token OPERATOR_LE   270
%token OPERATOR_GE   271
%token OPERATOR_EQ   272
%token OPERATOR_NE   273
%token OPERATOR_AND  274
%token OPERATOR_OR   275

%token<symbol> SYMBOL_UNDEFINED 	0
%token<symbol> TK_IDENTIFIER 		280
%token<symbol> LIT_INTEGER   		281
%token<symbol> LIT_REAL      		282
%token<symbol> LIT_CHAR      		285
%token<symbol> LIT_STRING    		286

%token TOKEN_ERROR   290

%left '!'
%left '+' '-'
%left '*' '/'
%left OPERATOR_OR
%left OPERATOR_AND

%%

programa 
		: declaracao programa
		|
		;
	
declaracao
		: declara_variavel
		| declara_funcao
		;
		
declara_variavel
		: TK_IDENTIFIER ':' tipo_variavel literal_numerica ';'
		| TK_IDENTIFIER ':' tipo_variavel '[' LIT_INTEGER ']' inicializacao_vetor ';'
		;

literal_numerica
		: LIT_INTEGER
		| LIT_REAL
		| LIT_CHAR
		;

inicializacao_vetor
		: literal_numerica inicializacao_vetor
		|
		;

tipo_variavel
		: KW_BYTE
		| KW_SHORT
		| KW_LONG
		| KW_FLOAT
		| KW_DOUBLE
		;

declara_funcao
		: tipo_variavel TK_IDENTIFIER '(' lista_parametros ')' comando ';'
		;

lista_parametros
		: declara_parametro ',' lista_parametros
		|
		;

declara_parametro
		: tipo_variavel TK_IDENTIFIER
		;

lista_comandos
		: comando ';'
		| comando ';' lista_comandos
		;

comando
		: atribuicao
		| '{' lista_comandos '}'
		| KW_READ TK_IDENTIFIER
		| KW_PRINT expressao lista_print
		| KW_RETURN expressao 
		|
		;

lista_print
		: expressao lista_print
		|
		;

atribuicao
		: TK_IDENTIFIER '=' expressao
		| TK_IDENTIFIER '#' expressao '=' expressao
		;

operador_binario
		: '+'
		| '-'
		| '*'
		| '/'
		| '>'
		| '<'
		| OPERATOR_LE
		| OPERATOR_GE
		| OPERATOR_EQ
		| OPERATOR_NE
		| OPERATOR_AND
		| OPERATOR_OR
		;

operador_unario
		: '!'
		;

expressao
		: '(' expressao_simples ')'
		| '(' operador_unario expressao_simples ')'
		| '(' expressao_simples operador_binario expressao_simples ')'
		| expressao_simples
		| operador_unario expressao_simples
		| expressao_simples operador_binario expressao_simples
		;

chama_parametros
		: expressao ',' chama_parametros
		|
		;

expressao_simples
		: TK_IDENTIFIER
		| TK_IDENTIFIER '[' LIT_INTEGER ']'
		//| TK_IDENTIFIER '(' chama_parametros ')'
		| literal_numerica
		| LIT_STRING
		;
		
controle_de_fluxo
		: 

%%

int yyerror(char* str)
{
	printf("ERRO: \"%s\" na linha: %d\n", str, getLineNumber());
	exit(3);
}
