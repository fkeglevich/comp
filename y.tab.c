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

#line 21 "parser.y"
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
#line 41 "y.tab.c"

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
#define OPERATOR_LE 270
#define OPERATOR_GE 271
#define OPERATOR_EQ 272
#define OPERATOR_NE 273
#define OPERATOR_AND 274
#define OPERATOR_OR 275
#define SYMBOL_UNDEFINED 0
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
    6,    6,    4,    4,    4,    4,    4,    3,    7,    7,
    7,    9,   10,   11,   11,    8,    8,    8,    8,    8,
    8,   14,   14,   12,   12,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   15,   15,   15,   13,   13,   13,
   13,   13,   13,   13,   13,   13,
};
static const YYINT yylen[] = {                            2,
    2,    0,    1,    1,    5,    8,    1,    1,    1,    1,
    2,    0,    1,    1,    1,    1,    1,    6,    1,    2,
    0,    2,    3,    2,    0,    1,    1,    2,    3,    2,
    0,    2,    0,    3,    5,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    3,    2,    1,
    4,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
   13,   14,   15,   16,   17,    0,    0,    0,    3,    4,
    0,    0,    1,    0,    0,    0,    7,    8,    9,    0,
    0,    0,    0,    0,    0,    5,   22,    0,   20,    0,
    0,    0,    0,    0,    0,   18,   27,   26,    0,    0,
   28,    0,   52,   53,   54,   56,    0,    0,    0,    0,
    0,    0,    0,   11,    6,    0,    0,   42,   43,   44,
   45,   46,   47,   36,   37,   38,   39,   40,   41,    0,
    0,   29,    0,    0,   24,   23,    0,    0,   32,    0,
   51,    0,
};
static const YYINT yydgoto[] = {                          7,
    8,    9,   10,   11,   39,   40,   23,   36,   24,   37,
   53,   38,   71,   72,   70,
};
static const YYINT yysindex[] = {                      -168,
    0,    0,    0,    0,    0,  -45,    0, -168,    0,    0,
 -254, -163,    0,  -17,  -87, -163,    0,    0,    0, -251,
  -28, -247,   -4,   -6,  -53,    0,    0, -117,    0, -257,
 -235,   48,   48,  -19, -117,    0,    0,    0, -257,  -10,
    0,  -41,    0,    0,    0,    0,   48,   78,  -33,   48,
   48,   -8,  -72,    0,    0, -227,   78,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   48,
  -33,    0,   78,  -40,    0,    0,  -37,   78,    0,   48,
    0,   78,
};
static const YYINT yyrindex[] = {                        58,
    0,    0,    0,    0,    0,    0,    0,   58,    0,    0,
    0,    0,    0,    0,    0,   18,    0,    0,    0,    0,
    0,    0,    0,   23,    0,    0,    0,   87,    0,    7,
    0,    0,    0,    0,  -48,    0,    0,    0,    9,    0,
    0,    1,    0,    0,    0,    0,    0,   47,   82,    0,
    0,    0,    0,    0,    0,    0,    8,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   82,    0,   52,    0,    0,    0,    0,   39,    0,    0,
    0,   57,
};
static const YYINT yygindex[] = {                        62,
    0,    0,    0,    3,   56,   34,    0,   40,    0,    0,
    0,    0,  -15,    5,    0,
};
#define YYTABLESIZE 353
static const YYINT yytable[] = {                         47,
   50,   66,   64,   20,   65,   35,   67,   49,   66,   64,
   31,   65,   12,   67,   15,   51,   48,   49,   22,   69,
   80,   68,   16,   17,   18,   14,   69,   19,   68,   25,
   26,   57,   27,   50,   73,   74,   28,   29,   48,   30,
   49,   50,   50,   50,   41,   50,   30,   50,   55,   56,
   75,   34,   76,   77,   78,   81,   35,    2,   21,   50,
   50,   50,   50,   19,   82,   12,   49,   10,   49,   13,
   21,   48,   54,    0,   52,   79,   25,    0,    0,    0,
   47,   33,    0,    0,    0,    0,   31,    1,    2,    3,
    4,    5,    1,    2,    3,    4,    5,   48,    0,   48,
    0,    0,    0,    0,    0,   30,    0,    0,    0,    0,
   34,    6,    0,    0,    0,   35,    0,    0,    0,   66,
   64,    0,   65,    0,   67,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   69,    0,   68,
   33,    0,    0,    0,    0,    0,    0,    0,   31,   32,
   33,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   34,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   17,   18,    0,    0,   19,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   58,
   59,   60,   61,   62,   63,    0,   58,   59,   60,   61,
   62,   63,    0,    0,    0,    0,   42,   43,   44,    0,
    0,   45,   46,    0,    0,    0,   50,   50,   50,   50,
   50,    0,    0,   49,   49,   49,   49,   49,    0,    0,
   50,   50,   50,   50,   50,   50,    0,    0,    0,    0,
   50,   50,   50,    0,    0,   50,   50,   49,   49,   49,
    0,    0,   49,   49,   48,   48,   48,   48,   48,    0,
    0,    0,   30,   30,   30,   30,   30,   34,   34,   34,
   34,   34,   35,   35,   35,   35,   35,    0,   48,   48,
   48,    0,    0,   48,   48,    0,   30,   42,   43,   44,
    0,   34,   45,   46,    0,    0,   35,   33,   33,   33,
   33,   33,   31,   31,   31,   31,   31,   58,   59,   60,
   61,   62,   63,
};
static const YYINT yycheck[] = {                         33,
    0,   42,   43,   91,   45,  123,   47,    0,   42,   43,
   59,   45,   58,   47,   12,   35,   32,   33,   16,   60,
   61,   62,   40,  281,  282,  280,   60,  285,   62,  281,
   59,   47,  280,   33,   50,   51,   41,   44,    0,   93,
   33,   61,   42,   43,  280,   45,    0,   47,   59,   91,
   59,    0,  125,  281,   70,   93,    0,    0,   41,   59,
   60,   61,   62,   41,   80,   59,   59,   59,   61,    8,
   15,   33,   39,   -1,   35,   71,  125,   -1,   -1,   -1,
   33,    0,   -1,   -1,   -1,   -1,    0,  256,  257,  258,
  259,  260,  256,  257,  258,  259,  260,   59,   -1,   61,
   -1,   -1,   -1,   -1,   -1,   59,   -1,   -1,   -1,   -1,
   59,  280,   -1,   -1,   -1,   59,   -1,   -1,   -1,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,   -1,   62,
   59,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  266,  267,
  268,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  280,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  281,  282,   -1,   -1,  285,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  270,
  271,  272,  273,  274,  275,   -1,  270,  271,  272,  273,
  274,  275,   -1,   -1,   -1,   -1,  280,  281,  282,   -1,
   -1,  285,  286,   -1,   -1,   -1,  256,  257,  258,  259,
  260,   -1,   -1,  256,  257,  258,  259,  260,   -1,   -1,
  270,  271,  272,  273,  274,  275,   -1,   -1,   -1,   -1,
  280,  281,  282,   -1,   -1,  285,  286,  280,  281,  282,
   -1,   -1,  285,  286,  256,  257,  258,  259,  260,   -1,
   -1,   -1,  256,  257,  258,  259,  260,  256,  257,  258,
  259,  260,  256,  257,  258,  259,  260,   -1,  280,  281,
  282,   -1,   -1,  285,  286,   -1,  280,  280,  281,  282,
   -1,  280,  285,  286,   -1,   -1,  280,  256,  257,  258,
  259,  260,  256,  257,  258,  259,  260,  270,  271,  272,
  273,  274,  275,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#define YYUNDFTOKEN 308
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
"KW_RETURN","KW_PRINT",0,"OPERATOR_LE","OPERATOR_GE","OPERATOR_EQ",
"OPERATOR_NE","OPERATOR_AND","OPERATOR_OR",0,0,0,0,"TK_IDENTIFIER",
"LIT_INTEGER","LIT_REAL",0,0,"LIT_CHAR","LIT_STRING",0,0,0,"TOKEN_ERROR",0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : programa",
"programa : declaracao programa",
"programa :",
"declaracao : declara_variavel",
"declaracao : declara_funcao",
"declara_variavel : TK_IDENTIFIER ':' tipo_variavel inicializacao_variavel ';'",
"declara_variavel : TK_IDENTIFIER ':' tipo_variavel '[' LIT_INTEGER ']' inicializacao_vetor ';'",
"inicializacao_variavel : LIT_INTEGER",
"inicializacao_variavel : LIT_REAL",
"inicializacao_variavel : LIT_CHAR",
"inicializacao_vetor : inicializacao_variavel",
"inicializacao_vetor : inicializacao_variavel inicializacao_vetor",
"inicializacao_vetor :",
"tipo_variavel : KW_BYTE",
"tipo_variavel : KW_SHORT",
"tipo_variavel : KW_LONG",
"tipo_variavel : KW_FLOAT",
"tipo_variavel : KW_DOUBLE",
"declara_funcao : tipo_variavel TK_IDENTIFIER '(' lista_parametros ')' comando",
"lista_parametros : parametro",
"lista_parametros : parametro ','",
"lista_parametros :",
"parametro : tipo_variavel TK_IDENTIFIER",
"bloco_comandos : '{' lista_comandos '}'",
"lista_comandos : comando ';'",
"lista_comandos :",
"comando : atribuicao",
"comando : bloco_comandos",
"comando : KW_READ TK_IDENTIFIER",
"comando : KW_PRINT expressao lista_print",
"comando : KW_RETURN expressao",
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
"expressao : expressao operador_binario expressao",
"expressao : '!' expressao",
"expressao : TK_IDENTIFIER",
"expressao : TK_IDENTIFIER '[' LIT_INTEGER ']'",
"expressao : LIT_INTEGER",
"expressao : LIT_REAL",
"expressao : LIT_CHAR",
"expressao : LIT_INTEGER",
"expressao : LIT_STRING",

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
#line 168 "parser.y"

int yyerror(char* str)
{
	printf("ERRO: \"%s\" na linha: %d\n", str, getLineNumber());
	exit(3);
}
#line 362 "y.tab.c"

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
