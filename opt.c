/*
Etapa 7 do trabalho de Compiladores (2017/1)

Professor: Marcelo Johann

Grupo:
	Delton Vaz (00229779) (nick: ~davaz)
	Flávio Keglevich (00229724)
*/

#include "opt.h"

AST_NODE* searchFuncCallChild(AST_NODE *node, int childNum);
AST_NODE* searchFuncCall(AST_NODE *node);
AST_NODE* searchFuncDecAndVerify(AST_NODE *root, HASH_NODE *funcSymbol, AST_NODE **returnNode);

AST_NODE* searchFuncCallChild(AST_NODE *node, int childNum)
{
	if (node == NULL || (childNum >= NUM_CHILDREN))
		return NULL;

	AST_NODE* child = searchFuncCall(node->children[childNum]);
	if (child != NULL)
		return child;
	else
		return searchFuncCallChild(node, childNum + 1);
}

AST_NODE* searchFuncCall(AST_NODE *node)
{
	if (node == NULL)
		return NULL;
	
	if (node->type == AST_ID_CALL)
		return node;

	return searchFuncCallChild(node, 0);
}

void print_str2(char* str)
{
	fprintf(OUT_FILE, "%s", str);
}

AST_NODE* cloneAstNode(AST_NODE* node)
{
	return ast_insert(node->type, node->symbol,	node->children[0], 
							node->children[1], 
							node->children[2],
							node->children[3]);
}

void passCopy(AST_NODE* A, AST_NODE* B)
{
	A->type = B->type;
	A->symbol = B->symbol;
	A->children[0] = B->children[0];
	A->children[1] = B->children[1];
	A->children[2] = B->children[2];
	A->children[3] = B->children[3];
}

AST_NODE* deepCloneFunc(AST_NODE* node)
{
	if ((node == NULL) || (node->type == AST_RETURN))
		return NULL;

	return ast_insert(node->type, node->symbol,	deepCloneFunc(node->children[0]), 
							deepCloneFunc(node->children[1]), 
							deepCloneFunc(node->children[2]),
							deepCloneFunc(node->children[3]));
}

void transformIntoCommandList(AST_NODE *node)
{
	node->type = AST_COMMAND_LIST;
	node->symbol = NULL;
	node->children[0] = NULL;
	node->children[1] = NULL;
	node->children[2] = NULL;
	node->children[3] = NULL;
}

//chid3
int hasFuncCallInsice(AST_NODE *node)
{
	return searchFuncCall(node) != NULL;
}

int getReturnCount(AST_NODE *node)
{
	if (node == NULL)
		return 0;

	if (node->type == AST_RETURN)
		return 1;

	return	getReturnCount(node->children[0]) + 
		getReturnCount(node->children[1]) + 
		getReturnCount(node->children[2]) + 
		getReturnCount(node->children[3]);
}

AST_NODE* isLastCommandAReturn(AST_NODE *node)
{
	if (node == NULL)
		return NULL;

	if (node->type == AST_FUNC_DEC)
	{
		if (node->children[2] != NULL)
		{
			if (node->children[2]->type == AST_RETURN)
				return node->children[2];
			else if (node->children[2]->type == AST_COMMAND_LIST)
				return isLastCommandAReturn(node->children[2]->children[0]);
		}
	}

	if (node->type == AST_COMMANDS)
	{
		if (node->children[0] != NULL)
		{
			if (node->children[0]->type == AST_RETURN)
			{
				if (node->children[1] == NULL)
					return node->children[0];
			}
			else
			{
				return isLastCommandAReturn(node->children[1]);
			}
		}
	}
	
	return NULL;
}

