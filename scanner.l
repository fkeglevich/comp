%{
#include <stdio.h>

#include "hash.h"
#include "y.tab.h"

int running = 1;
int lineCount = 0;

int getLineNumber(void);
void initMe();

#include "main.c"

%}

DIGIT	[0-9]
LETTER	[_a-zA-Z]
%x COMM

%%

"integer"					{return KW_INTEGER;}
"floating"					{return KW_FLOATING;}
"boolean"					{return KW_BOOLEAN;}
"character"					{return KW_CHARACTER;}
"declare"					{return KW_DECLARE;}
"if"						{return KW_IF;}
"then"						{return KW_THEN;}
"else"						{return KW_ELSE;}
"while"						{return KW_WHILE;}
"do"						{return KW_DO;}
"input"						{return KW_INPUT;}
"return"					{return KW_RETURN;}
"output"					{return KW_OUTPUT;}

"<="						{return OPERATOR_LE;}
">="						{return OPERATOR_GE;}
"=="						{return OPERATOR_EQ;}
"!="						{return OPERATOR_NE;}
"&&"						{return OPERATOR_AND;}
"||"						{return OPERATOR_OR;}

"true"|"TRUE"					{yylval.symbol = hash_insert(SYMBOL_LIT_TRUE, yytext);		return SYMBOL_LIT_TRUE;}
"false"|"FALSE"					{yylval.symbol = hash_insert(SYMBOL_LIT_FALSE, yytext);		return SYMBOL_LIT_FALSE;}
{LETTER}({LETTER}|{DIGIT})*		{yylval.symbol = hash_insert(SYMBOL_IDENTIFIER, yytext);	return SYMBOL_IDENTIFIER;}
'(\\.|[^\\'])+'			{yylval.symbol = hash_insert(SYMBOL_LIT_CHAR, yytext);		return SYMBOL_LIT_CHAR;}
\"(\\.|[^\\"])*\"				{yylval.symbol = hash_insert(SYMBOL_LIT_STRING, yytext);	return SYMBOL_LIT_STRING;}
{DIGIT}+\.{DIGIT}+				{yylval.symbol = hash_insert(SYMBOL_LIT_FLOATING, yytext);	return SYMBOL_LIT_FLOATING;}
\.{DIGIT}+						{yylval.symbol = hash_insert(SYMBOL_LIT_FLOATING, yytext);	return SYMBOL_LIT_FLOATING;}
{DIGIT}+\.						{yylval.symbol = hash_insert(TOKEN_ERROR, yytext);			return TOKEN_ERROR;}
{DIGIT}+						{yylval.symbol = hash_insert(SYMBOL_LIT_INTEGER, yytext);	return SYMBOL_LIT_INTEGER;}

"-"|";"|":"|","|"("|")"|"{"|"}"		{return yytext[0];}
"+"|"<"|">"|"="|"!"|"]"|"["|"*"		{return yytext[0];}
"/"									{return yytext[0];}

\n									{lineCount++;}
[ \t\v\f]

\/\/.*
"/*"								{BEGIN(COMM);}
<COMM>[^*\n]	
<COMM>"*"+[^*/\n]
<COMM>\n							{lineCount++;}
<COMM>"*"+"/"						{BEGIN(INITIAL);}

.									{printf("Caracter invalido: \"%s\" na linha %d\n",
									yytext, getLineNumber()); hash_insert(TOKEN_ERROR, yytext);return TOKEN_ERROR;}

%%

int getLineNumber(void)
{
	return lineCount + 1;
}

int yywrap(void)
{
	if (!feof(yyin)) running = 1;
	else running = 0;
	return 1;
}

void initMe()
{
	hash_init();
}
