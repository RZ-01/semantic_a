#include"tac.h"
#include<string.h>
#include<stdarg.h>
#include <stdlib.h>


//调用函数
EXP* do_call_ret(char* name,EXP* exp){
    SYM* func=lookup_sym(name);
    if(func==NULL)
        error("function not defination!\n");
    SYM* ret=mk_tmp();
    TAC* tac=mk_tac(TAC_VAR,ret,NULL,NULL);
    for(EXP* arg=exp;arg!=NULL;arg=arg->next)
        tac=join_tac(arg->tac,tac);
    while(exp!=NULL)
    {
        tac=join_tac(tac,mk_tac(TAC_ACTUAL,exp->ret,NULL,NULL));
        exp=exp->next;
    }
    tac=join_tac(tac,mk_tac(TAC_CALL,ret,func,NULL));
    return mk_exp(ret,tac,NULL);
}

//使用if语句，生成对应三地址码
TAC* do_if(EXP *exp, TAC *blk, TAC* elif){
    TAC* tac=exp->tac;
    SYM* label=mk_label(NULL);
    if(elif !=NULL){
        SYM* end=elif->a;
        tac=join_tac(tac,mk_tac(TAC_IFZ,label,exp->ret,NULL));
        tac=join_tac(tac,blk);
        tac=join_tac(tac,mk_tac(TAC_GOTO,end,NULL,NULL));
        tac=join_tac(tac,mk_tac(TAC_LABEL,label,NULL,NULL));
        tac=join_tac(tac,elif);
    }
    else{
        tac=join_tac(tac,mk_tac(TAC_IFZ,label,exp->ret,NULL));
        tac=join_tac(tac,blk);
        tac=join_tac(tac,mk_tac(TAC_LABEL,label,NULL,NULL));
    }
    return tac;
}

//if-else语句中的else部分的三地址码
TAC* do_else(TAC *blk){
    SYM* label=mk_label(NULL);
    TAC* tac=join_tac(blk,mk_tac(TAC_GOTO,label,NULL,NULL));
    tac=join_tac(tac,mk_tac(TAC_LABEL,label,NULL,NULL));
    return tac;
}

//return语句的三地址码
TAC* do_return(EXP* exp){
    TAC* tac=mk_tac(TAC_RETURN,exp->ret,NULL,NULL);
    tac=join_tac(exp->tac,tac);
    return tac;
}

//input语句的三地址码
TAC* do_input(char* name){
    SYM* sym=lookup_sym(name);
    return mk_tac(TAC_INPUT,sym,NULL,NULL);
}

//输出一个变量的三地址码
TAC* do_output(EXP* exp){
    TAC* tac;
    tac=mk_tac(TAC_OUTPUT,exp->ret,NULL,NULL);
    tac=join_tac(exp->tac,tac);
    return tac;
}

//while语句的三地址码
TAC* do_while(EXP* exp,TAC* tac){
    SYM* label=mk_label(NULL);
    TAC* code=mk_tac(TAC_LABEL,label,NULL,NULL);
    tac=join_tac(tac,mk_tac(TAC_GOTO,label,NULL,NULL));
    code=join_tac(code,do_if(exp,tac,NULL));
}

