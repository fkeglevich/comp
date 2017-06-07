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

#include "semantic.h"

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
	AST_NODE* astNode;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 43 "y.tab.c"

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
#define KW_BOOL 276
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
#define LIT_TRUE 287
#define LIT_FALSE 288
#define TOKEN_ERROR 290
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    3,    3,    6,    4,    4,
    4,    4,    4,    5,    5,    7,    7,    7,    7,    7,
    7,    8,    9,    9,    9,   10,   11,   11,   12,   12,
   12,   12,   12,   12,   12,   13,   13,   15,   15,   14,
   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,
   14,   14,   14,   14,   14,   14,   14,   14,   16,   16,
   16,   17,   17,   17,   17,
};
static const YYINT yylen[] = {                            2,
    1,    2,    0,    1,    1,    5,    8,    1,    1,    1,
    1,    1,    1,    2,    0,    1,    1,    1,    1,    1,
    1,    7,    1,    3,    0,    2,    3,    0,    1,    3,
    2,    3,    2,    1,    0,    2,    0,    3,    5,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    2,    1,    4,    4,    1,    1,    1,    3,
    0,    6,    8,    5,    9,
};
static const YYINT yydefred[] = {                         0,
   16,   17,   18,   19,   20,   21,    0,    0,    1,    0,
    4,    0,    5,    0,    2,    0,    0,    0,    9,   10,
   11,   12,   13,    0,    0,    0,    0,    0,    8,    0,
    6,   26,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   29,   34,   24,    0,    0,    0,
    0,    0,   31,    0,   58,    0,    0,   57,    0,    0,
    0,    0,    0,    0,   22,   14,    7,    0,    0,    0,
    0,    0,   53,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   32,    0,    0,    0,
   30,    0,    0,    0,    0,    0,    0,    0,   40,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   43,
   44,   36,    0,   27,    0,   64,    0,   55,    0,   56,
    0,    0,    0,   60,    0,    0,   63,    0,   65,
};
static const YYINT yydgoto[] = {                          8,
    9,   10,   11,   58,   49,   30,   12,   13,   27,   28,
   63,   64,   87,   88,   45,   98,   46,
};
static const YYINT yysindex[] = {                      -175,
    0,    0,    0,    0,    0,    0,  -51,    0,    0, -175,
    0, -258,    0, -208,    0,  -17,  -67, -208,    0,    0,
    0,    0,    0, -256,  -25, -248,   -5,   -1,    0,  -48,
    0,    0,  315, -208, -133,   13,   14,   15, -217,    6,
    6,  -14,  315,   12,    0,    0,    0, -133,   20,    6,
    6, -200,    0,  -21,    0,    6,    6,    0,  504,   55,
    6,    6,  -39,   28,    0,    0,    0,  453,  460,   35,
    6,    6,    0,  467,    6,    6,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    0,   55,  504,  214,
    0,  315, -173,  315,    6,  389,  488,   65,    0,   19,
   19,   19,   19,  -27,  511,   19,   19,   27,   27,    0,
    0,    0,    6,    0,  315,    0,  497,    0,    6,    0,
  504, -156,    6,    0,  315,  476,    0,  315,    0,
};
static const YYINT yyrindex[] = {                       113,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  113,
    0,    0,    0,    0,    0,    0,    0,   75,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   77,    0,    0,
    0,    0,   60,   75,   61,    0,    0,    0,    0,    0,
    0,    0,  -58,    0,    0,    0,    0,   61,    0,    0,
    0,    0,    0,  -33,    0,    0,    0,    0,  -57,  -56,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   80,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -56,  -55,    0,
    0,  -58,    0,  -54,    0,    0,   81,    0,    0,   70,
   97,  106,  133,  142,  431,  172,  404,   -3,   32,    0,
    0,    0,    0,    0,  -54,    0,    0,    0,   80,    0,
  -53,   64,    0,    0,  -54,    0,    0,  -54,    0,
};
static const YYINT yygindex[] = {                         0,
  116,    0,    0,   -4,   79,    0,   90,    0,   94,    0,
   40,  -16,   45,  552,    0,   16,    0,
};
#define YYTABLESIZE 785
static const YYINT yytable[] = {                         54,
   35,   33,   37,   38,   35,   39,   14,   54,   54,   54,
   54,   54,   25,   54,   85,   83,   44,   84,   72,   86,
   62,   16,   18,   24,   29,   54,   54,   54,   54,   41,
   48,   32,   81,   31,   82,   33,   41,   41,   56,   41,
   41,   41,   34,   48,   35,   57,   61,    1,    2,    3,
    4,    5,   50,   51,   52,   41,   41,   41,   41,   54,
   85,   83,   53,   84,   42,   86,   28,    6,   85,   71,
   65,   42,   42,   86,   42,   42,   42,  116,   67,   70,
    1,    2,    3,    4,    5,   91,   92,   56,  115,   41,
   42,   42,   42,   42,   57,   95,   85,   83,  122,   84,
    6,   86,   47,   17,    7,  120,  125,   26,  127,   47,
   47,  129,    3,   47,   81,   25,   82,   23,   35,   15,
   61,   59,   62,   26,   42,   15,   66,   47,   47,   48,
   47,  114,  112,    0,  124,    0,   48,   48,   49,    0,
   48,    0,    0,    0,    0,   49,   49,   19,   20,   49,
    0,   21,    0,   22,   23,   48,    0,   48,    0,    0,
    0,    0,   47,    0,   49,   50,   49,    0,    0,    0,
    0,    0,   50,   50,   51,    0,   50,    0,    0,    0,
    0,   51,   51,    0,    0,   51,    0,    0,    0,   48,
    0,   50,    0,   50,    0,    0,    0,    0,   49,    0,
   51,    0,   51,    0,   46,   33,   37,   38,   35,   39,
    0,   46,   46,   19,   20,   46,    0,   21,    0,   22,
   23,    0,    0,    0,    0,   50,    0,    0,    0,   54,
   46,    0,   46,    0,   51,   54,   54,   54,   54,   54,
   54,   54,   75,   76,   77,   78,   54,   54,   54,    0,
    0,   54,   54,   54,   54,   85,   83,    0,   84,   41,
   86,    0,    0,    0,   46,   41,   41,   41,   41,   41,
   41,   41,    0,   81,  113,   82,   41,   41,   41,    0,
    0,   41,   41,   41,   41,   54,   19,   20,    0,    0,
   21,   55,   22,   23,   42,    0,    0,    0,    0,    0,
   42,   42,   42,   42,   42,   42,   42,    0,    0,    0,
    0,   42,   42,   42,    0,    0,   42,   42,   42,   42,
    0,    0,    0,    0,   75,   76,   77,   78,   79,   80,
    0,    0,   47,    0,   54,   19,   20,    0,   47,   21,
   55,   22,   23,   47,   47,    0,    0,    0,    0,   47,
   47,   47,    0,    0,   47,   47,   47,   47,    0,   48,
    0,    0,    0,    0,    0,   48,    0,    0,   49,    0,
   48,   48,    0,    0,   49,    0,   48,   48,   48,   49,
   49,   48,   48,   48,   48,   49,   49,   49,    0,    0,
   49,   49,   49,   49,    0,   50,    0,    0,    0,    0,
    0,   50,    0,    0,   51,    0,   50,   50,    0,    0,
   51,    0,   50,   50,   50,   51,   51,   50,   50,   50,
   50,   51,   51,   51,    0,    0,   51,   51,   51,   51,
   85,   83,    0,   84,   46,   86,   45,   43,    0,    0,
   46,    0,    0,   45,   45,   46,   46,   45,   81,    0,
   82,   46,   46,   46,    0,    0,   46,   46,   46,   46,
    0,    0,   45,   52,   45,    0,    0,    0,    0,    0,
   52,   52,    0,    0,   52,    0,    0,    0,    0,    0,
    0,  118,    0,   75,   76,   77,   78,   79,   80,   52,
    0,   52,    0,   93,   85,   83,   45,   84,    0,   86,
   94,   85,   83,    0,   84,    0,   86,   99,   85,   83,
    0,   84,   81,   86,   82,    0,  128,   85,   83,   81,
   84,   82,   86,   52,    0,    0,   81,    0,   82,   85,
   83,  119,   84,    0,   86,   81,    0,   82,   85,   83,
    0,   84,    0,   86,    0,   85,   83,   81,   84,   82,
   86,    0,   85,   83,    0,   84,   81,   86,   82,    0,
    0,    0,    0,   81,    0,   82,    0,    0,    0,    0,
   81,    0,   82,    0,    0,   36,    0,    0,   37,   38,
   39,   40,   41,    0,    0,    0,    0,    0,    0,    0,
    0,   59,   60,    0,   42,    0,    0,    0,    0,    0,
    0,   68,   69,    0,    0,    0,    0,   73,   74,    0,
    0,    0,   89,   90,    0,    0,    0,    0,    0,    0,
    0,    0,   96,   97,    0,    0,  100,  101,  102,  103,
  104,  105,  106,  107,  108,  109,  110,  111,    0,    0,
    0,    0,    0,    0,    0,    0,  117,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   75,   76,
   77,   78,   79,   80,  121,    0,   45,    0,    0,    0,
   97,    0,   45,    0,  126,    0,    0,   45,   45,    0,
    0,    0,    0,   45,   45,   45,    0,    0,   45,   45,
   45,   45,    0,   52,    0,    0,    0,    0,    0,   52,
    0,    0,    0,    0,    0,   52,    0,    0,    0,    0,
   52,   52,   52,    0,    0,   52,   52,   52,   52,    0,
    0,    0,   75,   76,   77,   78,   79,   80,    0,   75,
   76,   77,   78,   79,   80,    0,   75,   76,   77,   78,
   79,   80,    0,    0,    0,   75,   76,   77,   78,   79,
   80,    0,    0,    0,    0,    0,    0,   75,   76,   77,
   78,   79,   80,    0,    0,  123,   75,   76,   77,   78,
   79,   80,    0,   75,   76,   77,   78,   79,   80,    0,
   75,   76,   77,   78,   79,
};
static const YYINT yycheck[] = {                         33,
   59,   59,   59,   59,   59,   59,   58,   41,   42,   43,
   44,   45,   17,   47,   42,   43,   33,   45,   40,   47,
   35,  280,   40,   91,  281,   59,   60,   61,   62,   33,
   35,  280,   60,   59,   62,   41,   40,   41,   33,   43,
   44,   45,   44,   48,   93,   40,   61,  256,  257,  258,
  259,  260,   40,   40,   40,   59,   60,   61,   62,   93,
   42,   43,  280,   45,   33,   47,  125,  276,   42,   91,
   59,   40,   41,   47,   43,   44,   45,   94,   59,  280,
  256,  257,  258,  259,  260,  125,   59,   33,  262,   93,
   59,   60,   61,   62,   40,   61,   42,   43,  115,   45,
  276,   47,   33,   14,  280,   41,  263,   18,  125,   40,
   41,  128,    0,   44,   60,   41,   62,   41,   59,   59,
   41,   41,   59,   34,   93,   10,   48,   34,   59,   33,
   61,   92,   88,   -1,  119,   -1,   40,   41,   33,   -1,
   44,   -1,   -1,   -1,   -1,   40,   41,  281,  282,   44,
   -1,  285,   -1,  287,  288,   59,   -1,   61,   -1,   -1,
   -1,   -1,   93,   -1,   59,   33,   61,   -1,   -1,   -1,
   -1,   -1,   40,   41,   33,   -1,   44,   -1,   -1,   -1,
   -1,   40,   41,   -1,   -1,   44,   -1,   -1,   -1,   93,
   -1,   59,   -1,   61,   -1,   -1,   -1,   -1,   93,   -1,
   59,   -1,   61,   -1,   33,  263,  263,  263,  263,  263,
   -1,   40,   41,  281,  282,   44,   -1,  285,   -1,  287,
  288,   -1,   -1,   -1,   -1,   93,   -1,   -1,   -1,  263,
   59,   -1,   61,   -1,   93,  269,  270,  271,  272,  273,
  274,  275,  270,  271,  272,  273,  280,  281,  282,   -1,
   -1,  285,  286,  287,  288,   42,   43,   -1,   45,  263,
   47,   -1,   -1,   -1,   93,  269,  270,  271,  272,  273,
  274,  275,   -1,   60,   61,   62,  280,  281,  282,   -1,
   -1,  285,  286,  287,  288,  280,  281,  282,   -1,   -1,
  285,  286,  287,  288,  263,   -1,   -1,   -1,   -1,   -1,
  269,  270,  271,  272,  273,  274,  275,   -1,   -1,   -1,
   -1,  280,  281,  282,   -1,   -1,  285,  286,  287,  288,
   -1,   -1,   -1,   -1,  270,  271,  272,  273,  274,  275,
   -1,   -1,  263,   -1,  280,  281,  282,   -1,  269,  285,
  286,  287,  288,  274,  275,   -1,   -1,   -1,   -1,  280,
  281,  282,   -1,   -1,  285,  286,  287,  288,   -1,  263,
   -1,   -1,   -1,   -1,   -1,  269,   -1,   -1,  263,   -1,
  274,  275,   -1,   -1,  269,   -1,  280,  281,  282,  274,
  275,  285,  286,  287,  288,  280,  281,  282,   -1,   -1,
  285,  286,  287,  288,   -1,  263,   -1,   -1,   -1,   -1,
   -1,  269,   -1,   -1,  263,   -1,  274,  275,   -1,   -1,
  269,   -1,  280,  281,  282,  274,  275,  285,  286,  287,
  288,  280,  281,  282,   -1,   -1,  285,  286,  287,  288,
   42,   43,   -1,   45,  263,   47,   33,  123,   -1,   -1,
  269,   -1,   -1,   40,   41,  274,  275,   44,   60,   -1,
   62,  280,  281,  282,   -1,   -1,  285,  286,  287,  288,
   -1,   -1,   59,   33,   61,   -1,   -1,   -1,   -1,   -1,
   40,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,
   -1,   93,   -1,  270,  271,  272,  273,  274,  275,   59,
   -1,   61,   -1,   41,   42,   43,   93,   45,   -1,   47,
   41,   42,   43,   -1,   45,   -1,   47,   41,   42,   43,
   -1,   45,   60,   47,   62,   -1,   41,   42,   43,   60,
   45,   62,   47,   93,   -1,   -1,   60,   -1,   62,   42,
   43,   44,   45,   -1,   47,   60,   -1,   62,   42,   43,
   -1,   45,   -1,   47,   -1,   42,   43,   60,   45,   62,
   47,   -1,   42,   43,   -1,   45,   60,   47,   62,   -1,
   -1,   -1,   -1,   60,   -1,   62,   -1,   -1,   -1,   -1,
   60,   -1,   62,   -1,   -1,  261,   -1,   -1,  264,  265,
  266,  267,  268,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   40,   41,   -1,  280,   -1,   -1,   -1,   -1,   -1,
   -1,   50,   51,   -1,   -1,   -1,   -1,   56,   57,   -1,
   -1,   -1,   61,   62,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   71,   72,   -1,   -1,   75,   76,   77,   78,
   79,   80,   81,   82,   83,   84,   85,   86,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   95,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  270,  271,
  272,  273,  274,  275,  113,   -1,  263,   -1,   -1,   -1,
  119,   -1,  269,   -1,  123,   -1,   -1,  274,  275,   -1,
   -1,   -1,   -1,  280,  281,  282,   -1,   -1,  285,  286,
  287,  288,   -1,  263,   -1,   -1,   -1,   -1,   -1,  269,
   -1,   -1,   -1,   -1,   -1,  275,   -1,   -1,   -1,   -1,
  280,  281,  282,   -1,   -1,  285,  286,  287,  288,   -1,
   -1,   -1,  270,  271,  272,  273,  274,  275,   -1,  270,
  271,  272,  273,  274,  275,   -1,  270,  271,  272,  273,
  274,  275,   -1,   -1,   -1,  270,  271,  272,  273,  274,
  275,   -1,   -1,   -1,   -1,   -1,   -1,  270,  271,  272,
  273,  274,  275,   -1,   -1,  269,  270,  271,  272,  273,
  274,  275,   -1,  270,  271,  272,  273,  274,  275,   -1,
  270,  271,  272,  273,  274,
};
#define YYFINAL 8
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#define YYUNDFTOKEN 310
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
"OPERATOR_NE","OPERATOR_AND","OPERATOR_OR","KW_BOOL",0,0,0,"TK_IDENTIFIER",
"LIT_INTEGER","LIT_REAL",0,0,"LIT_CHAR","LIT_STRING","LIT_TRUE","LIT_FALSE",0,
"TOKEN_ERROR",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : inicio",
"inicio : programa",
"programa : declaracao programa",
"programa :",
"declaracao : declara_variavel",
"declaracao : declara_funcao",
"declara_variavel : TK_IDENTIFIER ':' tipo_variavel literal_numerica ';'",
"declara_variavel : TK_IDENTIFIER ':' tipo_variavel '[' indice_vetor ']' inicializacao_vetor ';'",
"indice_vetor : LIT_INTEGER",
"literal_numerica : LIT_INTEGER",
"literal_numerica : LIT_REAL",
"literal_numerica : LIT_CHAR",
"literal_numerica : LIT_TRUE",
"literal_numerica : LIT_FALSE",
"inicializacao_vetor : literal_numerica inicializacao_vetor",
"inicializacao_vetor :",
"tipo_variavel : KW_BYTE",
"tipo_variavel : KW_SHORT",
"tipo_variavel : KW_LONG",
"tipo_variavel : KW_FLOAT",
"tipo_variavel : KW_DOUBLE",
"tipo_variavel : KW_BOOL",
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
"expressao : '(' expressao ')'",
"expressao : expressao '+' expressao",
"expressao : expressao '-' expressao",
"expressao : expressao '*' expressao",
"expressao : expressao '/' expressao",
"expressao : expressao '>' expressao",
"expressao : expressao '<' expressao",
"expressao : expressao OPERATOR_LE expressao",
"expressao : expressao OPERATOR_GE expressao",
"expressao : expressao OPERATOR_EQ expressao",
"expressao : expressao OPERATOR_NE expressao",
"expressao : expressao OPERATOR_AND expressao",
"expressao : expressao OPERATOR_OR expressao",
"expressao : '!' expressao",
"expressao : TK_IDENTIFIER",
"expressao : TK_IDENTIFIER '[' expressao ']'",
"expressao : TK_IDENTIFIER '(' chama_parametros ')'",
"expressao : literal_numerica",
"expressao : LIT_STRING",
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
#line 201 "parser.y"

