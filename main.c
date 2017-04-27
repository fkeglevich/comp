/*
Etapa 2 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

extern int getLineNumber();
extern int isRunning();
extern int yylex();
extern int yyparse();

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
	printf("Programa reconhecido com sucesso!\n");
	exit(0);
	
	return 0;
}
