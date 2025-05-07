#include<stdio.h>
#define SYM_UNDEF 0
#define SYM_VAR 1
#define SYM_FUNC 2
#define SYM_LABEL 3
#define SYM_TEXT 4
#define SYM_INT 5

#define UNDEF_TYPE 0
#define INT_TYPE 1
#define DOUBLE_TYPE 2
#define CHAR_TYPE 3 /* New */
#define VOID_TYPE 4 /* New */

#define TAC_UNDEF 0 /* undefine */
#define TAC_ADD 1 /* a=b+c */
#define TAC_SUB 2 /* a=b-c */
#define TAC_MUL 3 /* a=b*c */
#define TAC_DIV 4 /* a=b/c */
#define TAC_EQ 5 /* a=(b==c) */
#define TAC_NE 6 /* a=(b!=c) */
#define TAC_LT 7 /* a=(b<c) */
#define TAC_LE 8 /* a=(b<=c) */
#define TAC_GT 9 /* a=(b>c) */
#define TAC_GE 10 /* a=(b>=c) */
#define TAC_NEG 11 /* a=-b */
#define TAC_COPY 12 /* a=b */
#define TAC_GOTO 13 /* goto a */
#define TAC_IFZ 14 /* ifz b goto a */
#define TAC_BEGINFUNC 15 /* function begin */
#define TAC_ENDFUNC 16 /* function end */
#define TAC_LABEL 17 /* label a */
#define TAC_VAR 18 /* int a */
#define TAC_FORMAL 19 /* formal a */
#define TAC_ACTUAL 20 /* actual a */
#define TAC_CALL 21 /* a=call b */
#define TAC_RETURN 22 /* return a */
#define TAC_INPUT 23 /* input a */
#define TAC_OUTPUT 24 /* output a */
#define TAC_FOR 25 /* New */
#define TAC_FOR_INIT 26 /* New */
#define TAC_FOR_COND 27 /* New */
#define TAC_FOR_UPDATE 28 /* New */

typedef struct sym
{
	int type;
	int scope; // 0:global, 1:local
	char *name;
	int offset;
	int value;
	int label;
	struct tac *address; //SYM_FUNC
	struct sym *next;
	void *etc;
	int* para;//对于函数，需要保存各个参数的类型,如果不是函数则为NULL
	int retType;//对于函数，表示其返回值的类型
	int varType;//对于变量，无论是形参还是实参，都保存这个变量的类型
} SYM;

typedef struct tac{
	SYM *a;
	SYM *b;
	SYM *c;
	int op;
	struct tac* next;
	struct tac* previous;
}TAC;

typedef struct exp{
	SYM *ret;
	TAC *tac;
	struct exp *next;
	void *etc;
}EXP;

extern FILE *x,*yyin;
//next_tmp表示临时变量序号,临时变量名称如：t0。如果存在自定义的变量名称为t0?
//next_label表示生成的三地址码的label序号
//scope 1:local 0:global
extern int yylineno, scope, next_tmp, next_label;
extern SYM *sym_tab_global, *sym_tab_local;
extern TAC *tac_first, *tac_last;

//所有三地址码在输出到文件前都以TAC类型存储
void init();//初始化变量，如sym_tab_global,scope,next_tmp;
TAC* join_tac(TAC* a,TAC* b);//找到b这个保存TAC*类型的链表中的第一个TAC* t，然后t->next=a,返回b，即这个链表中的最后一个元素
SYM* get_var(char* name); //将变量从符号表中取出来
TAC* declare_func(char* name,TAC* parameters);//声明函数，返回这个函数
TAC* declare_para(char* name,int type);//声明参数，生成对应的三地址码，这个三地址码中的a中的varType=type
TAC* do_func(int retType,TAC* func,TAC* codes);//根据函数的返回值类型，函数名，函数中的代码生成对应的三地址码
void tac_complete();
SYM* do_var(char* name);//定义一个变量，此时的varType为TYPE_UNDEF,value默认为0,将其加入符号表中，返回这个变量
SYM* do_init_var(char* name,int value);//定义一个变量，此时的varType为TYPE_UNDEF，将其加入符号表中，返回这个变量
TAC* mk_tac(int op, SYM *a, SYM *b, SYM *c);
SYM* lookup_sym(char* name);//通过标识符名称查找符号表
EXP* do_bin( int binop, EXP *exp1, EXP *exp2);//对于两个表达式进行算术运算，注意，中间值需要生成一个中间变量，这里使用mk_tmp()
SYM* mk_tmp();//生成一个中间变量
SYM* mk_label(char *name);//生成一个label，在进行跳转的时候需要使用
EXP *do_cmp( int binop, EXP *exp1, EXP *exp2);//同样需要一个中间变量，这里进行的是比较的运算
EXP* do_call_ret(char* name,EXP* exp);//调用函数
TAC* do_if(EXP *exp, TAC *blk, TAC* elif);//使用if语句，生成对应三地址码，最后跳转到label处
TAC* do_else(TAC *blk);//if-else语句中的else部分的三地址码
TAC* do_ifelif(EXP *exp, TAC *blk, TAC* elif);//生成if-else语句的三地址码
TAC* do_return(EXP* exp);//return语句的三地址码
TAC* do_input(char* name);//input语句的三地址码
TAC* do_output(EXP* exp);//输出一个变量的三地址码
TAC* do_while(EXP* exp,TAC* tac);//while语句的三地址码
TAC* do_assign(SYM *var, EXP *exp);//赋值语句的三地址码
// TAC* do_for(EXP* init_exp, EXP* cond_exp, EXP* update_exp, TAC* body_tac); 
// TAC* do_for_decl(TAC* decl_tac, EXP* cond_exp, EXP* update_exp, TAC* body_tac); 
TAC* do_for_loop(TAC* init_tac, EXP* cond_exp, EXP* update_exp, TAC* body_tac); /* New combined function */
void add_type(int type,SYM* sym_list);//给之前加入符号表的变量加上类型,修改varType
TAC* do_declaration(EXP* exp_list);//生成变量定义的三地址码
EXP* mk_exp(SYM* ret,TAC* tac,EXP* next);//初始化一个EXP*类型变量
void error(const char *format, ...);
SYM* mk_const(int value);
SYM* insert_sym(SYM* sym);
SYM* insert_const(SYM* sym);
SYM* mk_sym();
void out_tac_list();
SYM* mk_text(char* text);
void out_tac(FILE* f,TAC* tac);