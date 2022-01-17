#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_
#include"defines.h"

typedef enum {
	TK_NUM,
	TK_RESERVED,
	TK_EOF,
} TokenType;

typedef struct Token{
	TokenType type;
	struct Token *next;
	int num;
	char *str;
} Token;

Token *Tokenize(char *p);
bool IsEOF(Token *token);
void PrintToken();

#endif
