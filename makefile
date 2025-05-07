all:test

test:main.c a.l a.y xzl.c zjr.cpp lyr.c tac.h
	lex a.l
	yacc -d a.y -Wcounterexamples
	g++ -g3 y.tab.c lex.yy.c main.c xzl.c zjr.cpp lyr.c -o test

clean:
	rm lex.yy.c test y.tab.c y.tab.h *.x

debug:main.c a.l a.y xzl.c zjr.cpp lyr.c tac.h
	lex a.l
	yacc -d a.y -Wcounterexamples
	g++ -g3 y.tab.c lex.yy.c main.c xzl.c zjr.cpp lyr.c -o test
	gdb ./test