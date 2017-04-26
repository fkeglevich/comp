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
    8,   14,   14,   12,   12,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,
};
static const YYINT yylen[] = {                            2,
    2,    0,    1,    1,    5,    8,    1,    1,    1,    1,
    2,    0,    1,    1,    1,    1,    1,    6,    1,    2,
    0,    2,    3,    2,    0,    1,    1,    2,    3,    2,
    0,    2,    0,    3,    5,    3,    3,    3,    3,    2,
    2,    3,    3,    3,    3,    3,    3,    3,    3,    1,
    4,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
   13,   14,   15,   16,   17,    0,    0,    0,    3,    4,
    0,    0,    1,    0,    0,    0,    7,    8,    9,    0,
    0,    0,    0,    0,    0,    5,   22,    0,   20,    0,
    0,    0,    0,    0,    0,   18,   27,   26,    0,    0,
   28,    0,   52,   53,   54,   56,    0,    0,    0,    0,
    0,    0,    0,    0,   11,    6,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   29,    0,    0,   24,   23,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   32,    0,   51,    0,
};
static const YYINT yydgoto[] = {                          7,
    8,    9,   10,   11,   39,   40,   23,   36,   24,   37,
   54,   38,   73,   74,
};
static const YYINT yysindex[] = {                      -233,
    0,    0,    0,    0,    0,  -45,    0, -233,    0,    0,
 -259, -207,    0,  -12,  -88, -207,    0,    0,    0, -245,
  -21, -241,   13,   -3,  -51,    0,    0, -115,    0, -276,
 -225,  187,  187,  -28, -115,    0,    0,    0, -276,   -2,
    0,  -35,    0,    0,    0,    0,  187,  187,  -25,  483,
  187,  187,   -1,  -66,    0,    0, -217,  471,  -25,  187,
  187,  187,  187,  187,  187,  187,  187,  187,  187,  187,
  187,  187,  483,    0,  -25,  -31,    0,    0,  -27,  -25,
  -25,  -25,  -25,  -60,  334,  471,  471,  115,  115,  -25,
  -25,  471,    0,  187,    0,  -25,
};
static const YYINT yyrindex[] = {                        67,
    0,    0,    0,    0,    0,    0,    0,   67,    0,    0,
    0,    0,    0,    0,    0,   27,    0,    0,    0,    0,
    0,    0,    0,   31,    0,    0,    0,   45,    0,   17,
    0,    0,    0,    0,  -55,    0,    0,    0,   21,    0,
    0,    1,    0,    0,    0,    0,    0,    0,  252,   10,
    0,    0,    0,    0,    0,    0,    0,   86,  163,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   10,    0,  264,    0,    0,    0,    0,  170,
  204,  218,  332,   32,   40,  117,  124,   71,   78,  432,
  446,  155,    0,    0,    0,  280,
};
static const YYINT yygindex[] = {                        73,
    0,    0,    0,    3,   69,   49,    0,   54,    0,    0,
    0,    0,  502,   19,
};
#define YYTABLESIZE 769
static const YYINT yytable[] = {                         71,
   50,   70,   20,   31,   17,   18,   52,   35,   19,   33,
   68,   66,   12,   67,   15,   69,   68,   66,   22,   67,
   14,   69,    1,    2,    3,    4,    5,   16,   71,   94,
   70,   48,   51,   50,   71,   25,   70,   26,   27,   49,
   29,   30,   50,   50,   31,   50,    6,   50,    1,    2,
    3,    4,    5,   28,   41,   57,   56,   77,   78,   50,
   50,   50,   50,   79,   48,   95,    2,   21,   33,   25,
   38,   19,   49,   48,   48,   12,   48,   39,   48,   10,
   13,   49,   49,   21,   49,   40,   49,   55,   53,    0,
   48,   93,   48,    0,    0,    0,    0,    0,   49,    0,
   49,    0,    0,   38,    0,    0,    0,    0,    0,    0,
   39,    0,   38,   38,    0,   38,   36,   38,   40,   39,
   39,    0,   39,   37,   39,    0,    0,    0,   40,   38,
   40,   38,    0,    0,    0,    0,   39,    0,   39,    0,
    0,    0,    0,    0,   40,    0,   40,    0,    0,   36,
   31,   32,   33,    0,   37,    0,   37,    0,    0,   36,
    0,   36,   41,    0,   34,    0,   37,    0,   37,   44,
    0,    0,    0,    0,   71,   36,   70,   36,    0,    0,
    0,    0,   37,    0,   37,    0,    0,   37,    0,    0,
    0,    0,   17,   18,    0,   41,   19,   37,    0,   37,
    0,    0,   44,   45,    0,    0,    0,    0,    0,   60,
   61,   62,   63,   37,    0,    0,    0,   46,    0,   48,
    0,   41,    0,   41,    0,    0,    0,    0,   44,    0,
   44,   47,    0,    0,    0,    0,   45,    0,   60,   61,
   62,   63,   64,   65,   60,   61,   62,   63,   64,   65,
   46,   30,    0,    0,    0,    0,   50,   50,   50,   50,
   50,    0,   45,   34,   45,   33,   33,   33,   33,   33,
   50,   50,   50,   50,   50,   50,   46,    0,   46,   35,
   50,   50,   50,    0,    0,   50,   50,   48,   48,   48,
   48,   48,    0,    0,    0,   49,   49,   49,   49,   49,
   31,   31,   31,   31,   31,   48,   48,    0,    0,    0,
   30,   48,   48,   48,   49,    0,   48,   48,    0,   49,
   49,   49,   34,    0,   49,   49,   38,   38,   38,   38,
   38,   47,    0,   39,   39,   39,   39,   39,   35,    0,
    0,   40,   40,   40,   40,   40,    0,    0,    0,    0,
   38,   38,   38,    0,    0,   38,   38,   39,   39,   39,
    0,    0,   39,   39,   47,   40,   40,   40,    0,    0,
   40,   40,   36,   36,   36,   36,   36,    0,    0,   37,
   37,   37,   37,   37,   60,   61,   62,   63,   64,   65,
   47,    0,   47,   71,    0,   70,   36,   36,   36,    0,
    0,   36,   36,   37,   37,   37,    0,    0,   37,   37,
   37,   37,   37,   37,   37,    0,    0,    0,   41,   41,
   41,   41,   41,    0,    0,   44,   44,   44,   44,   44,
    0,   42,    0,    0,   37,   37,   37,    0,    0,   37,
   37,    0,   41,   41,   41,   43,    0,   41,   41,   44,
   44,   44,    0,    0,   44,   44,    0,    0,    0,   45,
   45,   45,   45,   45,   42,    0,   42,   43,   44,    0,
    0,   45,   46,   46,   46,   46,   46,   46,   43,    0,
    0,    0,    0,   45,   45,   45,    0,    0,   45,   45,
   42,    0,   42,    0,    0,    0,    0,   46,   46,   46,
    0,    0,   46,   46,   43,    0,   43,   30,   30,   30,
   30,   30,   68,    0,    0,   48,    0,   69,    0,   34,
   34,   34,   34,   34,   68,   66,    0,   72,    0,   69,
   71,   30,   70,   49,   50,   35,   35,   35,   35,   35,
    0,    0,   71,   34,   70,    0,    0,    0,   58,   59,
    0,    0,   75,   76,    0,    0,    0,    0,    0,   35,
    0,   80,   81,   82,   83,   84,   85,   86,   87,   88,
   89,   90,   91,   92,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   47,   47,   47,
   47,   47,    0,    0,    0,   96,    0,    0,    0,    0,
    0,    0,    0,   60,   61,   62,   63,   64,    0,    0,
    0,   47,   47,   47,    0,    0,   47,   47,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   42,   42,   42,
   42,   42,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   43,   43,   43,   43,   43,    0,    0,    0,    0,
    0,   42,   42,   42,    0,    0,   42,   42,    0,    0,
    0,    0,    0,    0,    0,   43,   43,   43,    0,    0,
   43,   43,    0,    0,    0,    0,    0,    0,    0,    0,
   60,   61,   62,   63,   64,   65,    0,    0,    0,    0,
    0,    0,   60,   61,   62,   63,   64,   65,    0,    0,
    0,    0,   42,   43,   44,    0,    0,   45,   46,
};
static const YYINT yycheck[] = {                         60,
    0,   62,   91,   59,  281,  282,   35,  123,  285,    0,
   42,   43,   58,   45,   12,   47,   42,   43,   16,   45,
  280,   47,  256,  257,  258,  259,  260,   40,   60,   61,
   62,    0,   61,   33,   60,  281,   62,   59,  280,    0,
   44,   93,   42,   43,    0,   45,  280,   47,  256,  257,
  258,  259,  260,   41,  280,   91,   59,   59,  125,   59,
   60,   61,   62,  281,   33,   93,    0,   41,   59,  125,
    0,   41,   33,   42,   43,   59,   45,    0,   47,   59,
    8,   42,   43,   15,   45,    0,   47,   39,   35,   -1,
   59,   73,   61,   -1,   -1,   -1,   -1,   -1,   59,   -1,
   61,   -1,   -1,   33,   -1,   -1,   -1,   -1,   -1,   -1,
   33,   -1,   42,   43,   -1,   45,    0,   47,   33,   42,
   43,   -1,   45,    0,   47,   -1,   -1,   -1,   43,   59,
   45,   61,   -1,   -1,   -1,   -1,   59,   -1,   61,   -1,
   -1,   -1,   -1,   -1,   59,   -1,   61,   -1,   -1,   33,
  266,  267,  268,   -1,    0,   -1,   33,   -1,   -1,   43,
   -1,   45,    0,   -1,  280,   -1,   43,   -1,   45,    0,
   -1,   -1,   -1,   -1,   60,   59,   62,   61,   -1,   -1,
   -1,   -1,   59,   -1,   61,   -1,   -1,   33,   -1,   -1,
   -1,   -1,  281,  282,   -1,   33,  285,   43,   -1,   45,
   -1,   -1,   33,    0,   -1,   -1,   -1,   -1,   -1,  270,
  271,  272,  273,   59,   -1,   -1,   -1,    0,   -1,   33,
   -1,   59,   -1,   61,   -1,   -1,   -1,   -1,   59,   -1,
   61,   45,   -1,   -1,   -1,   -1,   33,   -1,  270,  271,
  272,  273,  274,  275,  270,  271,  272,  273,  274,  275,
   33,    0,   -1,   -1,   -1,   -1,  256,  257,  258,  259,
  260,   -1,   59,    0,   61,  256,  257,  258,  259,  260,
  270,  271,  272,  273,  274,  275,   59,   -1,   61,    0,
  280,  281,  282,   -1,   -1,  285,  286,  256,  257,  258,
  259,  260,   -1,   -1,   -1,  256,  257,  258,  259,  260,
  256,  257,  258,  259,  260,  274,  275,   -1,   -1,   -1,
   59,  280,  281,  282,  275,   -1,  285,  286,   -1,  280,
  281,  282,   59,   -1,  285,  286,  256,  257,  258,  259,
  260,    0,   -1,  256,  257,  258,  259,  260,   59,   -1,
   -1,  256,  257,  258,  259,  260,   -1,   -1,   -1,   -1,
  280,  281,  282,   -1,   -1,  285,  286,  280,  281,  282,
   -1,   -1,  285,  286,   33,  280,  281,  282,   -1,   -1,
  285,  286,  256,  257,  258,  259,  260,   -1,   -1,  256,
  257,  258,  259,  260,  270,  271,  272,  273,  274,  275,
   59,   -1,   61,   60,   -1,   62,  280,  281,  282,   -1,
   -1,  285,  286,  280,  281,  282,   -1,   -1,  285,  286,
  256,  257,  258,  259,  260,   -1,   -1,   -1,  256,  257,
  258,  259,  260,   -1,   -1,  256,  257,  258,  259,  260,
   -1,    0,   -1,   -1,  280,  281,  282,   -1,   -1,  285,
  286,   -1,  280,  281,  282,    0,   -1,  285,  286,  280,
  281,  282,   -1,   -1,  285,  286,   -1,   -1,   -1,  256,
  257,  258,  259,  260,   33,   -1,  280,  281,  282,   -1,
   -1,  285,  286,  256,  257,  258,  259,  260,   33,   -1,
   -1,   -1,   -1,  280,  281,  282,   -1,   -1,  285,  286,
   59,   -1,   61,   -1,   -1,   -1,   -1,  280,  281,  282,
   -1,   -1,  285,  286,   59,   -1,   61,  256,  257,  258,
  259,  260,   42,   -1,   -1,   33,   -1,   47,   -1,  256,
  257,  258,  259,  260,   42,   43,   -1,   45,   -1,   47,
   60,  280,   62,   32,   33,  256,  257,  258,  259,  260,
   -1,   -1,   60,  280,   62,   -1,   -1,   -1,   47,   48,
   -1,   -1,   51,   52,   -1,   -1,   -1,   -1,   -1,  280,
   -1,   60,   61,   62,   63,   64,   65,   66,   67,   68,
   69,   70,   71,   72,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  256,  257,  258,
  259,  260,   -1,   -1,   -1,   94,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  270,  271,  272,  273,  274,   -1,   -1,
   -1,  280,  281,  282,   -1,   -1,  285,  286,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  256,  257,  258,
  259,  260,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  256,  257,  258,  259,  260,   -1,   -1,   -1,   -1,
   -1,  280,  281,  282,   -1,   -1,  285,  286,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  280,  281,  282,   -1,   -1,
  285,  286,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  270,  271,  272,  273,  274,  275,   -1,   -1,   -1,   -1,
   -1,   -1,  270,  271,  272,  273,  274,  275,   -1,   -1,
   -1,   -1,  280,  281,  282,   -1,   -1,  285,  286,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#define YYUNDFTOKEN 307
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
0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
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
"expressao : expressao '+' expressao",
"expressao : expressao '-' expressao",
"expressao : expressao '*' expressao",
"expressao : expressao '/' expressao",
"expressao : '-' expressao",
"expressao : '!' expressao",
"expressao : expressao '>' expressao",
"expressao : expressao '<' expressao",
"expressao : expressao OPERATOR_LE expressao",
"expressao : expressao OPERATOR_GE expressao",
"expressao : expressao OPERATOR_EQ expressao",
"expressao : expressao OPERATOR_NE expressao",
"expressao : expressao OPERATOR_AND expressao",
"expressao : expressao OPERATOR_OR expressao",
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
#line 165 "parser.y"

int yyerror(char* str)
{
	printf("ERRO: \"%s\" na linha: %d\n", str, getLineNumber());
	exit(3);
}
#line 447 "y.tab.c"

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
