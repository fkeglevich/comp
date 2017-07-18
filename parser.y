/*
Etapa 5 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

%{
#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"
#include "tac.h"

int getLineNumber(void);

extern int yylex();
TAC *tac;

%}  

%union
{
	HASH_NODE* symbol;
	AST_NODE* astNode;
};

%type<astNode> inicio
%type<astNode> programa
%type<astNode> declaracao
%type<astNode> declara_variavel
%type<astNode> literal_numerica
%type<astNode> inicializacao_vetor
%type<astNode> indice_vetor
%type<astNode> tipo_variavel
%type<astNode> declara_funcao
%type<astNode> lista_parametros
%type<astNode> declara_parametro
%type<astNode> lista_comandos
%type<astNode> comando
%type<astNode> lista_print
%type<astNode> expressao
%type<astNode> atribuicao
%type<astNode> chama_parametros
%type<astNode> controle_de_fluxo

%token KW_BYTE			256
%token KW_SHORT			257
%token KW_LONG			258
%token KW_FLOAT			259
%token KW_DOUBLE		260
%token KW_WHEN			261
%token KW_THEN			262
%token KW_ELSE			263
%token KW_WHILE			264
%token KW_FOR			265
%token KW_READ			266
%token KW_RETURN		267
%token KW_PRINT			268
%token KW_TO			269
%token KW_BOOL		 	276

%token OPERATOR_LE		270
%token OPERATOR_GE		271
%token OPERATOR_EQ		272
%token OPERATOR_NE		273
%token OPERATOR_AND	274
%token OPERATOR_OR		275

%token<symbol> TK_IDENTIFIER 		280
%token<symbol> LIT_INTEGER   		281
%token<symbol> LIT_REAL      			282
%token<symbol> LIT_CHAR      			285
%token<symbol> LIT_STRING    			286
%token<symbol> LIT_TRUE      			287
%token<symbol> LIT_FALSE     			288

%token TOKEN_ERROR   290

%left OPERATOR_OR
%left OPERATOR_AND
%nonassoc OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE '<' '>'
%left '+' '-'
%left '*' '/'
%right '!'

%%

inicio: programa		{ast_print_tree($1); checkProgram($1); ast = $1;};

programa 
		: declaracao programa	{$$ = ast_insert(AST_PROGRAM, NULL, $1, $2, NULL, NULL);}
		|					{$$ = NULL;}
		;
	
declaracao
		: declara_variavel		{$$ = $1;}
		| declara_funcao		{$$ = $1;}
		;
		
declara_variavel
		: TK_IDENTIFIER ':' tipo_variavel literal_numerica ';'					{$$ = ast_insert(AST_VAR_DEC, $1, $3, $4, NULL, NULL);}
		| TK_IDENTIFIER ':' tipo_variavel '[' indice_vetor ']' inicializacao_vetor ';'	{$$ = ast_insert(AST_VEC_DEC, $1, $3, $5, $7, NULL);}
		;

indice_vetor : LIT_INTEGER	{$$ = ast_insert(AST_LITERAL, $1, NULL, NULL, NULL, NULL);};

literal_numerica
		: LIT_INTEGER	{$$ = ast_insert(AST_LITERAL, $1, NULL, NULL, NULL, NULL);}
		| LIT_REAL		{$$ = ast_insert(AST_LITERAL, $1, NULL, NULL, NULL, NULL);}
		| LIT_CHAR		{$$ = ast_insert(AST_LITERAL, $1, NULL, NULL, NULL, NULL);}
		| LIT_TRUE		{$$ = ast_insert(AST_LITERAL, $1, NULL, NULL, NULL, NULL);}
		| LIT_FALSE		{$$ = ast_insert(AST_LITERAL, $1, NULL, NULL, NULL, NULL);}
		;

inicializacao_vetor
		: literal_numerica inicializacao_vetor	{$$ = ast_insert(AST_VEC_INIT, NULL, $1, $2, NULL, NULL);}
		|								{$$ = NULL;}
		;

tipo_variavel
		: KW_BYTE						{$$ = ast_insert(AST_BYTE, NULL, NULL, NULL, NULL, NULL);}
		| KW_SHORT						{$$ = ast_insert(AST_SHORT, NULL, NULL, NULL, NULL, NULL);}
		| KW_LONG						{$$ = ast_insert(AST_LONG, NULL, NULL, NULL, NULL, NULL);}
		| KW_FLOAT						{$$ = ast_insert(AST_FLOAT, NULL, NULL, NULL, NULL, NULL);}
		| KW_DOUBLE						{$$ = ast_insert(AST_DOUBLE, NULL, NULL, NULL, NULL, NULL);}
		| KW_BOOL						{$$ = ast_insert(AST_BOOL, NULL, NULL, NULL, NULL, NULL);}
		;

declara_funcao: tipo_variavel TK_IDENTIFIER '(' lista_parametros ')' comando ';'	{$$ = ast_insert(AST_FUNC_DEC, $2, $1, $4, $6, NULL);};	

lista_parametros
		: declara_parametro					{$$ = $1;}
		| declara_parametro ',' lista_parametros		{$$ = ast_insert(AST_ARGS_LIST, NULL, $1, $3, NULL, NULL);}
		|									{$$ = NULL;}
		;

declara_parametro: tipo_variavel TK_IDENTIFIER		{$$ = ast_insert(AST_DEC_ARGS, $2, $1, NULL, NULL, NULL);};

lista_comandos
		: comando ';' lista_comandos				{$$ = ast_insert(AST_COMMANDS, NULL, $1, $3, NULL, NULL);}
		|									{$$ = NULL;}
		;

comando
		: atribuicao							{$$ = $1;}
		| '{' lista_comandos '}'					{$$ = ast_insert(AST_COMMAND_LIST, NULL, $2, NULL, NULL, NULL);}
		| KW_READ TK_IDENTIFIER				{$$ = ast_insert(AST_READ, $2, NULL, NULL, NULL, NULL);}
		| KW_PRINT expressao lista_print			{$$ = ast_insert(AST_PRINT, NULL, $2, $3, NULL, NULL);}
		| KW_RETURN expressao 				{$$ = ast_insert(AST_RETURN, NULL, $2, NULL, NULL, NULL);}
		| controle_de_fluxo						{$$ = $1;}
		|									{$$ = NULL;}
		;

lista_print
		: expressao lista_print						{$$ = ast_insert(AST_PRINT_ARGS, NULL, $1, $2, NULL, NULL);}
		|										{$$ = NULL;}
		;

atribuicao
		: TK_IDENTIFIER '=' expressao				{$$ = ast_insert(AST_ATRIB, $1, $3, NULL, NULL, NULL);}
		| TK_IDENTIFIER '#' expressao '=' expressao		{$$ = ast_insert(AST_ATRIB_VECTOR, $1, $3, $5, NULL, NULL);}
		;

expressao
		: '(' expressao ')'						{$$ = ast_insert(AST_PARENTHESES, NULL, $2, NULL, NULL, NULL);}
		| expressao '+' expressao				{$$ = ast_insert(AST_ADD, NULL, $1, $3, NULL, NULL);}
		| expressao '-' expressao					{$$ = ast_insert(AST_SUB, NULL, $1, $3, NULL, NULL);}
		| expressao '*' expressao					{$$ = ast_insert(AST_MUL, NULL, $1, $3, NULL, NULL);}
		| expressao '/' expressao					{$$ = ast_insert(AST_DIV, NULL, $1, $3, NULL, NULL);}
		| expressao '>' expressao				{$$ = ast_insert(AST_GT, NULL, $1, $3, NULL, NULL);}
		| expressao '<' expressao				{$$ = ast_insert(AST_LT, NULL, $1, $3, NULL, NULL);}
		| expressao OPERATOR_LE expressao		{$$ = ast_insert(AST_LE, NULL, $1, $3, NULL, NULL);}
		| expressao OPERATOR_GE expressao		{$$ = ast_insert(AST_GE, NULL, $1, $3, NULL, NULL);}
		| expressao OPERATOR_EQ expressao		{$$ = ast_insert(AST_EQ, NULL, $1, $3, NULL, NULL);}
		| expressao OPERATOR_NE expressao		{$$ = ast_insert(AST_NE, NULL, $1, $3, NULL, NULL);}
		| expressao OPERATOR_AND expressao		{$$ = ast_insert(AST_AND, NULL, $1, $3, NULL, NULL);}
		| expressao OPERATOR_OR expressao		{$$ = ast_insert(AST_OR, NULL, $1, $3, NULL, NULL);}
		| '!' expressao							{$$ = ast_insert(AST_NOT, NULL, $2, NULL, NULL, NULL);}
		| TK_IDENTIFIER						{$$ = ast_insert(AST_ID, $1, NULL, NULL, NULL, NULL);}
		| TK_IDENTIFIER '[' expressao ']'			{$$ = ast_insert(AST_ID_VECTOR, $1, $3, NULL, NULL, NULL);}
		| TK_IDENTIFIER '(' chama_parametros ')'	{$$ = ast_insert(AST_ID_CALL, $1, $3, NULL, NULL, NULL);}
		| literal_numerica						{$$ = $1;}
		| LIT_STRING							{$$ = ast_insert(AST_LITERAL, $1, NULL, NULL, NULL, NULL);}
		;

chama_parametros
		: expressao							{$$ = $1;}
		| expressao ',' chama_parametros			{$$ = ast_insert(AST_PARAM_LIST, NULL, $1, $3, NULL, NULL);}
		|									{$$ = NULL;}
		;

controle_de_fluxo
		: KW_WHEN '(' expressao ')' KW_THEN comando						{$$ = ast_insert(AST_WHEN, NULL, $3, $6, NULL, NULL);}
		| KW_WHEN '(' expressao ')' KW_THEN comando KW_ELSE comando		{$$ = ast_insert(AST_WHEN_ELSE, NULL, $3, $6, $8, NULL);}
		| KW_WHILE '(' expressao ')' comando								{$$ = ast_insert(AST_WHILE, NULL, $3, $5, NULL, NULL);}
		| KW_FOR '(' TK_IDENTIFIER '=' expressao KW_TO expressao ')' comando	{$$ = ast_insert(AST_FOR, $3, $5, $7, $9, NULL);}
		;

%%

int yyerror(char* str)
{
	printf("Programa não reconhecido, erro: \"%s\" na linha: %d\n", str, getLineNumber());
	exit(3);
}
