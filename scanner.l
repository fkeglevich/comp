%{
/*
Etapa 4 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include <stdio.h>
#include "semantic.h"
#include "y.tab.h"

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4	
#define SYMBOL_LIT_TRUE 5	
#define SYMBOL_LIT_FALSE 6	
#define SYMBOL_IDENTIFIER 7	

int running = 1;
int contadorLinhas = 1;

int getLineNumber(void);
int isRunning(void);
void initMe();

#include "main.c"

%}

DIGITO		[0-9]
CARACTERE	[_a-zA-Z]
%x COMENTARIO

%%

"byte"						{return KW_BYTE;}
"short"						{return KW_SHORT;}
"long"						{return KW_LONG;}
"float"						{return KW_FLOAT;}
"double"						{return KW_DOUBLE;}
"bool"						{return KW_BOOL;} //Booleano da etapa 4
"when"						{return KW_WHEN;}
"then"						{return KW_THEN;}
"else"						{return KW_ELSE;}
"while"						{return KW_WHILE;}
"for"						{return KW_FOR;}
"read"						{return KW_READ;}
"print"						{return KW_PRINT;}
"return"						{return KW_RETURN;}
"to"							{return KW_TO;}

"<="						{return OPERATOR_LE;}
">="						{return OPERATOR_GE;}
"=="						{return OPERATOR_EQ;}
"!="						{return OPERATOR_NE;}
"&&"						{return OPERATOR_AND;}
"||"							{return OPERATOR_OR;}					
true							{hash_insert(SYMBOL_LIT_TRUE, yytext); return LIT_TRUE;}
TRUE							{hash_insert(SYMBOL_LIT_TRUE, yytext); return LIT_TRUE;}
false							{hash_insert(SYMBOL_LIT_FALSE, yytext); return LIT_FALSE;}
FALSE							{hash_insert(SYMBOL_LIT_FALSE, yytext); return LIT_FALSE;}
[-;:,(){}+*/<>=!&$#]|"]"|"["        			{return yytext[0];}

{CARACTERE}({CARACTERE}|{DIGITO})*	{hash_insert(SYMBOL_IDENTIFIER, yytext);return TK_IDENTIFIER;}

{DIGITO}+								{hash_insert(SYMBOL_LIT_INT, yytext);return LIT_INTEGER;}
{DIGITO}+\.{DIGITO}+					{hash_insert(SYMBOL_LIT_REAL, yytext);return LIT_REAL;}
\"(\\.|[^\\"|^\n])*\"						{hash_insert(SYMBOL_LIT_STRING, yytext);return LIT_STRING;}
"'"("\\".|[^'\n])"'"							{hash_insert(SYMBOL_LIT_CHAR, yytext);return LIT_CHAR;}

\/\/.*
\n										{contadorLinhas++;}
[ \t\v\f]

"/*"										BEGIN(COMENTARIO);
<COMENTARIO>.							;
<COMENTARIO>\n              				{contadorLinhas++;}
<COMENTARIO>"*/"             				BEGIN(INITIAL);

.										{return TOKEN_ERROR;}

%%

int getLineNumber(void)
{
	return contadorLinhas;
}

int isRunning(void)
{
	return running;
}

int yywrap(void)
{
	if (!feof(yyin)) 
		running = 1;
	else
		running = 0;
	return 1;
}

void initMe()
{
	hashStart();
}
