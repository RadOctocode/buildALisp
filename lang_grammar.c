#include "mpc.h"
int main(int argc, char const *argv[]){
	
	mpc_parser_t* Adjective = mpc_new("adj");
	mpc_parser_t* Noun = mpc_new("noun");
	mpc_parser_t* Phrase = mpc_new("phr");
	mpc_parser_t* Sentence = mpc_new("sent");

	mpca_lang(MPCA_LANG_DEFAULT,
		"						 \
			adj:\"rad\"|\"wild\";\
			noun:\"dog\"|\"cat\";\
			phr: <adj> <noun>;	 \
			sent:<phr>*;		 \
		",
		Adjective, Noun, Phrase, Sentence);

	mpc_cleanup(4,Adjective,Noun,Phrase,Sentence);

	return 0;
}

/*
    › Write down some more examples of strings the Doge language contains.
    	-rad dog wild cat
    	-rad cat wild dog
    	-wild dog
    	-rad dog
    	-wild cat
    	-rad cat
    	-
    › Why are there back slashes \ in front of the quote marks " in the grammar?
    	-nested strings
    › Why are there back slashes \ at the end of the line in the grammar?
    	-multilined strings
    › Describe textually a grammar for decimal numbers such as 0.01 or 52.221.
    	pos:1|2|3|4|5|6|7|8|9|0;
    	point:.;
    	num:<pos><point><pos>;
    › Describe textually a grammar for web URLs such as http://www.buildyourownlisp.com.
    	header:http://www.;
    	word:a-z|A-Z|1-0;
    	end:.com;
    	URL:<header><word>*<end>
    › Describe textually a grammar for simple English sentences such as the cat sat on the mat.
    	sentence:<adj>*<noun><verb><noun>*
    › Describe more formally the above grammars. Use |, *, or any symbols of your own invention.
	› If you are familiar with JSON, textually describe a grammar for it.
*/