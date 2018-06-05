#include <stdio.h>
#include <stdlib.h>


#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char* readline(char* prompt){
	fputs(prompt,stdout);
	fgets(buffer, 2048,stdin);
	char* cpy=malloc(strlen(buffer)+1);
	strcpy(cpy,buffer);
	cpy[strlen(cpy)-1]='\0';
	return cpy;
}

void add_history(char* str){}

#else //__linux__ 
#include <editline/readline.h>
#include <editline/history.h>
#endif
//cc -std=c99 -Wall prompt.c -ledit -o prompt


int main(int argc, char  *argv[]){
	puts("Lisp Version 0.0.1");
	puts("Ctrl+c to exit");
	
	while(1){
		char* input=readline("lisp>");
		add_history(input);
		printf("%s\n",input );
		free(input);	

	}
	return 0;
}