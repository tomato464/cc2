#include"generate.h"
#include<stdio.h>
#include"defines.h"
#include<stdlib.h>
// register name : rax, rbx, rcx, rdx, rsi, rdi, rbp, esp
//
char *code;

static void GenDfs(Node *node)
{
	if(!node){// maybe error
		return;
	}

	if(node->type == ND_NUM){
		printf("	push %d\n", node->num);
		return;
	}

	GenDfs(node->r_child);
	GenDfs(node->l_child);

	printf("	pop rax\n");
	printf("	pop rdi\n");


	switch(node->type){
	case ND_ADD:{
		printf("	add rax, rdi\n");
		break;
	}

	case ND_SUB :{
		printf("	sub rax, rdi\n");
		break;
	}
	case ND_MUL :{
		printf("	imul rax, rdi\n");
		break;
	}
	case ND_DIV :{
		printf("	cqo\n");
		printf("	idiv rdi\n");
		break;
	}
	default :
		fprintf(stderr, "not implemented yet\n");//code err function later
		exit(1);
		break;
	}	
	printf("	push rax\n");
}

void Generate(Node *node, char *p){
	code = p;

	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");
	
	GenDfs(node);

	printf("	pop rax\n");
	printf("	ret\n");	
}
