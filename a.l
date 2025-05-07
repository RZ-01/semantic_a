%{
    #include<stdlib.h>
    #include "tac.h"
    #include"y.tab.h"  
%}

%option yylineno

%%

"elif" {return ELSEIF;}

"else" {return ELSE;}

"if" {return IF;}

"int" {return TYPE_INTEGER;}

"double" {return TYPE_DOUBLE;}

"char" {return TYPE_CHAR;} /* New */

"void" {return TYPE_VOID;} /* New */

"for" {return FOR;} /* New */

"return" {return RETURN;}

"output" {return OUTPUT;}

"input" {return INPUT;}

"while" {return WHILE;}

"call" {return CALL;}

\"[^"]*\" {return TEXT;}

[A-Za-z][A-Za-z0-9_]* {
    yylval.string = strdup(yytext); 
	return IDENTIFIER;
}

[0-9]+ {
	yylval.string = strdup(yytext); 
	return INTEGER;
}

">=" {return GE;}

"==" {return EQ;}

"!=" {return NEQ;}

"<=" {return LE;}

"+"|"-"|"*"|"/"|"("|")"|"<"|">"|"="|";"|"{"|"}"|"["|"]"|","|"."|":" {return *yytext;}

[ \t\r\n]

. 	{
		printf("lexical error: line %d\n", yylineno);
		exit(0);
	}
%%

int yywrap()
{
    return 1;
}
