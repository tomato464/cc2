#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"defines.h"
#include"tokenize.h"
#include"parse.h"
#include"generate.h"

bool tokenize_test = false;
char *p;

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
		if(!strncmp(argv[0], "--tokenize_test", 15)){
			tokenize_test = true;
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
		fprintf(stderr, "Usage error : %s --input input\n--tokenize_test\n", argv[0]);
		return 0;
	}

	if(tokenize_test){
		Token *token = Tokenize(p);
		PrintToken(token);
		return 0;
	}

	
	Token *token = Tokenize(p);
	Node *node = ConstructTree(token, p);

	Generate(node, p);

	return 0;
}
