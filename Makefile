#
# UFRGS - Compiladores B - Marcelo Johann - 2017/1 - Etapa 5
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa5: y.tab.c lex.yy.c
	gcc -o etapa5 lex.yy.c ast.c hash.c y.tab.c semantic.c tac.c
	
lex.yy.c: scanner.l
	lex -d scanner.l
	
y.tab.c: parser.y
	yacc -d parser.y

tgz: clean
	tar cvzf etapa5.tgz .

clean:
	rm -rf *o lex.yy.* y.tab.* etapa5 etapa5.tgz