//for语句的三地址码
/* TAC* do_for(EXP* init_exp, EXP* cond_exp, EXP* update_exp, TAC* body_tac){
    TAC *tac1, *tac2, *tac3, *tac4, *tac5;
    SYM *label1, *label2, *label3;

    label1 = mk_label(NULL); 
    label2 = mk_label(NULL); 
    label3 = mk_label(NULL); 

    tac1 = init_exp->tac; 

    tac2 = mk_tac(TAC_LABEL, label1, NULL, NULL); 
    tac2 = join_tac(tac2, cond_exp->tac);
    tac2 = join_tac(tac2, mk_tac(TAC_IFZ, label3, cond_exp->ret, NULL)); 
    tac2 = join_tac(tac2, mk_tac(TAC_GOTO, label2, NULL, NULL));       

    tac3 = mk_tac(TAC_LABEL, label2, NULL, NULL); 
    tac3 = join_tac(tac3, body_tac);               
    tac3 = join_tac(tac3, update_exp->tac);         
    tac3 = join_tac(tac3, mk_tac(TAC_GOTO, label1, NULL, NULL)); 

    tac4 = mk_tac(TAC_LABEL, label3, NULL, NULL); 

    tac5 = join_tac(tac1, tac2);
    tac5 = join_tac(tac5, tac3);
    tac5 = join_tac(tac5, tac4);

    return tac5;
}

//for语句的三地址码（带声明）
TAC* do_for_decl(TAC* decl_tac, EXP* cond_exp, EXP* update_exp, TAC* body_tac){
    TAC *tac1, *tac2, *tac3, *tac4, *tac5;
    SYM *label1, *label2, *label3;

    label1 = mk_label(NULL); 
    label2 = mk_label(NULL); 
    label3 = mk_label(NULL); 

    tac1 = decl_tac; 

    tac2 = mk_tac(TAC_LABEL, label1, NULL, NULL); 
    tac2 = join_tac(tac2, cond_exp->tac);
    tac2 = join_tac(tac2, mk_tac(TAC_IFZ, label3, cond_exp->ret, NULL)); 
    tac2 = join_tac(tac2, mk_tac(TAC_GOTO, label2, NULL, NULL));       

    tac3 = mk_tac(TAC_LABEL, label2, NULL, NULL); 
    tac3 = join_tac(tac3, body_tac);               
    tac3 = join_tac(tac3, update_exp->tac);         
    tac3 = join_tac(tac3, mk_tac(TAC_GOTO, label1, NULL, NULL)); 

    tac4 = mk_tac(TAC_LABEL, label3, NULL, NULL); 

    tac5 = join_tac(tac1, tac2);
    tac5 = join_tac(tac5, tac3);
    tac5 = join_tac(tac5, tac4);

    return tac5;
} */

//赋值语句的三地址码
TAC* do_assign(SYM *var, EXP *exp){
    TAC* tac;
    tac=mk_tac(TAC_COPY,var,exp->ret,NULL);
    tac=join_tac(exp->tac,tac);
    return tac;
}

//给之前加入符号表的变量加上类型,修改varType
void add_type(int type,SYM* sym_list){
    SYM* tmp;
    for(SYM* sym=sym_list;sym!=NULL;sym=sym->next)
    {
        tmp=lookup_sym(sym->name);
        tmp->varType=type;
    }
}

//生成变量定义的三地址码
TAC* do_declaration(EXP* exp_list){
    TAC* tac;
    tac=mk_tac(TAC_VAR,exp_list->ret,NULL,NULL);
    if(exp_list->tac!=NULL)
           tac=join_tac(tac,exp_list->tac);
    for(EXP* exp=exp_list->next;exp!=NULL;exp=exp->next)
    {
        tac=join_tac(tac,mk_tac(TAC_VAR,exp->ret,NULL,NULL));
        if(exp->tac!=NULL)
           tac=join_tac(tac,exp->tac);
    }
    return tac;
}

//将符号加入符号表中，如果scope=1的话优先加入局部符号表中
SYM* insert_sym(SYM* sym)
{
    SYM* p=mk_sym();
    if(scope==1)
    {
        p=sym_tab_local;
        while(p!=NULL)
        {
            if(strcmp(p->name,sym->name)==0)
                break;
            p=p->next;
        }
        if(p!=NULL)
            error("identifier redefination!\n");
        p=sym_tab_local;
        if(p==NULL)
            sym_tab_local=sym;
        else
        {
            while(p->next!=NULL)
                p=p->next;
            p->next=sym;
        }
    }
    else
    {
        p=sym_tab_global;
        while(p!=NULL)
        {
            if(strcmp(p->name,sym->name)==0)
                break;
            p=p->next;
        }
        if(p!=NULL)
            error("identifier redefination!\n");
        p=sym_tab_global;
        if(p==NULL)
            sym_tab_global=sym;
        else
        {
            while(p->next!=NULL)
                p=p->next;
            p->next=sym;
        }
    }
    return sym;
}

//报错，如果在语义分析的过程中发现了问题则用该函数进行报错
void error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
	exit(0);
}

