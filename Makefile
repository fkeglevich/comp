#
# UFRGS - Compiladores B - Marcelo Johann - 2017/1 - Etapa 4
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa4: y.tab.c lex.yy.c
	gcc -o etapa4 lex.yy.c ast.c hash.c y.tab.c semantic.c #main.c chamada em scanner.l
	
lex.yy.c: scanner.l
	lex -d scanner.l
	
y.tab.c: parser.y
	yacc -d parser.y

tgz: clean
	tar cvzf etapa4.tgz .

clean:
	rm -rf *o lex.yy.* y.tab.* etapa4 etapa4.tgz

