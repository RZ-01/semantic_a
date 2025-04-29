#include"tac.h"
#include<stdlib.h>

//分配一个SYM*类型的变量
SYM* mk_sym()
{
    SYM* sym=(SYM*)malloc(sizeof(SYM));
    return sym;
}

// 将变量从符号表中取出来
SYM* get_var(char* name)
{
    SYM* sym=lookup_sym(name);
    if(sym==NULL)
        error("variable not defination!\n");
    else if(sym->type!=SYM_VAR)
        error("type incorrect");
    return sym;
}

// 声明函数，返回这个函数的label以及参数的tac（即label func和formal a等）
TAC *declare_func(char *name, TAC *parameters)
{
    SYM *sym = NULL;

    sym = lookup_sym(name);

    if (sym != NULL)
    {
        if (sym->type == SYM_FUNC)
        {
            error("func already declared");
            return NULL;
        }

        if (sym->type != SYM_UNDEF)
        {
            error("func name already used");
            return NULL;
        }

        return mk_tac(TAC_LABEL,sym,NULL,NULL);
    }

    sym = mk_sym();
    sym->type = SYM_FUNC;
    sym->name = name;
    sym->address=NULL;
    int cnt=0;
    for(TAC* tac=parameters;tac!=NULL;tac=tac->previous)
        cnt++;
    sym->para =(int*)malloc(sizeof(int)*cnt);
    cnt=0;
    for(TAC* tac=parameters;tac!=NULL;tac=tac->previous)
    {
        sym->para[cnt]=tac->a->type;
        cnt++;
    }
    insert_sym(sym);
    TAC* t=join_tac(mk_tac(TAC_LABEL,sym,NULL,NULL),parameters);
    return t;
}

// 声明参数，生成对应的三地址码，这个三地址码中的a中的varType=type
TAC *declare_para(char *name, int type)
{
    SYM *sym = NULL;

    sym = lookup_sym(name);

    if (sym != NULL)
    {
        error("para already declared");
        return NULL;
    }

    sym = mk_sym();
    sym->type = SYM_VAR;
    sym->varType = type;
    sym->name = name;

    insert_sym(sym);
    return mk_tac(TAC_FORMAL, sym, NULL, NULL);
}

// 根据函数的返回值类型，函数名，函数中的代码生成对应的三地址码
TAC *do_func(int retType, TAC *func, TAC *codes)
{
    SYM* sym;
    TAC* t;
    for(t=func;t->previous!=NULL;t=t->previous);
    sym=t->a;
    sym->retType=retType;
    TAC* tacBegin=mk_tac(TAC_BEGINFUNC,NULL,NULL,NULL);
    TAC* tacEnd=mk_tac(TAC_ENDFUNC,NULL,NULL,NULL);
    TAC* tac;
    tac=join_tac(func,tacBegin);
    tac=join_tac(tac,codes);
    tac=join_tac(tac,tacEnd);
    return tac;
}