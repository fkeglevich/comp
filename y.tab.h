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
extern YYSTYPE yylval;
