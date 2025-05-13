#include "tac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYDEBUG 1

#include "y.tab.h"
#include "obj.h"

int tos; /* top of static */
int tof; /* top of frame */
int oof; /* offset of formal */
int oon;

FILE* file_s;
FILE* output_file;
struct rdesc rdesc[16];
extern FILE* yyin;
extern int yyparse(void); 

void print_token(int token, char* lexeme) {
    fprintf(stderr, "Token: %d, Lexeme: %s\n", token, lexeme ? lexeme : "");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        exit(1);
    }
    
    char *input_filename = argv[1];
    size_t len = strlen(input_filename);
    
    if (len < 3 || input_filename[len-3] != '.' || 
        input_filename[len-2] != 'c' || input_filename[len-1] != 'l') {
        fprintf(stderr, "Input file must end with .cl extension\n");
        exit(1);
    }
    
    if ((yyin = fopen(input_filename, "r")) == NULL) {
        fprintf(stderr, "Cannot open input file %s\n", input_filename);
        exit(1);
    }
    
    char *output_filename = strdup(input_filename);
    output_filename[len-2] = 't';
    output_filename[len-1] = 'a';
    output_filename[len] = 'c';
    output_filename[len+1] = '\0';

	
    
    if ((output_file = fopen(output_filename, "w")) == NULL) {
        fprintf(stderr, "Cannot create output file %s\n", output_filename);
        exit(1);
    }

    init();
    
    printf("Starting lexical analysis...\n");
    
    printf("File content check:\n");
    rewind(yyin);
    int c;
    while ((c = fgetc(yyin)) != EOF) {
        putchar(c);
    }
    rewind(yyin);

    printf("Starting parser...\n");
    int parse_result = yyparse();
    printf("Parser returned: %d\n", parse_result);
    
    if (parse_result == 0) {
        printf("Parsing complete, generating code...\n");
        out_tac_list();
        printf("Compilation successful: output file is %s\n", output_filename);
    } else {
        printf("Parsing failed with code %d\n", parse_result);
    }
    fclose(yyin);
    fclose(output_file);
    free(output_filename);
    tac_obj();
    
    return 0;
}
