#include"parse.h"
#include"tokenize.h"
#include"defines.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
Token *token_cur = NULL;
char *code;
// Expr = Mul (+ Mul|- Mul )*
// Mul = Pri (* Pri | / Pri)*
// Pri = num | ( Expr )

static Node *CreateNode(NodeType type)
{
	Node *node = (Node *)malloc(sizeof(Node));
	memset(node, 0, sizeof(Node));
	node->type = type;
	return node;
}

static Node *CreateNumNode(int num)
{
	Node *node = CreateNode(ND_NUM);
	node->num = num;
	node->str = token_cur->str;
	return node;
}

void PrintCompileError(char *str ,Token *token)
{
	char *p = str;
	int line = 0;
	int row = 0;
	char buf[256];
	//cpunt number of line
	while(p != token->str){
		if(*p == '\n'){
			line++;
		}
		p++;
	}
	p = str;
	for(int i = 0; i < line - 1; ){
		if(*p == '\n'){
			i++;
		}
		p++;
	}

	for(int i = 0; i < 256; i++){
		if(p[i] == '\n' || p[i] == EOF){
			break;
		}
		buf[i] =p[i];
	}
	row = token->str - str;

	fprintf(stderr, "%d : %s\n", line, buf);
	fprintf(stderr, "%d : ", line);
	for(int i = 0; i < row;i++){
		fprintf(stderr, " ");
	}
	fprintf(stderr, "^\n");
}

static int ExpectNum()
{
	if(token_cur->type == TK_NUM){
		int ret = token_cur->num;
		token_cur = token_cur->next;
		return ret;		
	}else{
		PrintCompileError(code, token_cur);
		exit(1);
	}
}

static bool Expect(char *reserved, int len)
{
	if(!strncmp(token_cur->str, reserved, len)){
		token_cur = token_cur->next;
		return true;
	}else{
		PrintCompileError(code, token_cur);
		exit(1);
	}
}

static bool Consume(char *p, int len)
{
	if(token_cur->type != TK_RESERVED){
		return false;
	}

	if(!strncmp(token_cur->str, p, len)){
		token_cur = token_cur->next;
		return true;
	}
	return false;
}

static Node *InsertNode(NodeType type, Node* l_child, Node *r_child)
{
	Node *node = CreateNode(type); 
	node->l_child = l_child;
	node->r_child = r_child;
	return node;
}

static Node *Expr();
static Node *Mul();
static Node *Primary();

// Expr = Mul (+ Mul | - Mul)*
static Node *Expr()
{
	Node *node = Mul();

	for(;;){
		if(Consume("+", 1)){
			node = InsertNode(ND_ADD, node, Mul());
		}else if(Consume("-", 1)){
			node = InsertNode(ND_SUB, node, Mul());
		}else{
			return node;
		}
	}
}

// Mul = Pri (* Pri | / Pri)*
static Node *Mul()
{
	Node *node = Primary();

	for(;;){
		if(Consume("*", 1)){
			node = InsertNode(ND_MUL, node, Primary());
		}else if(Consume("/", 1)){
			node = InsertNode(ND_DIV, node, Primary());
		}else{
			return node;
		}
	}
}

// pri = num | ( Expr )
static Node *Primary()
{
	if(Consume("(", 1)){
		Node *node = Expr();
		Expect(")", 1);
		return node;
	}

	// => num
	Node *node = CreateNumNode(ExpectNum());	
	return node;
}

Node *ConstructTree(Token *token, char *p)
{
	code = p;
	token_cur = token;
	Node *root;
	while(!IsEOF(token_cur)){
		root = Expr();
	}

	return root;
}
