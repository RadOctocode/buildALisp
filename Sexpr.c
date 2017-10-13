#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/*Fake readline function*/
char* readline(){
    fputs();
    fgets(buffer,2048,stdin);
    char* cpy=malloc(strlen(buffer)+1);
    strcpy(cpy,buffer);
    cpy[strlen(cpy)-1]='\0';
    return cpy;
}

void add_history(char* unused){}


#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

enum{ LVAL_NUM, LVAL_ERR};
enum{ LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM};

typedef struct {
    int type;
    long num;
    int err;
} lval;

lval lval_num(long x){
    lval v;
    v.type=LVAL_NUM;
    v.num=x;
    return v;

}

lval lval_err(int x){
    lval v;
    v.type=LVAL_ERR;
    v.err=x;
    return v;
}

void lval_print(lval v){
    switch(v.type){
        case LVAL_NUM: printf("%li", v.num); break;
        case LVAL_ERR:
           if(v.err==LERR_DIV_ZERO){
                printf("div error"); 
           }
           if(v.err==LERR_BAD_OP){
                printf("inval error");
           }

           if(v.err==LERR_BAD_NUM){
                printf("inval numb");
           }
           break;
    }
}

void lval_println(lval v){
    lval_print(v);
    putchar('\n');
}
lval eval_op(lval x, char* op, lval y) {
   if(x.type == LVAL_ERR){return x;}
   if(y.type == LVAL_ERR){return y;}

   if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
   if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
   if (strcmp(op, "%") == 0) { return lval_num(x.num % y.num); }
   if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
   if (strcmp(op, "/") == 0) {
       return y.num ==0 ? lval_err(LERR_DIV_ZERO): lval_num(x.num/y.num);
       
   }
   if (strcmp(op, "^") == 0) {
       long reps=y.num;
       long retVal=1;
       while(reps){
        retVal=(x.num)*retVal;
        reps=reps-1;
       }
      return lval_num(retVal); 
   }

   return lval_err(LERR_BAD_OP);
}

lval eval(mpc_ast_t* t) {
 
   
   if((!(strstr(t->tag, "number")))&&(t->children_num==4)){
       char* myop = t->children[1]->contents;
       if(*myop=='-'){       
          errno=0;
          long x=0-(strtol(t->children[2]->contents,NULL,10));
          return errno != ERANGE ? lval_num(x): lval_err(LERR_BAD_NUM);
       }
   }

   if (strstr(t->tag, "number")) {
       errno=0;
       long x=strtol(t->contents,NULL,10);
       return errno != ERANGE ? lval_num(x): lval_err(LERR_BAD_NUM);

   }
   
   char* op = t->children[1]->contents;
   lval x = eval(t->children[2]);
  
   int i = 3; 
   while (strstr(t->children[i]->tag, "expr")) {
       x = eval_op(x, op, eval(t->children[i]));
       i++;
   }

   return x;
}

int main(int argc, char** argv) {
    /* Create Some Parsers */
  mpc_parser_t* Number   = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr     = mpc_new("expr");
  mpc_parser_t* Lispy    = mpc_new("lispy");
  
  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number   : /-?[0-9]+/ ;                             \
      operator : '+' | '-' | '*' | '/' | '%' | '^';       \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      lispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
    Number, Operator, Expr, Lispy);


 
   puts("Lispy Version 0.0.0.0.1");
   puts("Press Ctrl+c to Exit\n");

   while (1) {

         /* takes string and output stream*/
         char* input=readline("lispy> ");
         add_history(input);

         mpc_result_t r;
         if(mpc_parse("<stdin>", input, Lispy, &r)){
          mpc_ast_print(r.output);
          /*mpc_ast_delete(r.output);*/
          mpc_ast_t* a = r.output;
         /* printf("Tag: %s\n", a->tag);
          printf("Contents: %s\n", a->contents);
          printf("Number of children: %i\n", a->children_num);

          mpc_ast_t* c0 = a->children[0];
          printf("First Child Tag: %s\n", c0->tag);
          printf("First Child Contents: %s\n", c0->contents);
          printf("First Child Number of children: %i\n",c0->children_num);
          */
            lval result =eval(r.output);
            lval_println(result);
            mpc_ast_delete(r.output);
         
         }
         else{
            /*Otherwise print and delete error*/
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
         
         }

         /* Echo input back to user */

         free(input);
    }

   mpc_cleanup(4, Number, Operator, Expr, Lispy);
   return 0;
}
