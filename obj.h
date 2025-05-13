#define R_UNDEF -1
#define R_FLAG 0
#define R_IP 1
#define R_BP 2
#define R_JP 3
#define R_TP 4
#define R_GEN 5
#define R_NUM 16

#define MODIFIED 1
#define UNMODIFIED 0

#define LEN_INT 4
#define LEN_FLOAT 4
#define LEN_BOOL 4
#define LEN_POINTER 8

#define LOCAL_OFF 8
#define FORMAL_OFF -4

#include"tac.h"

struct rdesc /* register descriptor */
{
	struct sym *var;
	int mod;
	int cnt;
};
extern struct rdesc rdesc[16];
extern FILE* file_s;
extern int tos; /* top of static */
extern int tof; /* top of frame */
extern int oof; /* offset of formal */
extern int oon; /* offset of next frame */

void tac_obj();//生成目标代码,所有程序从这里开始
void asm_head();//目标代码开头，初始化R2和栈
void asm_tail();//目标代码结尾，退出程序
// Strings will be processed in asm_static
// void asm_str();//将输出语句需要用到的字符串放到exit后
void asm_static();//将全局变量放到以STATIC为开头的标签后
void asm_code(TAC* tac);//根据对应的三地址码生成对应的目标代码，只需要调用后续的asm_cond,asm_bin,asm_cmp等函数
void asm_var(TAC *tac);//变量声明语句
void asm_copy(TAC *tac);//赋值语句
void asm_label(TAC *tac);//label语句


// Teammates Jobs
void reg_fill(SYM *sym, int r, int mod);//将sym装入寄存器r中，产生对应的目标代码
void reg_write_back(int r);//将寄存器r中内容写回到栈里
void reg_clear(int r);//将寄存器r中内容清空
int reg_alloc(SYM* sym);//给sym分配一个寄存器
void reg_load(SYM *sym, int r);//将sym装入寄存器
void asm_ifz(TAC *tac);//if语句
void asm_input(TAC *tac);//input语句
void asm_output(TAC *tac);//output语句


void asm_bin(TAC *tac);//算术运算和逻辑运算
void asm_cmp(TAC *tac);//比较运算
void asm_return(TAC *tac);//return语句
void asm_call(TAC *tac);//函数调用
void asm_actual(TAC *tac);//实参入栈
void asm_formal(TAC *tac);//形参读取offset值
void asm_beginfunc(TAC *tac);//begin,跳转需修改tof,oof等
void asm_endfunc(TAC *tac);//begin,返回时需修改tof,oof等
int* reg_alloc_2(SYM* sym1,SYM* sym2);
int* reg_alloc_3(SYM* sym1,SYM* sym2,SYM* sym3);

