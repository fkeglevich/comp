#
# UFRGS - Compiladores B - Marcelo Johann - 2017/1 - Etapa 7
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa7: y.tab.c lex.yy.c
	gcc -o etapa7 lex.yy.c ast.c hash.c y.tab.c semantic.c tac.c asm.c
	
lex.yy.c: scanner.l
	lex -d scanner.l
	
y.tab.c: parser.y
	yacc -d parser.y

tgz: clean
	tar cvzf etapa7.tgz .

clean:
	rm -rf *o lex.yy.* y.tab.* etapa7 etapa7.tgz saidaAsm SAIDA_ASM.S

