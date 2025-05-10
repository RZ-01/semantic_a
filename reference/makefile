all: mini

mini: main.c mini.l mini.y tac.c tac.h
	lex -o mini.l.c mini.l
	yacc -d -o mini.y.c mini.y
	gcc -g3 main.c mini.l.c mini.y.c tac.c -o mini

clean:
	rm -fr *.l.* *.y.* *.x mini

