/*
Etapa 1 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

extern int getLineNumber();
extern int isRunning();
extern int yylex();

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
	printf("Linha:\tToken:\t\t\tTexto:\n");
	while (isRunning())
	{
		token = yylex();
		if (!isRunning()) break;
				
		printf("%d\t%s\t(%d)\t%s\n", getLineNumber(), getTokenName(token), token, yytext);
	}
	printf("Imprimindo os valores na hash: \n");
	hash_print();
	
	return 0;
}
