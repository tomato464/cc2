#ifndef _PARSE_H_
#define _PARSE_H_
#include"tokenize.h" 

typedef enum{
	ND_SUB,
	ND_ADD,
	ND_MUL,
	ND_DIV,
	ND_NUM,
}NodeType;

typedef struct Node{
	NodeType type;
	struct Node *r_child;
	struct Node *l_child;
	int num;
	char *str;
}Node;

Node *ConstructTree(Token *token, char *p);

#endif
