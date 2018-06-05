int main(int argc, char const *argv[]){
	mpc_parser_t* Number = mpc_new("num");
	mpc_parser_t* Operation = mpc_new("op");
	mpc_parser_t* Expression = mpc_new("expr");
	mpc_parser_t* Lisp= mpc_new("lisp");

	mpca_lang(MPCA_LANG_DEFAULT,
		"						 			    \
			num : /-?[0-9]+/ ;				    \
			op  : '+' | '-' | '/' | '*' ;	    \
			expr: <num> | '(' <op> <expr>+ ')' ;\
			lisp: /^/ <op> <expr>+ /$/ ;	    \
		",
		Number, Operation, Expression, Lisp);

	puts("Lisp Version 0.0.1");
	puts("Ctrl+C TO EXIT");
	
	while(1){
		char* input=readline("lisp>");
		add_history(input);

		mpc_result_t r;

		if(mpc_parse("<stdin>",input,Lisp,&r)){//
			
			long result = eval(r.output);
      		printf("%li\n", result);
      		mpc_ast_delete(r.output);
	
		}

		else{
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}


		free(input);	

	}

	mpc_cleanup(4,Number, Operation, Expression, Lisp);

	return 0;
}