AST_NODE* searchFuncDecAndVerify(AST_NODE *root, HASH_NODE *funcSymbol, AST_NODE **returnNode)
{
	if (root == NULL)
		return NULL;

	if ((root->type == AST_FUNC_DEC) && (root->symbol == funcSymbol))
	{
		if (!hasFuncCallInsice(root))
		{	
			if ((getReturnCount(root) == 1))
			{
				AST_NODE* lastReturn = isLastCommandAReturn(root);
				if (lastReturn != NULL)
				{
					(*returnNode) = lastReturn;
					return root;
				}
			}
		}
		return NULL;
	}
	
	AST_NODE* child0 = searchFuncDecAndVerify(root->children[0], funcSymbol, returnNode);
	if (child0 != NULL)
		return child0;
	else
	{
		AST_NODE* child1 = searchFuncDecAndVerify(root->children[1], funcSymbol, returnNode);
		if (child1 != NULL)
			return child1;
		else
			return NULL;
	}
}

void searchLeafCommand(AST_NODE *node, AST_NODE *root, int* success)
{
	AST_NODE* funcCall;
	AST_NODE* funcDec;
	AST_NODE* clonedFuncBody;
	AST_NODE* funcArg;
	AST_NODE* funcReturn = NULL;
	AST_NODE* leafCommandClone;
	AST_NODE* astCommandNode;	

	if (node == NULL)
		return;
	
	switch (node->type)
	{
		case AST_PRINT:
		case AST_RETURN:
		case AST_ATRIB:
		case AST_ATRIB_VECTOR:
		case AST_WHEN:
		case AST_WHEN_ELSE:
		case AST_WHILE:
		case AST_FOR:
			//fprintf(stderr, "ACHOU CHAMADA DE FUNC! \n");
			funcCall = searchFuncCall(node);		
			if (funcCall != NULL)
			{
				funcDec = searchFuncDecAndVerify(root, funcCall->symbol, &funcReturn);
				if ((funcDec != NULL) && (funcDec->children[1] == NULL))
				{
					/*print_str2("//             Leaf command: \n");
					ast_print(node);
					print_str2("\n");
					print_str2("//             Func call: \n");
					ast_print(funcCall);
					print_str2("\n");
					print_str2("//             Func dec: \n");
					ast_print(funcDec);
					print_str2("\n");
					print_str2("\n");*/

					leafCommandClone = cloneAstNode(node);
					transformIntoCommandList(node);
					//astCommandNode = ast_insert(AST_COMMANDS, NULL, funcDec->children[2], NULL, NULL, NULL);
					
					clonedFuncBody = deepCloneFunc(funcDec->children[2]);
					//funcReturn = 
					
					//funcCall->type = 

					astCommandNode = ast_insert(AST_COMMANDS, NULL, leafCommandClone, NULL, NULL, NULL);
					astCommandNode = ast_insert(AST_COMMANDS, NULL, clonedFuncBody, astCommandNode, NULL, NULL);
					
					node->children[0] = astCommandNode;				
					
					passCopy(funcCall, ast_insert(AST_PARENTHESES, NULL, funcReturn->children[0], NULL, NULL, NULL));
					(*success) = 1;
					//fprintf(stderr, "is last return?: %d\n", isLastCommandAReturn(funcDec) != NULL);
				}
				
			}
			break;

		default:
			searchLeafCommand(node->children[0], root, success);
			searchLeafCommand(node->children[1], root, success);
			searchLeafCommand(node->children[2], root, success);
			searchLeafCommand(node->children[3], root, success);
			break;
	}
}

void optimizeInline(AST_NODE *root)
{
	/*if (node == NULL)
		return;

	if (node->type == 	)
	{
		fprintf(stderr, "ACHOU CHAMADA DE FUNC! \n");
		return;
	}
	else
	{
		optimizeInline(node->children[0]);
		optimizeInline(node->children[1]);
		optimizeInline(node->children[2]);
		optimizeInline(node->children[3]);
	}*/
	int success = 0;
	do
	{
		success = 0;
		searchLeafCommand(root, root, &success);
	}
	while (success);
}

void optimizeAst(AST_NODE *root)
{
	//fprintf(stderr, "EDDIIE \n");
	optimizeInline(root);
}