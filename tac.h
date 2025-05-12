#ifndef _TAC_H_
#define _TAC_H_

#include <stdio.h>
#include <stdlib.h>

/* 符号类型 */
#define SYM_UNDEF   0  // 未定义符号
#define SYM_VAR     1  // 变量
#define SYM_FUNC    2  // 函数
#define SYM_LABEL   3  // 标签
#define SYM_TEXT    4  // 文本
#define SYM_INT     5  // 整型常量
#define SYM_ARRAY   6  // 数组
#define SYM_CONST   7  // 常量变量
#define SYM_FLOAT   8  // 浮点型常量

/* 数据类型 */
#define UNDEF_TYPE  0  // 未定义类型
#define INT_TYPE    1  // 整型
#define FLOAT_TYPE  2  // 浮点型
#define BOOL_TYPE   3  // 布尔型
#define STRING_TYPE 4  // 字符串型

/* 三地址码操作类型 */
#define TAC_UNDEF        0   // 未定义
#define TAC_ADD          1   // a = b + c
#define TAC_SUB          2   // a = b - c
#define TAC_MUL          3   // a = b * c
#define TAC_DIV          4   // a = b / c
#define TAC_MOD          5   // a = b % c
#define TAC_EQ           6   // a = (b == c)
#define TAC_NE           7   // a = (b != c)
#define TAC_LT           8   // a = (b < c)
#define TAC_LE           9   // a = (b <= c)
#define TAC_GT           10  // a = (b > c)
#define TAC_GE           11  // a = (b >= c)
#define TAC_NEG          12  // a = -b
#define TAC_COPY         13  // a = b
#define TAC_GOTO         14  // goto a
#define TAC_IFZ          15  // if z goto a
#define TAC_IFNZ         16  // if !z goto a
#define TAC_BEGINFUNC    17  // 函数开始
#define TAC_ENDFUNC      18  // 函数结束
#define TAC_LABEL        19  // 标签
#define TAC_VAR          20  // 变量声明
#define TAC_FORMAL       21  // 形参
#define TAC_ACTUAL       22  // 实参
#define TAC_CALL         23  // a = call b
#define TAC_RETURN       24  // return a
#define TAC_INPUT        25  // input a
#define TAC_OUTPUT       26  // output a
#define TAC_AND          27  // a = b && c
#define TAC_OR           28  // a = b || c
#define TAC_NOT          29  // a = !b
#define TAC_ARRAY_INDEX  30  // a = b[c]
#define TAC_ARRAY_ASSIGN 31  // a[b] = c
#define TAC_FOR_INIT     32  // for初始化
#define TAC_FOR_COND     33  // for条件
#define TAC_FOR_UPDATE   34  // for更新
#define TAC_INT_TO_FLOAT 35  // int to float conversion
#define TAC_FLOAT_TO_INT 36  // float to int conversion

/* 符号表项结构 */
typedef struct sym {
    int type;            // 符号类型
    int scope;           // 作用域: 0全局, 1局部
    char *name;          // 符号名称
    int offset;          // 偏移量
    int value;           // 整型值（对于整型常量）
    float float_value;   // 浮点值（对于浮点型常量）
    int label;           // 标签编号
    struct sym *address; // 地址
    struct sym *next;    // 链表下一项
    void *etc;           // 额外信息
    int* para;           // 函数参数类型列表
    int retType;         // 函数返回类型
    int varType;         // 变量类型
    int size;            // 数组大小
    int isConst;         // 是否为常量
} SYM;

/* 三地址码结构 */
typedef struct tac {
    SYM *a;              // 目标/结果
    SYM *b;              // 操作数1
    SYM *c;              // 操作数2
    int op;              // 操作类型
    struct tac* next;    // 下一条指令
    struct tac* previous;// 上一条指令
} TAC;

/* 表达式结构 */
typedef struct exp {
    SYM *ret;            // 结果符号
    TAC *tac;            // 相关的三地址码
    struct exp *next;    // 下一个表达式
    void *etc;           // 额外信息
} EXP;

/* 全局变量声明 */
extern FILE *output_file;  // This should be declared, not defined
extern FILE *yyin;
extern int yylineno, scope, next_tmp, next_label;
extern SYM *sym_tab_global, *sym_tab_local;
extern TAC *tac_first, *tac_last;

/* 函数声明 */
void init();                                 // 初始化
TAC* join_tac(TAC* a, TAC* b);              // 连接TAC
SYM* get_var(char* name);                   // 获取变量
TAC* declare_func(char* name, TAC* parameters); // 声明函数
TAC* declare_para(char* name, int type);    // 声明参数
TAC* do_func(int retType, TAC* func, TAC* codes); // 处理函数定义
void tac_complete();                        // 完成TAC生成
SYM* do_var(char* name);                    // 变量定义
SYM* do_init_var(char* name, int value, int type); // 变量定义并初始化
SYM* do_init_float_var(char* name, float value, int type); // 浮点变量定义并初始化
TAC* mk_tac(int op, SYM *a, SYM *b, SYM *c); // 创建TAC
SYM* lookup_sym(char* name);                // 查找符号
EXP* do_bin(int binop, EXP *exp1, EXP *exp2); // 二元操作
SYM* mk_tmp();                              // 创建临时变量
SYM* mk_label(char *name);                  // 创建标签
EXP* do_cmp(int binop, EXP *exp1, EXP *exp2); // 比较操作
EXP* do_call_ret(char* name, EXP* exp);     // 函数调用
TAC* do_if(EXP *exp, TAC *blk);             // if语句
TAC* do_if_else(EXP *exp, TAC *blk1, TAC *blk2); // if-else语句
TAC* do_return(EXP* exp);                   // return语句
TAC* do_input(char* name);                  // 输入语句
TAC* do_output(EXP* exp);                   // 输出语句
TAC* do_while(EXP* exp, TAC* tac);          // while循环
TAC* do_assign(SYM *var, EXP *exp);         // 赋值语句
void add_type(int type, EXP* exp_list);     // 添加类型
TAC* do_declaration(EXP* exp_list);         // 声明语句
EXP* mk_exp(SYM* ret, TAC* tac, EXP* next); // 创建表达式
void error(const char *format, ...);        // 错误处理
SYM* mk_const(int value);                   // 创建常量
SYM* mk_float_const(float value);           // 创建浮点常量
SYM* insert_sym(SYM* sym);                  // 插入符号
SYM* insert_const(SYM* sym);                // 插入常量
SYM* mk_sym();                              // 创建符号
void out_tac_list();                        // 输出TAC列表
SYM* mk_text(char* text);                   // 创建文本
void out_tac(FILE* f, TAC* tac);            // 输出单条TAC
SYM* mk_array(char* name, int size);        // 创建数组
SYM* do_const_var(char* name, int value);   // 创建常量变量
EXP* do_array_index(SYM* array, EXP* index); // 数组索引
TAC* do_array_assign(SYM* array, EXP* index, EXP* value); // 数组赋值
EXP* do_bool_literal(int value);            // 布尔字面量
EXP* do_logic(int op, EXP *exp1, EXP *exp2); // 逻辑操作
EXP* do_not(EXP *exp);                       // 逻辑非操作
TAC* do_for(TAC* init, EXP* cond, TAC* update, TAC* body); // for循环

int yylex(void);                           // 词法分析函数
void yyerror(char* msg);                   // 语法错误函数

#endif