//给常数添加到全局符号表中
SYM* mk_const(int value)
{
    SYM* sym=mk_sym();
    char* name=malloc(20);
    sprintf(name,"%d",value);
    sym->name=name;
    sym->type=SYM_INT;
    sym->value=value;
    return insert_const(sym);
}

//生成一个label，在进行跳转的时候需要使用,需要将label加入符号表中
SYM* mk_label(char* name)
{
    char* label=malloc(20);
    sprintf(label,"L%d",next_label);
    SYM* sym=mk_sym();
    if(name!=NULL)
        sym->name=name;
    else
        sym->name=label;
    sym->label=next_label;
    next_label++;
    sym->type=SYM_LABEL;
    return insert_sym(sym);
}

//同样需要一个中间变量，这里进行的是比较的运算
EXP *do_cmp( int binop, EXP *exp1, EXP *exp2)
{
    SYM* sym=mk_tmp();
    TAC* tac=join_tac(exp1->tac,exp2->tac);
    tac=join_tac(tac,mk_tac(TAC_VAR,sym,NULL,NULL));
    tac=(tac,mk_tac(binop,sym,exp1->ret,exp2->ret));
    return mk_exp(sym,tac,NULL);
}

//把字符串添加进符号表中
SYM* mk_text(char* text)
{
    char* label=malloc(20);
    sprintf(label,"L%d",next_label);
    SYM* sym=mk_sym();
    sym->name=text;
    sym->type=SYM_TEXT;
    sym->label=next_label;
    next_label++;
    return insert_sym(sym);
}

//把format这个字符串添加进最后输出的文件中
void out_str(FILE *f, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(f, format, args);
    va_end(args);
}

//从tac_first开始，将每一个tac都输出到文件中
void out_tac_list()
{
    out_str(x,".code\n");
    for(TAC*cur=tac_first;cur!=NULL;cur=cur->next)
    {
        out_str(x,"%p\t",cur);
        out_tac(x,cur);
    }
}

//将常数添加进全局符号表中
SYM* insert_const(SYM* sym)
{
    SYM* p=mk_sym();
    p=sym_tab_global;
    while(p!=NULL)
    {
        if(strcmp(p->name,sym->name)==0)
            break;
        p=p->next;
    }
    if(p!=NULL)
        return p;
    p=sym_tab_global;
    if(p==NULL)
        sym_tab_global=sym;
    else
    {
        while(p->next!=NULL)
            p=p->next;
        p->next=sym;
    }
    return sym;
}

/*

//定义一个变量，此时的varType为TYPE_UNDEF,value默认为0,将其加入符号表中，返回这个变量
SYM* do_var(char* name){
    SYM* sym=insert_sym(name,SYM_VAR);
    sym->varType=TYPE_UNDEF;
    sym->value=0;
    return sym;
}

//定义一个变量，此时的varType为TYPE_UNDEF，将其加入符号表中，返回这个变量
SYM* do_init_var(char* name,int value){
    SYM* sym=insert_sym(name,SYM_VAR);
    sym->varType=TYPE_UNDEF;
    sym->value=value;
    return sym;
}

//找到b这个保存TAC*类型的链表中的第一个TAC* head，然后head->previous=a,返回b，即这个链表中的最后一个元素
TAC* join_tac(TAC* a,TAC* b){
    TAC* head=b;
    while(head->previous!=NULL)
        head=head->previous;
    head->previous=a;
    return b;
}

void init()
{
    sym_tab_global=NULL;
    sym_tab_local=NULL;
    scope=0;
    next_tmp=0;
    next_label=0;
}

//生成一个中间变量
SYM* mk_tmp()
{
    char* tmp=malloc(12);
    sprintf(tmp,"t%d",next_tmp++);
    SYM* sym=insert_sym(tmp,SYM_VAR);
    return sym;
}

TAC* mk_tac(int op, SYM *a, SYM *b, SYM *c)
{
    TAC* tac;
    tac->op=op;
    tac->a=a;
    tac->b=b;
    tac->c=c;
    return tac;
}

//同样需要一个中间变量，这里进行的是比较的运算
EXP *do_cmp( int binop, EXP *exp1, EXP *exp2)
{
    
}
*/