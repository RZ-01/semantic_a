CC = gcc
CFLAGS = -Wall -g

all: compiler asm machine

compiler: main.c tac.h obj.h xzl.c lyr.c zjr.c custom.y custom.l tac.c
	yacc -d custom.y
	flex custom.l
	$(CC) $(CFLAGS) -c tac.c
	$(CC) $(CFLAGS) zjr.c xzl.c lyr.c tac.o main.c y.tab.c lex.yy.c -o compiler

clean:
	rm -f compiler lex.yy.c y.tab.c y.tab.h *.o *.tac asm machine

asm: asm.l asm.y opcode.h
	lex -o asm.l.c asm.l
	yacc -d -o asm.y.c asm.y
	gcc -g3 asm.l.c asm.y.c -o asm

machine: machine.c opcode.h
	gcc -g3 machine.c -o machine

test: compiler machine asm
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH; \
	./compiler test.cl; \
	./asm output.s; \
	./machine output.o

.PHONY: all clean test
