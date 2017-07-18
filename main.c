/*
Etapa 5 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include "asm.h"

extern int getLineNumber();
extern int isRunning();
extern int yylex();
extern int yyparse();
extern FILE* OUT_FILE;

int main (int argv, char **argc)
{
	int token;
	if (argv < 3)
	{
		printf("Arquivos nao informados!\n");
		exit(1);
	}

	yyin = fopen(argc[1], "r");
	if (!yyin)
	{
		printf("Arquivo inexistente!\n");
		exit(2);
	}
	
	FILE* out = fopen(argc[2], "w");
	if (!out)
	{
		printf("Erro ao gerar arquivo de saida!\n");
		exit(1);
	}
	OUT_FILE = out;

	initMe();
	yyparse();
	hash_print();


	 fprintf(stderr,"<<TAC_SYMBOL's omitidas para facilitar a leitura.>>\n");
	 tacPrintForward(tacReverse(tacGenerate(ast)));

	FILE* asmFile = fopen("SAIDA_ASM.S", "w+");
	if(asmFile == NULL){
		fprintf(stderr, "%s", "Can't create asm file. \n");
		exit(2);
	}
	
	asmGen(tacReverse(tacGenerate(ast)), asmFile);
	fclose(asmFile);
	fclose(out);
	//printf("Programa reconhecido com sucesso!\n");
	exit(0);
	
	return 0;
}
