#
# UFRGS - Compiladores B - Marcelo Johann - 2017/1 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa2: y.tab.c lex.yy.c
	gcc -o etapa2 lex.yy.c hash.c y.tab.c #main.c chamada em scanner.l
	
lex.yy.c: scanner.l
	lex scanner.l
	
y.tab.c: parser.y
	yacc -d parser.y
	
tgz: clean
	tar cvzf etapa2.tgz .

clean:
	rm -rf *o lex.yy.* y.tab.* etapa2 etapa2.tgz
