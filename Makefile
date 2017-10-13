all: lispy

lispy: mpc.c mpc.h Sexpr.c
		cc -std=c99 -Wall Sexpr.c mpc.c -ledit -lm -o Sexpr
clean:
	rm Sexpr
