#include"tac.h"
#include"obj.h"

int* reg_alloc_3(SYM* sym1,SYM* sym2,SYM* sym3)
{
    int* r=(int*)malloc(sizeof(int)*3);
    r[0]=r[1]=r[2]=-1;
    while(r[0]==r[1]||r[1]==r[2]||r[0]==r[2])
    {
        r[0]=reg_alloc(sym1);
        r[1]=reg_alloc(sym2);
        r[2]=reg_alloc(sym3);
    }
    return r;
}

int* reg_alloc_2(SYM* sym1,SYM* sym2)
{
    int* r=(int*)malloc(sizeof(int)*2);
    r[0]=r[1]=2;
    while(r[0]==r[1])
    {
        r[0]=reg_alloc(sym1);
        r[1]=reg_alloc(sym2);
    }
    return r;
}

//算术运算和逻辑运算
void asm_bin(TAC* tac)
{
    SYM* a=tac->a;
    SYM* b=tac->b;
    SYM* c=tac->c;
    int op=tac->op;
    int* r=reg_alloc_3(a,b,c);
    out_str(file_s,"    LOD R%u,R%u\n",r[0],r[1]);
    switch (op)
    {
        case TAC_ADD:
            out_str(file_s,"    ADD R%u,R%u\n",r[0],r[2]);
            break;
        
        case TAC_SUB:
            out_str(file_s,"    SUB R%u,R%u\n",r[0],r[2]);
            break;
        
        case TAC_MUL:
            out_str(file_s,"    MUL R%u,R%u\n",r[0],r[2]);
            break;
        
        case TAC_DIV:
            out_str(file_s,"    DIV R%u,R%u\n",r[0],r[2]);
            break;
        
        default:
            error("instruction not defined!\n");
            break;
    }
    reg_fill(a,r[0],MODIFIED);
}

//比较运算
void asm_cmp(TAC* tac)
{
    SYM* a=tac->a;
    SYM* b=tac->b;
    SYM* c=tac->c;
    int op=tac->op;
    int *r=reg_alloc_3(a,b,c);
    out_str(file_s,"    LOD R%u,R%u\n",r[0],r[1]);
    out_str(file_s,"    SUB R%u,R%u\n",r[0],r[2]);
    out_str(file_s,"    TST R%u\n",r[0]);
    switch (op)
    {
        case TAC_EQ:
            out_str(file_s,"    LOD R%u,1\n",r[0]);
            out_str(file_s,"    LOD R3,R1+24\n");
            out_str(file_s,"    JEZ R3\n");
            out_str(file_s,"    LOD R%u,0\n",r[0]);
            break;
        
        case TAC_NE:
            out_str(file_s,"    LOD R%u,0\n",r[0]);
            out_str(file_s,"    LOD R3,R1+24\n");
            out_str(file_s,"    JEZ R3\n");
            out_str(file_s,"    LOD R%u,1\n",r[0]);
            break;
        
        case TAC_LT:
            out_str(file_s,"    LOD R%u,1\n",r[0]);
            out_str(file_s,"    LOD R3,R1+24\n");
            out_str(file_s,"    JLZ R3\n");
            out_str(file_s,"    LOD R%u,0\n",r[0]);
            break;
        
        case TAC_LE:
            out_str(file_s,"    LOD R%u,0\n",r[0]);
            out_str(file_s,"    LOD R3,R1+24\n");
            out_str(file_s,"    JGZ R3\n");
            out_str(file_s,"    LOD R%u,1\n",r[0]);
            break;

        case TAC_GT:
            out_str(file_s,"    LOD R%u,1\n",r[0]);
            out_str(file_s,"    LOD R3,R1+24\n");
            out_str(file_s,"    JGZ R3\n");
            out_str(file_s,"    LOD R%u,0\n",r[0]);
            break;
        
        case TAC_GE:
            out_str(file_s,"    LOD R%u,0\n",r[0]);
            out_str(file_s,"    LOD R3,R1+24\n");
            out_str(file_s,"    JLZ R3\n");
            out_str(file_s,"    LOD R%u,1\n",r[0]);
            break;

        default:
            error("instruction not defined!\n");
            break;
    }
    reg_fill(a,r[0],MODIFIED);
}

//return语句
void asm_return(TAC* tac)
{
    SYM* a=tac->a;
    if(a!=NULL)
    {
        int r=reg_alloc(a);
        reg_fill(a,r,UNMODIFIED);
        out_str(file_s,"    LOD R%u,R%u\n",R_TP,r);
    }
    out_str(file_s,"    LOD R%u,(R%u+4)\n",R_JP,R_BP);
    out_str(file_s,"    LOD R%u,(R%u)\n",R_BP,R_BP);
    out_str(file_s,"    JMP R%u\n",R_JP);
}

//函数调用
void asm_call(TAC*tac)
{
    //a=call b
    for(int i=R_GEN;i<R_NUM;i++)
    {
		reg_write_back(i);
		reg_clear(i);
	}
    SYM* a=tac->a;
    SYM* b=tac->b;
    oof=LOCAL_OFF;
    out_str(file_s,"    LOD R%u,R%u+%d\n",R_TP,R_IP,40);
    out_str(file_s,"    STO (R%u+%u),R%u\n",R_BP,oon+tof+4,R_TP);//保存返回地址
    out_str(file_s,"    STO (R%u+%u),R%u\n",R_BP,oon+tof,R_BP);//保存动态链接
    out_str(file_s,"    ADD R%u,%d\n",R_BP,oon+tof);
    out_str(file_s,"    JMP %s\n",b->name);
    int r=reg_alloc(a);
    out_str(file_s,"    LOD R%u,R%u\n",r,R_TP);
    reg_fill(a,r,MODIFIED);
    oon=0;
}

//实参入栈
void asm_actual(TAC* tac)
{
    SYM* a=tac->a;
    int r=reg_alloc(a);
    reg_fill(a,r,MODIFIED);
    out_str(file_s,"    STO (R%u+%d),R%u\n",R_BP,tof+oon,r);
	oon+=4;
}

//形参读取offset值
void asm_formal(TAC* tac)
{
    SYM* a=tac->a;
    //int r=reg_alloc(a);
    //rdesc_fill(r,a,MODIFIED);
    a->offset=oof;
	a->scope=1;
    //out_str(file_s,"    LOD R%u,(R%u+%u)\n",r,R_BP,oof);
    oof-=4;
}

//begin,跳转需修改tof,oof等
void asm_beginfunc(TAC* tac)
{
    tof=LOCAL_OFF;
    oof=FORMAL_OFF;
    scope=1;
}

//end,返回时需修改tof,oof等
void asm_endfunc(TAC* tac)
{
    asm_return(tac);
    scope=0;
}