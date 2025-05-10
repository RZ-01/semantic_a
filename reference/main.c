#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"
#include "mini.y.h"

int main(int argc,   char *argv[])
{
	if(argc != 2)
	{
		printf("usage: %s filename\n", argv[0]);
		exit(0);
	}
	
	char *input = argv[1];
	if(input[strlen(input)-1]!='m')
	{
		printf("%s does not end with .m\n", input);
		exit(0);
	}

	if(freopen(input, "r", stdin)==NULL) error("open %s failed\n", input);

	char *output=strdup(input);
	output[strlen(output)-1]='x';

	if((x=fopen(output,"w"))==NULL) error("open %s failed\n", output);

	tac_init();

	yyparse();

	out_tac_list();

	return 0;
}
