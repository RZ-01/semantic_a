#include "obj.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int reg_lookup(SYM* sym)
{
    for(int i=R_GEN;i<R_NUM;i++)
    {
        if(rdesc[i].var==sym)
            return i;
    }
    return -1;
}

// 将sym装入寄存器r中，产生对应的目标代码
void reg_fill(SYM *sym, int r,int mod)
{
    int a=reg_lookup(sym);
    if(a!=-1&&a!=r)
        reg_clear(a);
    rdesc[r].var = sym;
    rdesc[r].mod = mod;
}

// 将寄存器r中内容写回到栈里
void reg_write_back(int r)
{
    if (rdesc[r].var && rdesc[r].mod == MODIFIED)
    {
        SYM* sym=rdesc[r].var;
        if(sym->type==SYM_VAR)
        {
            if (sym->scope == 0)//global
            {
                out_str(file_s,"    LOD R%u,STATIC\n",R_TP);
                out_str(file_s,"    STO (R%u+%d),R%u\n",R_TP,sym->offset,r);
            }
            else if (sym->scope == 1)
            {
                if(sym->offset>0)
                    out_str(file_s,"    STO (R%u+%d),R%u\n",R_BP,sym->offset,r);
                else
                    out_str(file_s,"    STO (R%u%d),R%u\n",R_BP,sym->offset,r);
            }
        }
    }
    reg_clear(r);
}

// 将寄存器r中内容清空
void reg_clear(int r)
{
    rdesc[r].var = NULL;
    rdesc[r].mod = UNMODIFIED;
    rdesc[r].cnt=0;
}

int reg_alloc(SYM* sym)
{
    int r=reg_lookup(sym);
    if(r!=-1)
    {
        for(int i=R_GEN;i<R_NUM;i++)
            if(rdesc[i].cnt<rdesc[r].cnt&&rdesc[i].cnt!=0)
                rdesc[i].cnt+=1;
        rdesc[r].cnt=1;
	    return r;
    }
    r=reg_lookup(NULL);
    if(r!=-1)
    {
        for(int i=R_GEN;i<R_NUM;i++)
            if(rdesc[i].cnt!=0)
                rdesc[i].cnt+=1;
        rdesc[r].cnt=1;
        reg_fill(sym,r,UNMODIFIED);
        reg_load(sym,r);
	    return r;
    }
    for(int i=R_GEN;i<R_NUM;i++)
        if(rdesc[i].cnt==R_NUM-R_GEN)
            r=i;
        else
            rdesc[i].cnt+=1;
    rdesc[r].cnt=1;
    reg_write_back(r);
    reg_fill(sym,r,UNMODIFIED);
    reg_load(sym,r);
	return r;
}

// 将sym装入寄存器r
void reg_load(SYM *sym, int r)
{
    if (sym->type==SYM_TEXT)
        out_str(file_s,"    LOD R%u,L%d\n",r,sym->label);
    else if(sym->type==SYM_VAR)
    {
        if (sym->scope == 0)//global
        {
            out_str(file_s,"    LOD R%u,STATIC\n",R_TP);
            out_str(file_s,"    LOD R%u,(R%u+%d)\n",r,R_TP,sym->offset);
        }
        else if (sym->scope == 1)
        {
            if(sym->offset>0)
                out_str(file_s,"    LOD R%u,(R%u+%d)\n",r,R_BP,sym->offset);
            else
                out_str(file_s,"    LOD R%u,(R%u%d)\n",r,R_BP,sym->offset);
        }
    }
    else if(sym->type==SYM_INT)
        out_str(file_s,"    LOD R%u,%d\n",r,sym->value);
}

// ifz语句  ifz b goto a
void asm_ifz(TAC *tac)
{
    for(int r=R_GEN; r < R_NUM; r++) 
        reg_write_back(r);
    SYM* a=tac->a;
    SYM* b=tac->b;
    int* r=reg_alloc_2(a,b);
    out_str(file_s,"    TST R%u\n",r[1]);
    out_str(file_s,"    JEZ %s\n",a->name);
}

// input语句
void asm_input(TAC *tac)
{
    SYM* a=tac->a;
    int r=reg_alloc(a);
    reg_write_back(R_NUM);
    out_str(file_s,"    IN\n");
    out_str(file_s,"    LOD R%u,R%u\n",r,15);
	rdesc[r].mod=MODIFIED;
}

// output语句
void asm_output(TAC *tac)
{
    SYM* a=tac->a;
    int r=reg_lookup(a);
    if(r==-1)
    {
		reg_write_back(R_NUM-1);
        reg_load(a,R_NUM-1);
		if(a->type==SYM_VAR)
        	out_str(file_s,"    OUTN\n");
		else if(a->type==SYM_TEXT)
			out_str(file_s,"    OUTS\n");
    }
    else
    {
		reg_write_back(R_NUM-1);
        out_str(file_s,"    LOD R%u,R%u\n",R_NUM-1,r);
        reg_clear(r);
		if(a->type==SYM_VAR)
        	out_str(file_s,"    OUTN\n");
		else if(a->type==SYM_TEXT)
			out_str(file_s,"    OUTS\n");
    }
}