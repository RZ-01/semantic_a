#include "tac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define YYDEBUG before including y.tab.h
#define YYDEBUG 1

#include "y.tab.h"

FILE* output_file;
extern FILE* yyin;
extern int yyparse(void); 

// Add a debug function for lexer
void print_token(int token, char* lexeme) {
    fprintf(stderr, "Token: %d, Lexeme: %s\n", token, lexeme ? lexeme : "");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "用法: %s 输入文件\n", argv[0]);
        exit(1);
    }
    
    char *input_filename = argv[1];
    size_t len = strlen(input_filename);
    
    // 检查文件扩展名
    if (len < 3 || input_filename[len-3] != '.' || 
        input_filename[len-2] != 'c' || input_filename[len-1] != 'l') {
        fprintf(stderr, "输入文件必须以 .cl 扩展名结尾\n");
        exit(1);
    }
    
    // 打开输入文件
    if ((yyin = fopen(input_filename, "r")) == NULL) {
        fprintf(stderr, "无法打开输入文件 %s\n", input_filename);
        exit(1);
    }
    
    // 创建输出文件名
    char *output_filename = strdup(input_filename);
    output_filename[len-2] = 't';
    output_filename[len-1] = 'a';
    output_filename[len] = 'c';
    output_filename[len+1] = '\0';
    
    // 打开输出文件
    if ((output_file = fopen(output_filename, "w")) == NULL) {
        fprintf(stderr, "无法创建输出文件 %s\n", output_filename);
        exit(1);
    }
    
    // 初始化编译器
    init();
    
    printf("Starting lexical analysis...\n");
    
    // 打印文件内容以验证读取正确
    printf("File content check:\n");
    rewind(yyin);
    int c;
    while ((c = fgetc(yyin)) != EOF) {
        putchar(c);
    }
    rewind(yyin);
    
    // 执行语法分析和语义分析
    printf("Starting parser...\n");
    int parse_result = yyparse();
    printf("Parser returned: %d\n", parse_result);
    
    if (parse_result == 0) {
        printf("Parsing complete, generating code...\n");
        // 输出三地址码
        out_tac_list();
        printf("编译成功: 输出文件为 %s\n", output_filename);
    } else {
        printf("Parsing failed with code %d\n", parse_result);
    }
    
    // 清理资源
    fclose(yyin);
    fclose(output_file);
    free(output_filename);
    
    return 0;
}
