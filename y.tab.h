
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SYMBOL_UNDEFINED = 0,
     KW_INTEGER = 256,
     KW_FLOATING = 257,
     KW_BOOLEAN = 258,
     KW_CHARACTER = 259,
     KW_DECLARE = 260,
     KW_IF = 261,
     KW_THEN = 262,
     KW_ELSE = 263,
     KW_WHILE = 264,
     KW_DO = 265,
     KW_INPUT = 266,
     KW_RETURN = 267,
     KW_OUTPUT = 268,
     OPERATOR_LE = 270,
     OPERATOR_GE = 271,
     OPERATOR_EQ = 272,
     OPERATOR_NE = 273,
     OPERATOR_AND = 274,
     OPERATOR_OR = 275,
     SYMBOL_LIT_INTEGER = 1,
     SYMBOL_LIT_FLOATING = 2,
     SYMBOL_LIT_TRUE = 3,
     SYMBOL_LIT_FALSE = 4,
     SYMBOL_LIT_CHAR = 5,
     SYMBOL_LIT_STRING = 6,
     SYMBOL_IDENTIFIER = 7,
     TOKEN_ERROR = 290
   };
#endif
/* Tokens.  */
#define SYMBOL_UNDEFINED 0
#define KW_INTEGER 256
#define KW_FLOATING 257
#define KW_BOOLEAN 258
#define KW_CHARACTER 259
#define KW_DECLARE 260
#define KW_IF 261
#define KW_THEN 262
#define KW_ELSE 263
#define KW_WHILE 264
#define KW_DO 265
#define KW_INPUT 266
#define KW_RETURN 267
#define KW_OUTPUT 268
#define OPERATOR_LE 270
#define OPERATOR_GE 271
#define OPERATOR_EQ 272
#define OPERATOR_NE 273
#define OPERATOR_AND 274
#define OPERATOR_OR 275
#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_FLOATING 2
#define SYMBOL_LIT_TRUE 3
#define SYMBOL_LIT_FALSE 4
#define SYMBOL_LIT_CHAR 5
#define SYMBOL_LIT_STRING 6
#define SYMBOL_IDENTIFIER 7
#define TOKEN_ERROR 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 9 "parser.y"

  HASH_NODE* symbol;
  


/* Line 1676 of yacc.c  */
#line 118 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


