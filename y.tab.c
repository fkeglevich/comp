/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 12 "parser.y"
#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

int getLineNumber(void);
extern int yylex();

#line 22 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union
  {
  HASH_NODE* symbol;
  } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 42 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_BYTE 256
#define KW_SHORT 257
#define KW_LONG 258
#define KW_FLOAT 259
#define KW_DOUBLE 260
#define KW_WHEN 261
#define KW_THEN 262
#define KW_ELSE 263
#define KW_WHILE 264
#define KW_FOR 265
#define KW_READ 266
#define KW_RETURN 267
#define KW_PRINT 268
#define KW_TO 269
#define OPERATOR_LE 270
#define OPERATOR_GE 271
#define OPERATOR_EQ 272
#define OPERATOR_NE 273
#define OPERATOR_AND 274
#define OPERATOR_OR 275
#define TK_IDENTIFIER 280
#define LIT_INTEGER 281
#define LIT_REAL 282
#define LIT_CHAR 285
#define LIT_STRING 286
#define TOKEN_ERROR 290
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    1,    1,    2,    2,    5,    5,    5,    6,
    6,    4,    4,    4,    4,    4,    3,    7,    7,    7,
    9,   10,   10,    8,    8,    8,    8,    8,    8,    8,
   13,   13,   11,   11,   15,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   15,   15,   16,   12,   12,   12,
   12,   12,   12,   17,   17,   17,   17,   17,   18,   18,
   18,   14,   14,   14,   14,
};
static const YYINT yylen[] = {                            2,
    2,    0,    1,    1,    5,    8,    1,    1,    1,    2,
    0,    1,    1,    1,    1,    1,    7,    1,    3,    0,
    2,    3,    0,    1,    3,    2,    3,    2,    1,    0,
    2,    0,    3,    5,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    3,    4,    5,
    1,    2,    3,    1,    4,    4,    1,    1,    1,    3,
    0,    6,    8,    5,    9,
};
static const YYINT yydefred[] = {                         0,
   12,   13,   14,   15,   16,    0,    0,    0,    3,    4,
    0,    0,    1,    0,    0,    0,    7,    8,    9,    0,
    0,    0,    0,    0,    0,    5,   21,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   24,
   29,   19,    0,    0,    0,    0,    0,   26,    0,   58,
   47,    0,   57,   28,    0,    0,    0,    0,    0,    0,
    0,   17,   10,    6,    0,    0,    0,    0,    0,    0,
    0,   52,   41,   42,   43,   44,   45,   46,   35,   36,
   37,   38,   39,   40,    0,    0,   27,   33,    0,    0,
   25,    0,    0,    0,    0,    0,    0,    0,   48,    0,
   53,   31,    0,   22,    0,   64,    0,   55,    0,   56,
   49,    0,   34,    0,    0,   60,   50,    0,    0,   63,
    0,   65,
};
static const YYINT yydgoto[] = {                          7,
    8,    9,   10,   11,   53,   44,   23,   60,   24,   61,
   40,   86,   87,   41,   85,   55,   56,   97,
};
static const YYINT yysindex[] = {                      -163,
    0,    0,    0,    0,    0,  -39,    0, -163,    0,    0,
 -257, -149,    0,  -10,  -88, -149,    0,    0,    0, -243,
  -20, -235,    5,   11,  -44,    0,    0, -119, -149, -265,
   17,   18,   19, -216,  -18,  -18,  -28, -119,   15,    0,
    0,    0, -265,   16,  -18,  -18, -210,    0,  -35,    0,
    0,    1,    0,    0, -238,   26,  -18,  -18,  -18,   22,
  -49,    0,    0,    0,   36,   38,   24,  -18,  -18, -238,
   20,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -238,  -18,    0,    0,   28, -119,
    0, -179, -119,  -18,   -6,   54,   58,   59,    0, -238,
    0,    0,  -18,    0, -119,    0, -165,    0,  -18,    0,
    0,   64,    0, -151,  -18,    0,    0, -119,   72,    0,
 -119,    0,
};
static const YYINT yyrindex[] = {                       116,
    0,    0,    0,    0,    0,    0,    0,  116,    0,    0,
    0,    0,    0,    0,    0,   77,    0,    0,    0,    0,
    0,    0,    0,   78,    0,    0,    0,   61,   77,   62,
    0,    0,    0,    0,    0,    0,    0,  -53,    0,    0,
    0,    0,   62,    0,    0,    0,    0,    0,  -33,    0,
    0,    0,    0,    0,    0,   -9,  -58,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   81,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -58,    0,    0,    0,  -53,
    0,    0,  -57,    0,    0,   82,    0,    0,    0,    0,
    0,    0,    0,    0,  -57,    0,    0,    0,   81,    0,
    0,    0,    0,   15,    0,    0,    0,  -57,    0,    0,
  -57,    0,
};
static const YYINT yygindex[] = {                       118,
    0,    0,    0,   25,   10,   84,   99,  -15,    0,   39,
    0,   56,   44,    0,   60,   80,  -34,   27,
};
#define YYTABLESIZE 301
static const YYINT yytable[] = {                         54,
   32,   30,   20,   38,   69,   30,   59,   54,   54,   54,
   54,   54,   39,   54,   51,   17,   18,   71,   12,   19,
   72,   52,   14,   51,   21,   54,   54,   54,   54,   16,
   51,   51,   58,   51,   51,   98,   15,   25,   26,   43,
   22,   49,   17,   18,   27,   28,   19,   50,   30,   51,
  101,   51,   43,   22,   29,   68,   45,   46,   47,   54,
   99,   81,   79,   48,   80,  112,   82,   81,   79,   67,
   80,   23,   82,   62,   64,   91,   92,  106,   93,   84,
   90,   83,  105,   51,   94,   84,  108,   83,  103,  114,
   54,   57,    1,    2,    3,    4,    5,  109,  110,  111,
   65,   66,  120,  115,  117,  122,    1,    2,    3,    4,
    5,  118,  121,   88,   89,    2,    6,   20,   18,   30,
   11,   61,   59,   95,   96,   13,   63,   42,  104,  102,
  100,   70,    0,    0,    0,  116,    0,    0,    0,    0,
    0,   31,    0,    0,   32,   33,   34,   35,   36,  107,
    0,    0,    0,    0,    0,    0,    0,    0,  113,    0,
   37,    0,    0,    0,   96,    0,    0,    0,    0,    0,
  119,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   17,   18,    0,    0,   19,    0,    0,    0,
    0,    0,    0,    0,   32,   30,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   54,
    0,    0,    0,    0,    0,   54,   54,   54,   54,   54,
   54,   54,    0,    0,    0,    0,   54,   54,   54,    0,
    0,   54,   54,   51,    0,    0,    0,    0,    0,   51,
    0,   49,   17,   18,    0,    0,   19,   50,    0,    0,
   51,   51,   51,    0,    0,   51,   51,    0,    0,    0,
   49,   17,   18,    0,    0,   19,   50,    0,    0,   73,
   74,   75,   76,   77,   78,   73,   74,   75,   76,   77,
   78,
};
static const YYINT yycheck[] = {                         33,
   59,   59,   91,  123,   40,   59,   35,   41,   42,   43,
   44,   45,   28,   47,   33,  281,  282,   52,   58,  285,
   55,   40,  280,   33,   15,   59,   60,   61,   62,   40,
   40,   41,   61,   33,   44,   70,   12,  281,   59,   30,
   16,  280,  281,  282,  280,   41,  285,  286,   93,   59,
   85,   61,   43,   29,   44,   91,   40,   40,   40,   93,
   41,   42,   43,  280,   45,  100,   47,   42,   43,  280,
   45,  125,   47,   59,   59,  125,   41,   93,   41,   60,
   59,   62,  262,   93,   61,   60,   93,   62,   61,  105,
   35,   36,  256,  257,  258,  259,  260,   44,   41,   41,
   45,   46,  118,  269,   41,  121,  256,  257,  258,  259,
  260,  263,   41,   58,   59,    0,  280,   41,   41,   59,
   59,   41,   41,   68,   69,    8,   43,   29,   90,   86,
   71,   52,   -1,   -1,   -1,  109,   -1,   -1,   -1,   -1,
   -1,  261,   -1,   -1,  264,  265,  266,  267,  268,   94,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  103,   -1,
  280,   -1,   -1,   -1,  109,   -1,   -1,   -1,   -1,   -1,
  115,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  281,  282,   -1,   -1,  285,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  263,  263,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  263,
   -1,   -1,   -1,   -1,   -1,  269,  270,  271,  272,  273,
  274,  275,   -1,   -1,   -1,   -1,  280,  281,  282,   -1,
   -1,  285,  286,  263,   -1,   -1,   -1,   -1,   -1,  269,
   -1,  280,  281,  282,   -1,   -1,  285,  286,   -1,   -1,
  280,  281,  282,   -1,   -1,  285,  286,   -1,   -1,   -1,
  280,  281,  282,   -1,   -1,  285,  286,   -1,   -1,  270,
  271,  272,  273,  274,  275,  270,  271,  272,  273,  274,
  275,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#define YYUNDFTOKEN 311
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,"'#'",0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,
0,0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_BYTE","KW_SHORT","KW_LONG","KW_FLOAT",
"KW_DOUBLE","KW_WHEN","KW_THEN","KW_ELSE","KW_WHILE","KW_FOR","KW_READ",
"KW_RETURN","KW_PRINT","KW_TO","OPERATOR_LE","OPERATOR_GE","OPERATOR_EQ",
"OPERATOR_NE","OPERATOR_AND","OPERATOR_OR",0,0,0,0,"TK_IDENTIFIER",
"LIT_INTEGER","LIT_REAL",0,0,"LIT_CHAR","LIT_STRING",0,0,0,"TOKEN_ERROR",0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : programa",
"programa : declaracao programa",
"programa :",
"declaracao : declara_variavel",
"declaracao : declara_funcao",
"declara_variavel : TK_IDENTIFIER ':' tipo_variavel literal_numerica ';'",
"declara_variavel : TK_IDENTIFIER ':' tipo_variavel '[' LIT_INTEGER ']' inicializacao_vetor ';'",
"literal_numerica : LIT_INTEGER",
"literal_numerica : LIT_REAL",
"literal_numerica : LIT_CHAR",
"inicializacao_vetor : literal_numerica inicializacao_vetor",
"inicializacao_vetor :",
"tipo_variavel : KW_BYTE",
"tipo_variavel : KW_SHORT",
"tipo_variavel : KW_LONG",
"tipo_variavel : KW_FLOAT",
"tipo_variavel : KW_DOUBLE",
"declara_funcao : tipo_variavel TK_IDENTIFIER '(' lista_parametros ')' comando ';'",
"lista_parametros : declara_parametro",
"lista_parametros : declara_parametro ',' lista_parametros",
"lista_parametros :",
"declara_parametro : tipo_variavel TK_IDENTIFIER",
"lista_comandos : comando ';' lista_comandos",
"lista_comandos :",
"comando : atribuicao",
"comando : '{' lista_comandos '}'",
"comando : KW_READ TK_IDENTIFIER",
"comando : KW_PRINT expressao lista_print",
"comando : KW_RETURN expressao",
"comando : controle_de_fluxo",
"comando :",
"lista_print : expressao lista_print",
"lista_print :",
"atribuicao : TK_IDENTIFIER '=' expressao",
"atribuicao : TK_IDENTIFIER '#' expressao '=' expressao",
"operador_binario : '+'",
"operador_binario : '-'",
"operador_binario : '*'",
"operador_binario : '/'",
"operador_binario : '>'",
"operador_binario : '<'",
"operador_binario : OPERATOR_LE",
"operador_binario : OPERATOR_GE",
"operador_binario : OPERATOR_EQ",
"operador_binario : OPERATOR_NE",
"operador_binario : OPERATOR_AND",
"operador_binario : OPERATOR_OR",
"operador_unario : '!'",
"expressao : '(' expressao_simples ')'",
"expressao : '(' operador_unario expressao_simples ')'",
"expressao : '(' expressao_simples operador_binario expressao_simples ')'",
"expressao : expressao_simples",
"expressao : operador_unario expressao_simples",
"expressao : expressao_simples operador_binario expressao_simples",
"expressao_simples : TK_IDENTIFIER",
"expressao_simples : TK_IDENTIFIER '[' expressao ']'",
"expressao_simples : TK_IDENTIFIER '(' chama_parametros ')'",
"expressao_simples : literal_numerica",
"expressao_simples : LIT_STRING",
"chama_parametros : expressao",
"chama_parametros : expressao ',' chama_parametros",
"chama_parametros :",
"controle_de_fluxo : KW_WHEN '(' expressao ')' KW_THEN comando",
"controle_de_fluxo : KW_WHEN '(' expressao ')' KW_THEN comando KW_ELSE comando",
"controle_de_fluxo : KW_WHILE '(' expressao ')' comando",
"controle_de_fluxo : KW_FOR '(' TK_IDENTIFIER '=' expressao KW_TO expressao ')' comando",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 182 "parser.y"

int yyerror(char* str)
{
	printf("Programa não reconhecido, erro: \"%s\" na linha: %d\n", str, getLineNumber());
	exit(3);
}
#line 376 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
