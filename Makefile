all: lispy

lispy: mpc.c mpc.h parsing.c
		cc -std=c99 -Wall parsing.c mpc.c -ledit -lm -o parsing
clean:
	rm parsing
