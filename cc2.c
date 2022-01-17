#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"defines.h"
#include"tokenize.h"

bool token_curize_test = false;
char *p;
Token *token_cur = NULL;

int ExpectNum()
{
	if(token_cur->type == TK_NUM){
		int ret = token_cur->num;
		token_cur = token_cur->next;
		return ret;		
	}else{
		printf("expectng num\n");
		exit(1);
	}
}

bool Consume(char *p)
{
	if(token_cur->type != TK_RESERVED){
		return false;
	}

	if(!strncmp(token_cur->str, p, 1)){
		token_cur = token_cur->next;
		return true;
	}
	return false;
}

static int ParseArgs(int argc, char *argv[])
{
	bool input = false;

	while(argc > 0){
		if(!strncmp(argv[0], "--input", 7) || !strncmp(argv[0], "-i", 2)){
			p = argv[1];
			argc -= 2;
			argv += 2;
			input = true;
			continue;
		}
		if(!strncmp(argv[0], "--token_curize_test", 15)){
			token_curize_test = true;
			argc -= 1;
			argv += 1;
			continue;
		}
		return -1;
	}

	if(input){
		return 0;
	}

	return -1;
}

int main(int argc, char *argv[])
{
	int n = ParseArgs(argc - 1, argv + 1);

	if(n < 0){
		fprintf(stderr, "Usage error : %s --input input\n--token_curize_test => token_curize test\n", argv[0]);
		return 0;
	}

	if(token_curize_test){
		Token *token_cur = Tokenize(p);
		PrintToken(token_cur);
		return 0;
	}

	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");
	
	token_cur = Tokenize(p);
	printf("	mov eax, %d\n", ExpectNum());

	while(!IsEOF(token_cur)){
		if(Consume("+")){
			printf("	add eax, %d\n", ExpectNum());
			continue;
		}
		if(Consume("-")){
			printf("	sub eax, %d\n", ExpectNum());
			continue;
		}
		fprintf(stderr, "compile error\n");
		exit(1);
	}

	printf("	ret\n");
	return 0;
}
