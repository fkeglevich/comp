/*
Etapa 4 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include <stdlib.h>
#include <string.h>

#include "ast.h"

int getLineNumber(void);

AST_NODE* ast_insert(int type, HASH_NODE *symbol, AST_NODE* c0, AST_NODE* c1, AST_NODE* c2, AST_NODE* c3)
{
	AST_NODE *astNode;
	int i;
	
	astNode = calloc(1, sizeof(AST_NODE));
    	astNode->type = type;
	astNode->symbol = symbol;

	astNode->children[0] = c0;
	astNode->children[1] = c1;
	astNode->children[2] = c2;
	astNode->children[3] = c3;

	astNode->lineNumber = getLineNumber();

    	return astNode;
}

void print_op_node(AST_NODE *node, char* op_str)
{
	ast_print(node->children[0]);
	fprintf(OUT_FILE, "%s", op_str);
	ast_print(node->children[1]);
}

void print_str(char* str)
{
	fprintf(OUT_FILE, "%s", str);
}

void ast_print_tree(AST_NODE *root)
{
	ast_print(root);
}

void ast_print(AST_NODE *node)
{
	int i;
	
	if (node == NULL) return;

	switch(node->type)
	{
		case AST_PARENTHESES: print_str("("); ast_print(node->children[0]); print_str(")"); break;

		case AST_ADD:
		case AST_SUB:
		case AST_MUL:
		case AST_DIV:
		case AST_GT:
		case AST_LT:
			ast_print(node->children[0]);
			fprintf(OUT_FILE, "%c ", node->type);
			ast_print(node->children[1]);
			break;
		
		case AST_LE:		print_op_node(node, "<= "); break;
		case AST_GE:		print_op_node(node, ">= "); break;
		case AST_EQ:		print_op_node(node, "== "); break;
		case AST_NE:		print_op_node(node, "!= "); break;
		case AST_AND:	print_op_node(node, "&& "); break;
		case AST_OR:		print_op_node(node, "|| "); break;
		
		case AST_NOT: 	print_str("! "); ast_print(node->children[0]); break;
		
		case AST_LITERAL:
		case AST_ID:		
			fprintf(OUT_FILE, "%s ", node->symbol->text); break;

		case AST_ID_VECTOR: 
			fprintf(OUT_FILE, "%s", node->symbol->text);
			print_str("["); ast_print(node->children[0]); print_str("]");
			break;

		case AST_ID_CALL: 
			fprintf(OUT_FILE, "%s", node->symbol->text);
			print_str("("); ast_print(node->children[0]); print_str(")");
			break;

		case AST_PARAM_LIST: 
			ast_print(node->children[0]); print_str(", "); ast_print(node->children[1]);
			break;
		
		case AST_WHEN: 
		case AST_WHEN_ELSE: 
			print_str("when ( "); ast_print(node->children[0]);
			print_str(") then "); ast_print(node->children[1]);
			if (node->children[2] != NULL) {
				print_str("else "); ast_print(node->children[2]); 
			}
			break;

		case AST_WHILE:
			print_str("while ( "); ast_print(node->children[0]);
			print_str(") "); ast_print(node->children[1]);
			break;

		case AST_FOR:
			print_str("for ( "); fprintf(OUT_FILE, "%s ", node->symbol->text); 
			print_str("= "); ast_print(node->children[0]);
			print_str("to "); ast_print(node->children[1]);
			print_str(") "); ast_print(node->children[2]);
			break;

		case AST_ATRIB:
			fprintf(OUT_FILE, "%s ", node->symbol->text); 
			print_str("= "); ast_print(node->children[0]);
			break;

		case AST_ATRIB_VECTOR:
			fprintf(OUT_FILE, "%s ", node->symbol->text); 
			print_str("# "); ast_print(node->children[0]);
			print_str("= "); ast_print(node->children[1]);
			break;
		
		case AST_VEC_INIT:
		case AST_PROGRAM:
		case AST_PRINT_ARGS:
			ast_print(node->children[0]);
			ast_print(node->children[1]);
			break;

		case AST_VAR_DEC:
			fprintf(OUT_FILE, "%s ", node->symbol->text); 
			print_str(": "); ast_print(node->children[0]);
			print_str(" "); ast_print(node->children[1]);
			print_str(";\n");
			break;

		case AST_VEC_DEC:
			fprintf(OUT_FILE, "%s ", node->symbol->text); 
			print_str(": "); ast_print(node->children[0]);
			print_str("[ "); ast_print(node->children[1]);
			print_str("] "); ast_print(node->children[2]);
			print_str(";\n");
			break;

		case AST_FUNC_DEC:
			ast_print(node->children[0]); print_str(" "); 
			fprintf(OUT_FILE, "%s ", node->symbol->text); 
			print_str("( "); ast_print(node->children[1]);
			print_str(") "); ast_print(node->children[2]);
			print_str(";\n");
			break;

		case AST_BYTE:		print_str("byte ");		break;
		case AST_SHORT:		print_str("short ");		break;
		case AST_LONG:		print_str("long ");		break;
		case AST_FLOAT:		print_str("float ");		break;
		case AST_DOUBLE:	print_str("double ");	break;
		case AST_BOOL:		print_str("bool ");	break;
		
		case AST_ARGS_LIST:
			ast_print(node->children[0]);
			print_str(", "); 
			ast_print(node->children[1]);
			break;

		case AST_DEC_ARGS:
			ast_print(node->children[0]);
			print_str(" "); 
			fprintf(OUT_FILE, "%s ", node->symbol->text); 
			break;

		case AST_COMMAND_LIST:
			print_str("{\n"); 
			ast_print(node->children[0]);
			print_str("}"); 
			break;

		case AST_READ:
			print_str("read "); 
			fprintf(OUT_FILE, "%s ", node->symbol->text); 
			break;

		case AST_PRINT:
			print_str("print "); ast_print(node->children[0]);
			print_str(" "); ast_print(node->children[1]);
			break;

		case AST_RETURN: print_str("return "); ast_print(node->children[0]); break;

		case AST_COMMANDS:
			ast_print(node->children[0]);
			print_str(";\n"); 
			ast_print(node->children[1]);
			break;
	}
}