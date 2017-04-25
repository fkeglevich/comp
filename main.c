//y.tab.h
/*ETAPA 2 - COMPILADORES - DAVI e ALEXANDRE*/

#include <stdio.h>

extern int getLineNumber();

int main (int argv, char **argc)
{
	int token;
	if (argv < 2)
	{
		printf("Quantidade de parametros errada!\n");
		exit(1);
	}
	
	yyin = fopen(argc[1], "r");
	if (!yyin)
	{
		printf("Arquivo inexistente!\n");
		exit(1);
	}
	initMe();
	
	yyparse();
		
	printf("Parsing concluido com sucesso!\n");
	
	return 0;
}
