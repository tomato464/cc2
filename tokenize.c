#include"tokenize.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

Token *head = NULL;
Token *cur = NULL;

#define RESERVED_NUM 6
char *reserved_chrs[RESERVED_NUM] = {"+", "-", "*", "/", "(", ")"};
static Token *CreateToken(TokenType type)
{
	Token *token;
	token = (Token *) malloc(sizeof(Token));
	memset(token, 0, sizeof(Token));

	token->type = type;

	return token;
}

static void InsertReservedToken(char *p)
{
	Token *token = CreateToken(TK_RESERVED);

	token->str = p;//point in input, not copy

	cur->next = token;
	cur = token;
}

static void InsertNumToken(char *p, int num)
{
	Token *token = CreateToken(TK_NUM);
	token->str = p;
	token->num = num;
	cur->next = token;
	cur = token;
}

static bool IsSpace(char *p)
{
	if(*p == ' '){
		return true;
	}
	return false;
}

static bool IsReserved(char *p)
{
	char *reserved;
	for(int i = 0; i < RESERVED_NUM; i++){
		reserved = reserved_chrs[i];
		if(!reserved){
			return false;
		}

		if(!strncmp(p, reserved, 1)){
			return true;
		}
	}
	return false;
}

static bool IsDigit(char *p)
{
	if('0' <= *p && *p <= '9'){
		return true;
	}
	return false;
}

Token *Tokenize(char *p)
{
	head = (Token *) malloc(sizeof(Token));
	memset(head, 0, sizeof(Token));
	cur = head;

	while(*p){
		if(IsSpace(p)){
			p++;
			continue;
		}

		if(IsReserved(p)){
			InsertReservedToken(p);
			p++;
			continue;
		}	
		//assume num
		if(IsDigit(p)){
			int i = strtol(p, &p, 10);
			InsertNumToken(p, i);
			continue;
		}

		printf("error tokenize at : %c\n", *p);
		exit(1);
	}

	cur->next = CreateToken(TK_EOF);

	return head->next;
}

bool IsEOF(Token *token)
{
	if(token->type == TK_EOF){
		return true;
	}	
	return false;
}

void Print(Token *token)
{
	switch(token->type){
	case TK_NUM:{
		printf("type : NUM %d => " , token->num);
		break;
	}
	case TK_RESERVED :{
		printf("type : RES %s => ", token->str);
		break;
	}

	default :{
		break;
	}
	}
}

//for debug purpuse
void PrintToken()
{
	Token *token = head->next;
	while(!IsEOF(token)){
		Print(token);
		token = token->next;
	}
	printf("\n");
}
