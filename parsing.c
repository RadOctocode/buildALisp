#include "mpc.h"
#ifdef _WIN32

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



#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char const *argv[]){
	
	//polish grammar
	mpc_parser_t* Number = mpc_new("num");
	mpc_parser_t* Operation = mpc_new("op");
	mpc_parser_t* Expression = mpc_new("expr");
	mpc_parser_t* Lisp= mpc_new("lisp");

	mpca_lang(MPCA_LANG_DEFAULT,
		"						 			 \
			num: /-?[0-9]+/;				 \
			op: '+' | '-' | '/' | '*' | \'%\';		 \
			expr: <num> |'(' <op> <expr>+ ')';\
			lisp: /^/ <op> <expr>+ /$/ ;	 \
		",
		Number, Operation, Expression, Lisp);
	//polish grammar

/*
	//decimal grammar
	mpc_parser_t* Digit = mpc_new("dgt");
	mpc_parser_t* Point = mpc_new("pnt");
	mpc_parser_t* De_num = mpc_new("dnum");

	mpca_lang(MPCA_LANG_DEFAULT,
		"						 			 \
			dgt: /[0-9]+/;  				 \
			pnt: '.';				 		 \
			dnum:/^/ <dgt><pnt><dgt> /$/;\
		",
		Digit,Point,De_num);
	//decimal grammar
*/
/*
	//conventional grammar
	mpc_parser_t* Number = mpc_new("num");
	mpc_parser_t* Operation = mpc_new("op");
	mpc_parser_t* Expression = mpc_new("expr");
	mpc_parser_t* Lisp= mpc_new("lisp");

	mpca_lang(MPCA_LANG_DEFAULT,
		"						 			 \
			num: /-?[0-9]+/;				 \
			op: '+' | '-' | '/' | '*' | \'%\';		 \
			expr: <num> |'(' <expr>+ <op> <expr>+ ')';\
			lisp: /^/ <expr>+ <op> <expr>+ /$/ ;	 \
		",
		Number, Operation, Expression, Lisp);
	//conventional grammar
*/
	//terminal
	puts("Lisp Version 0.0.1");
	puts("Ctrl+C TO EXIT");
	
	while(1){
		char* input=readline("lisp>");
		add_history(input);

		mpc_result_t r;//the result of the grammar

		if(mpc_parse("<stdin>",input,Lisp,&r)){//
			//when successful print AST
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
		}

		else{
			//otherwise print error
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}


		free(input);	

	}
	//terminal


	mpc_cleanup(4,Number, Operation, Expression, Lisp);

	return 0;
}

/*
    › Write a regular expression matching strings of all a or b such as aababa or bbaa.
		
    › Write a regular expression matching strings of consecutive a and b such as ababab or aba.

    › Write a regular expression matching pit, pot and respite but not peat, spit, or part.
    	
    › Change the grammar to add a new operator such as %.

    › Change the grammar to recognise operators written in textual format add, sub, mul, div.
    	-replace the symbols with add,sub,mul,div

    › Change the grammar to recognize decimal numbers such as 0.01, 5.21, or 10.2.
	
    › Change the grammar to make the operators written conventionally, between two expressions.

    › Use the grammar from the previous chapter to parse Doge. You must add start and end of input.

*/