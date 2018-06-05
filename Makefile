all: qexpr sexpr

qexpr: mpc.c mpc.h qexpr.c
		cc -std=c99 -Wall qexpr.c mpc.c -ledit -lm -o qexpr


sexpr: mpc.c mpc.h sexpr.c
		cc -std=c99 -Wall sexpr.c mpc.c -ledit -lm -o sexpr

clean:
	rm qexpr sexpr
