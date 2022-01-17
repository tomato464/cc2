#include<stdio.h>

int main(int argc, char *argv[])
{
	/*
	if(argc != 2){
		fprintf(stderr, "Usage error : %s input", argv[0]);
		return 0;
	}
	*/

	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");
	printf("	mov rax, 42\n");
	printf("	ret\n");
	
}
