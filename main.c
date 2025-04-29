#include"tac.h"
#include"y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* x;
int scope, next_tmp, next_label;
SYM *sym_tab_global, *sym_tab_local;
TAC *tac_first, *tac_last;

int main(int argc,   char *argv[])
{
	if(argc != 2)
	{
		printf("usage: %s filename\n", argv[0]);
		exit(0);
	}
	
	char *input = argv[1];
	if(input[strlen(input)-1]!='a')
	{
		printf("%s does not end with .a\n", input);
		exit(0);
	}

	if(freopen(input, "r", stdin)==NULL) error("open %s failed\n", input);

	char *output=strdup(input);
	output[strlen(output)-1]='x';

	if((x=fopen(output,"w"))==NULL) error("open %s failed\n", output);

	init();

	yyparse();

	out_tac_list();

	return 0;
}

/*int main(int argc, char *argv[]) {

	if(argc!=2) {
		printf("usage: %s filename\n", argv[0]);
		exit(0);
	}			

	if( (yyin=fopen(argv[1], "r")) ==NULL )
	{
		printf("open file %s failed\n", argv[1]);
		exit(0);
	}

	yyparse();

	fclose(yyin);
	return 0;
}*/