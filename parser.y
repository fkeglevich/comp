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
		: KW_DECLARE SYMBOL_IDENTIFIER ':' tipo ';'
		| KW_DECLARE SYMBOL_IDENTIFIER ':' tipo '[' SYMBOL_LIT_INTEGER ']'';'
		;
		
declara_funcao
 		: SYMBOL_IDENTIFIER ':' tipo '(' parametros ')' ';'
		| SYMBOL_IDENTIFIER ':' tipo '(' parametros ')' comando ';'
		;

bloco
		: comando
		| comando ';' bloco
		;
		
comando
		: KW_INPUT SYMBOL_IDENTIFIER
		| KW_OUTPUT elemento
		| KW_RETURN expressao
		| KW_DECLARE SYMBOL_IDENTIFIER ':' tipo
		| KW_DECLARE SYMBOL_IDENTIFIER ':' tipo '[' SYMBOL_LIT_INTEGER ']'
		| SYMBOL_IDENTIFIER '=' expressao
		| SYMBOL_IDENTIFIER '[' expressao ']' '=' expressao
		| controle
		| '{' bloco '}'
		|
		;

elemento
		: constante
		| constante ',' elemento
		| SYMBOL_IDENTIFIER
		| SYMBOL_IDENTIFIER ',' elemento
		;

constante
		: SYMBOL_LIT_INTEGER
		| SYMBOL_LIT_FLOATING
		| SYMBOL_LIT_TRUE
		| SYMBOL_LIT_FALSE
		| SYMBOL_LIT_CHAR
		| SYMBOL_LIT_STRING
		;

expressao
		: '(' expressao_primaria ')'
		| '(' expressao_primaria operador expressao ')'
		| expressao_primaria
		| expressao_primaria operador expressao
		;
        	
expressao_primaria
		: SYMBOL_IDENTIFIER
		| constante
		| SYMBOL_IDENTIFIER '[' expressao ']'	
		| SYMBOL_IDENTIFIER '(' chamada_parametros ')'
		;
		
operador
		: '+' 
		| '-' 
		| '*' 
		| '/' 
		| '>' 
		| '<' 
		| OPERATOR_AND 
		| OPERATOR_OR 
		| OPERATOR_LE 
		| OPERATOR_GE 
		| OPERATOR_EQ 
		| OPERATOR_NE 
		;

chamada_parametro
		: constante
		| constante ',' chamada_parametro
		| SYMBOL_IDENTIFIER
		| SYMBOL_IDENTIFIER ',' chamada_parametro
		;

chamada_parametros
		: chamada_parametro
		|
		;

controle
		: KW_IF '(' expressao ')' KW_THEN bloco
		| KW_IF '(' expressao ')' KW_THEN bloco KW_ELSE bloco
		| KW_WHILE '(' expressao ')' bloco
		| KW_DO bloco KW_WHILE '(' expressao ')'
		;

tipo
		: KW_INTEGER
		| KW_FLOATING
		| KW_CHARACTER
		| KW_BOOLEAN
		;
		
parametros
		: parametro
		|
		;	
		
parametro
		: SYMBOL_IDENTIFIER ':' tipo
		| SYMBOL_IDENTIFIER ':' tipo ',' parametro
		;
	



%%

int yyerror( char* str)
{
	printf("ERRO: \"%s\" na linha: %d\n", str, getLineNumber());
	exit(3);
}