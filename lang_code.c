#include "mpc.h"

int main(int argc, char const *argv[]){
	
	mpc_parser_t* Adjective=mpc_or(4,
		mpc_sym("wow"),mpc_sym("so"),
		mpc_sym("many"),mpc_sym("such")
	);

	mpc_parser_t* Noun=mpc_or(4,
		mpc_sym("hello"),mpc_sym("world"),
		mpc_sym("C"),mpc_sym("lisp")
	);

  	mpc_parser_t* Phrase = mpc_and(2, mpcf_strfold, 
    Adjective, Noun, free);
	
  	mpc_parser_t* Sentence=mpc_many(mpcf_strfold,Phrase)

	mpc_delete(Sentence);
	return 0;
}