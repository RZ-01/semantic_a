CC = gcc
CXX = g++
CFLAGS = -Wall -g
CXXFLAGS = -Wall -g -std=c++17

all: compiler

compiler: y.tab.c lex.yy.c tac.o main.o obj.o
	$(CXX) $(CXXFLAGS) -o compiler y.tab.c lex.yy.c tac.o main.o obj.o

y.tab.c y.tab.h: custom.y
	yacc -d custom.y

lex.yy.c: custom.l y.tab.h
	flex custom.l

tac.o: tac.c tac.h
	$(CC) $(CFLAGS) -c tac.c

main.o: main.c tac.h y.tab.h
	$(CC) $(CFLAGS) -c main.c

obj.o: obj.cpp obj.h
	$(CXX) $(CXXFLAGS) -c obj.cpp

clean:
	rm -f compiler lex.yy.c y.tab.c y.tab.h *.o *.tac *.asm

test: compiler
	./compiler test.cl

.PHONY: all clean test