int yyerror(char* str)
{
	printf("Programa não reconhecido, erro: \"%s\" na linha: %d\n", str, getLineNumber());
	exit(3);
}
#line 476 "y.tab.c"

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
case 1:
#line 89 "parser.y"
	{ast_print_tree(yystack.l_mark[0].astNode); checkProgram(yystack.l_mark[0].astNode); }
break;
case 2:
#line 92 "parser.y"
	{yyval.astNode = ast_insert(AST_PROGRAM, NULL, yystack.l_mark[-1].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 3:
#line 93 "parser.y"
	{yyval.astNode = NULL;}
break;
case 4:
#line 97 "parser.y"
	{yyval.astNode = yystack.l_mark[0].astNode;}
break;
case 5:
#line 98 "parser.y"
	{yyval.astNode = yystack.l_mark[0].astNode;}
break;
case 6:
#line 102 "parser.y"
	{yyval.astNode = ast_insert(AST_VAR_DEC, yystack.l_mark[-4].symbol, yystack.l_mark[-2].astNode, yystack.l_mark[-1].astNode, NULL, NULL);}
break;
case 7:
#line 103 "parser.y"
	{yyval.astNode = ast_insert(AST_VEC_DEC, yystack.l_mark[-7].symbol, yystack.l_mark[-5].astNode, yystack.l_mark[-3].astNode, yystack.l_mark[-1].astNode, NULL);}
break;
case 8:
#line 106 "parser.y"
	{yyval.astNode = ast_insert(AST_LITERAL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 9:
#line 109 "parser.y"
	{yyval.astNode = ast_insert(AST_LITERAL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 10:
#line 110 "parser.y"
	{yyval.astNode = ast_insert(AST_LITERAL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 11:
#line 111 "parser.y"
	{yyval.astNode = ast_insert(AST_LITERAL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 12:
#line 112 "parser.y"
	{yyval.astNode = ast_insert(AST_LITERAL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 13:
#line 113 "parser.y"
	{yyval.astNode = ast_insert(AST_LITERAL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 14:
#line 117 "parser.y"
	{yyval.astNode = ast_insert(AST_VEC_INIT, NULL, yystack.l_mark[-1].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 15:
#line 118 "parser.y"
	{yyval.astNode = NULL;}
break;
case 16:
#line 122 "parser.y"
	{yyval.astNode = ast_insert(AST_BYTE, NULL, NULL, NULL, NULL, NULL);}
break;
case 17:
#line 123 "parser.y"
	{yyval.astNode = ast_insert(AST_SHORT, NULL, NULL, NULL, NULL, NULL);}
break;
case 18:
#line 124 "parser.y"
	{yyval.astNode = ast_insert(AST_LONG, NULL, NULL, NULL, NULL, NULL);}
break;
case 19:
#line 125 "parser.y"
	{yyval.astNode = ast_insert(AST_FLOAT, NULL, NULL, NULL, NULL, NULL);}
break;
case 20:
#line 126 "parser.y"
	{yyval.astNode = ast_insert(AST_DOUBLE, NULL, NULL, NULL, NULL, NULL);}
break;
case 21:
#line 127 "parser.y"
	{yyval.astNode = ast_insert(AST_BOOL, NULL, NULL, NULL, NULL, NULL);}
break;
case 22:
#line 130 "parser.y"
	{yyval.astNode = ast_insert(AST_FUNC_DEC, yystack.l_mark[-5].symbol, yystack.l_mark[-6].astNode, yystack.l_mark[-3].astNode, yystack.l_mark[-1].astNode, NULL);}
break;
case 23:
#line 133 "parser.y"
	{yyval.astNode = yystack.l_mark[0].astNode;}
break;
case 24:
#line 134 "parser.y"
	{yyval.astNode = ast_insert(AST_ARGS_LIST, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 25:
#line 135 "parser.y"
	{yyval.astNode = NULL;}
break;
case 26:
#line 138 "parser.y"
	{yyval.astNode = ast_insert(AST_DEC_ARGS, yystack.l_mark[0].symbol, yystack.l_mark[-1].astNode, NULL, NULL, NULL);}
break;
case 27:
#line 141 "parser.y"
	{yyval.astNode = ast_insert(AST_COMMANDS, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 28:
#line 142 "parser.y"
	{yyval.astNode = NULL;}
break;
case 29:
#line 146 "parser.y"
	{yyval.astNode = yystack.l_mark[0].astNode;}
break;
case 30:
#line 147 "parser.y"
	{yyval.astNode = ast_insert(AST_COMMAND_LIST, NULL, yystack.l_mark[-1].astNode, NULL, NULL, NULL);}
break;
case 31:
#line 148 "parser.y"
	{yyval.astNode = ast_insert(AST_READ, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 32:
#line 149 "parser.y"
	{yyval.astNode = ast_insert(AST_PRINT, NULL, yystack.l_mark[-1].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 33:
#line 150 "parser.y"
	{yyval.astNode = ast_insert(AST_RETURN, NULL, yystack.l_mark[0].astNode, NULL, NULL, NULL);}
break;
case 34:
#line 151 "parser.y"
	{yyval.astNode = yystack.l_mark[0].astNode;}
break;
case 35:
#line 152 "parser.y"
	{yyval.astNode = NULL;}
break;
case 36:
#line 156 "parser.y"
	{yyval.astNode = ast_insert(AST_PRINT_ARGS, NULL, yystack.l_mark[-1].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 37:
#line 157 "parser.y"
	{yyval.astNode = NULL;}
break;
case 38:
#line 161 "parser.y"
	{yyval.astNode = ast_insert(AST_ATRIB, yystack.l_mark[-2].symbol, yystack.l_mark[0].astNode, NULL, NULL, NULL);}
break;
case 39:
#line 162 "parser.y"
	{yyval.astNode = ast_insert(AST_ATRIB_VECTOR, yystack.l_mark[-4].symbol, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 40:
#line 166 "parser.y"
	{yyval.astNode = ast_insert(AST_PARENTHESES, NULL, yystack.l_mark[-1].astNode, NULL, NULL, NULL);}
break;
case 41:
#line 167 "parser.y"
	{yyval.astNode = ast_insert(AST_ADD, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 42:
#line 168 "parser.y"
	{yyval.astNode = ast_insert(AST_SUB, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 43:
#line 169 "parser.y"
	{yyval.astNode = ast_insert(AST_MUL, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 44:
#line 170 "parser.y"
	{yyval.astNode = ast_insert(AST_DIV, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 45:
#line 171 "parser.y"
	{yyval.astNode = ast_insert(AST_GT, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 46:
#line 172 "parser.y"
	{yyval.astNode = ast_insert(AST_LT, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 47:
#line 173 "parser.y"
	{yyval.astNode = ast_insert(AST_LE, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 48:
#line 174 "parser.y"
	{yyval.astNode = ast_insert(AST_GE, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 49:
#line 175 "parser.y"
	{yyval.astNode = ast_insert(AST_EQ, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 50:
#line 176 "parser.y"
	{yyval.astNode = ast_insert(AST_NE, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 51:
#line 177 "parser.y"
	{yyval.astNode = ast_insert(AST_AND, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 52:
#line 178 "parser.y"
	{yyval.astNode = ast_insert(AST_OR, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 53:
#line 179 "parser.y"
	{yyval.astNode = ast_insert(AST_NOT, NULL, yystack.l_mark[0].astNode, NULL, NULL, NULL);}
break;
case 54:
#line 180 "parser.y"
	{yyval.astNode = ast_insert(AST_ID, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 55:
#line 181 "parser.y"
	{yyval.astNode = ast_insert(AST_ID_VECTOR, yystack.l_mark[-3].symbol, yystack.l_mark[-1].astNode, NULL, NULL, NULL);}
break;
case 56:
#line 182 "parser.y"
	{yyval.astNode = ast_insert(AST_ID_CALL, yystack.l_mark[-3].symbol, yystack.l_mark[-1].astNode, NULL, NULL, NULL);}
break;
case 57:
#line 183 "parser.y"
	{yyval.astNode = yystack.l_mark[0].astNode;}
break;
case 58:
#line 184 "parser.y"
	{yyval.astNode = ast_insert(AST_LITERAL, yystack.l_mark[0].symbol, NULL, NULL, NULL, NULL);}
break;
case 59:
#line 188 "parser.y"
	{yyval.astNode = yystack.l_mark[0].astNode;}
break;
case 60:
#line 189 "parser.y"
	{yyval.astNode = ast_insert(AST_PARAM_LIST, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 61:
#line 190 "parser.y"
	{yyval.astNode = NULL;}
break;
case 62:
#line 194 "parser.y"
	{yyval.astNode = ast_insert(AST_WHEN, NULL, yystack.l_mark[-3].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 63:
#line 195 "parser.y"
	{yyval.astNode = ast_insert(AST_WHEN_ELSE, NULL, yystack.l_mark[-5].astNode, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL);}
break;
case 64:
#line 196 "parser.y"
	{yyval.astNode = ast_insert(AST_WHILE, NULL, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL, NULL);}
break;
case 65:
#line 197 "parser.y"
	{yyval.astNode = ast_insert(AST_FOR, yystack.l_mark[-6].symbol, yystack.l_mark[-4].astNode, yystack.l_mark[-2].astNode, yystack.l_mark[0].astNode, NULL);}
break;
#line 938 "y.tab.c"
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
