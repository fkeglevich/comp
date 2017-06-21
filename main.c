/*
Etapa 5 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

extern int getLineNumber();
extern int isRunning();
extern int yylex();
extern int yyparse();
extern FILE* OUT_FILE;
extern FILE *outputTAC;

int main (int argv, char **argc)
{
	int token;
	if (argv < 3)
	{
		printf("Arquivo nao informado!\n");
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

	FILE* outTAC = fopen(argc[3], "w+");
	if (!outTAC)
	{
		printf("Erro ao gerar arquivo de saida TAC!\n");
		exit(1);
	}
	outputTAC = outTAC;
	
	initMe();
	yyparse();
	hash_print();
	fclose(out);
	fclose(outputTAC);
	printf("Programa reconhecido com sucesso!\n");
	exit(0);
	
	return 0;
}
