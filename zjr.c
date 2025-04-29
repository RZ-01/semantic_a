#include "tac.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//初始化变量
void init() {
    sym_tab_global = NULL;
    sym_tab_local = NULL;
    scope = 0;  // 默认为全局作用域
    next_tmp = 0;
    next_label = 0;
    tac_first = NULL;
    tac_last = NULL;
}

// 创建三地址码
TAC* mk_tac(int op, SYM *a, SYM *b, SYM *c) {
    TAC* tac = (TAC*)malloc(sizeof(TAC));
    assert(tac != NULL); 
    
    tac->op = op;
    tac->a = a;
    tac->b = b;
    tac->c = c;
    tac->next = NULL;
    tac->previous = NULL;
    
    return tac;
}

//通过标识符名称查找符号表
SYM* lookup_sym(char* name){
    SYM* p;
    if(scope==1)
    {
        p=sym_tab_local;
        while(p!=NULL)
        {
            if(strcmp(p->name,name)==0)
                break;
            p=p->next;
        }
        if(p!=NULL)
            return p;
    }
    p=sym_tab_global;
    while(p!=NULL)
    {
        if(strcmp(p->name,name)==0)
            break;
        p=p->next;
    }
    if(p!=NULL)
        return p;
    return NULL;
}

//返回一个临时变量，临时变量的名称为t0,t1....
SYM* mk_tmp() {
    char name[32];
    sprintf(name, "t%d", next_tmp++);
    return do_var(name);
}

//将一个变量添加进符号表中，变量初始值默认为0
SYM* do_var(char* name) {
    SYM* sym = (SYM*)malloc(sizeof(SYM));
    assert(sym != NULL);
    
    sym->name = strdup(name);
    sym->type = SYM_VAR;
    sym->scope = scope;
    sym->value = 0;
    sym->varType = UNDEF_TYPE;
    sym->para = NULL;
    sym->retType = UNDEF_TYPE;
    sym->next = NULL;
    
    if (scope == 0) {
        sym->next = sym_tab_global;
        sym_tab_global = sym;
    } else {
        sym->next = sym_tab_local;
        sym_tab_local = sym;
    }
    return sym;
}

//将一个变量添加进符号表中，并且给它赋初值
SYM* do_init_var(char* name, int value) {
    SYM* sym = do_var(name);
    sym->value = value;
    return sym;
}

//将两个EXP*类型变量的算术运算合并成一个EXP*
EXP* do_bin(int binop, EXP *exp1, EXP *exp2) {
    SYM* tmp = mk_tmp();
    TAC* tac = mk_tac(binop, tmp, exp1->ret, exp2->ret);
    
    tac = join_tac(exp1->tac, tac);
    tac = join_tac(exp2->tac, tac);
    return mk_exp(tmp, tac, NULL);
}

//根据给定的ret,tac,next生成EXP*类型变量
EXP* mk_exp(SYM* ret, TAC* tac, EXP* next) {
    EXP* exp = (EXP*)malloc(sizeof(EXP));
    assert(exp != NULL);
    
    exp->ret = ret;
    exp->tac = tac;
    exp->next = next;
    exp->etc = NULL;
    
    return exp;
}

//将两个三地址码合并，返回值为合并的三地址码的最后一个
TAC* join_tac(TAC* a, TAC* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    
    TAC* t = b;
    while (t->previous != NULL) 
        t = t->previous;
    a->next = t;
    t->previous = a;
    return b;
}

//把三地址码输出到文件中，形式由TAC*变为对应要求的三地址码
void out_tac(FILE* f,TAC* tac)
{
    switch (tac->op) {
        case TAC_ADD:
            fprintf(x, "%s = %s + %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_SUB:
            fprintf(x, "%s = %s - %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_MUL:
            fprintf(x, "%s = %s * %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_DIV:
            fprintf(x, "%s = %s / %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_COPY:
            fprintf(x, "%s = %s\n", tac->a->name, tac->b->name);
            break;
        case TAC_EQ:
            fprintf(x, "%s = %s == %s\n", tac->a->name, tac->b->name,tac->c->name);
            break;
        case TAC_NE: /* a=(b!=c) */
            fprintf(x, "%s = %s != %s\n", tac->a->name, tac->b->name,tac->c->name);
            break;
        case TAC_LT: /* a=(b<c) */
            fprintf(x, "%s = %s < %s\n", tac->a->name, tac->b->name,tac->c->name);
            break;
        case TAC_LE: /* a=(b<=c) */
            fprintf(x, "%s = %s <= %s\n", tac->a->name, tac->b->name,tac->c->name);
            break;
        case TAC_GT: /* a=(b>c) */
            fprintf(x, "%s = %s > %s\n", tac->a->name, tac->b->name,tac->c->name);
            break;
        case TAC_GE: /* a=(b>=c) */ 
            fprintf(x, "%s = %s >= %s\n", tac->a->name, tac->b->name,tac->c->name);
            break;
        case TAC_NEG: /* a=-b */
            fprintf(x, "%s = -%s\n", tac->a->name, tac->b->name);
            break;
        case TAC_GOTO: /* goto a */
            fprintf(x, "goto %s\n", tac->a->name);
            break;
        case TAC_IFZ: /* ifz b goto a */
            fprintf(x, "ifz %s goto %s\n", tac->b->name, tac->a->name);
            break;
        case TAC_BEGINFUNC: /* function begin */
            fprintf(x, "begin\n");
            break;
        case TAC_ENDFUNC: /* function end */
            fprintf(x, "end\n");
            break;
        case TAC_LABEL: /* label a */
            fprintf(x, "label %s\n", tac->a->name);
            break;
        case TAC_VAR: /* int a */
            fprintf(x, "var %s\n", tac->a->name);
            break;
        case TAC_FORMAL: /* formal a */
            fprintf(x, "formal %s\n", tac->a->name);
            break;
        case TAC_ACTUAL: /* actual a */
            fprintf(x, "actual %s\n", tac->a->name);
            break;
        case TAC_CALL: /* a=call b */
            fprintf(x, "%s = call %s\n", tac->a->name, tac->b->name);
            break;
        case TAC_RETURN: /* return a */
            fprintf(x, "return %s\n", tac->a->name);
            break;
        case TAC_INPUT: /* input a */
            fprintf(x, "input %s\n", tac->a->name);
            break;
        case TAC_OUTPUT: /* output a */
            fprintf(x, "output %s\n", tac->a->name);
            break;
        default:
            fprintf(x, "Unknown operation: %d\n", tac->op);
        }
}

//将原先的只能从表尾向表头遍历的单向链表变为双向链表
void tac_complete() {
    TAC* tac=tac_last;
    if(tac==NULL)
        return;
    tac_last->next=NULL;
    while(tac->previous!=NULL)
    {   
        tac->previous->next=tac;
        tac=tac->previous;
    }
    tac_first=tac;
} 