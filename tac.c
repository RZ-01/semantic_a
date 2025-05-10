#include "tac.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

/* 全局变量定义 */
extern FILE *output_file;
int scope = 0, next_tmp = 0, next_label = 0;
SYM *sym_tab_global = NULL, *sym_tab_local = NULL;
TAC *tac_first = NULL, *tac_last = NULL;

/* 初始化编译器环境 */
void init() {
    sym_tab_global = NULL;
    sym_tab_local = NULL;
    scope = 0;
    next_tmp = 0;
    next_label = 0;
    tac_first = NULL;
    tac_last = NULL;
}

/* 创建符号表项 */
SYM* mk_sym() {
    SYM* sym = (SYM*)malloc(sizeof(SYM));
    if (!sym) {
        error("内存分配失败");
        exit(1);
    }
    memset(sym, 0, sizeof(SYM));
    return sym;
}

/* 获取变量 */
SYM* get_var(char* name) {
    SYM* sym = lookup_sym(name);
    if (!sym) {
        error("变量未定义: %s", name);
    } else if (sym->type != SYM_VAR && sym->type != SYM_ARRAY) {
        error("标识符不是变量: %s", name);
    }
    return sym;
}

/* 声明函数 */
TAC* declare_func(char* name, TAC* parameters) {
    SYM* sym = lookup_sym(name);
    
    if (sym == NULL) {
        // Create new function symbol
        sym = mk_sym();
        sym->type = SYM_FUNC;
        sym->name = strdup(name);
        
        // Make sure to set appropriate scope for functions (global)
        sym->scope = 0;
        
        // Add to global symbol table explicitly
        sym->next = sym_tab_global;
        sym_tab_global = sym;
    } else {
        // Function already exists
        if (sym->type == SYM_FUNC) {
            error("函数重复声明: %s", name);
        } else {
            error("标识符已被占用: %s", name);
        }
    }
    
    // Count parameters
    int count = 0;
    for (TAC* t = parameters; t != NULL; t = t->previous) count++;
    
    if (count > 0) {
        sym->para = (int*)malloc(sizeof(int) * (count + 1));  // +1 for terminator
        count = 0;
        for (TAC* t = parameters; t != NULL; t = t->previous) {
            sym->para[count++] = t->a->varType;
        }
        sym->para[count] = 0;  // Terminate the list
    } else {
        sym->para = NULL;
    }
    
    // Create and return function label TAC
    return mk_tac(TAC_LABEL, sym, NULL, NULL);
}

/* 声明参数 */
TAC* declare_para(char* name, int type) {
    SYM* sym = lookup_sym(name);
    if (sym != NULL && sym->scope == scope) {
        error("参数名称冲突: %s", name);
    }
    
    sym = mk_sym();
    sym->type = SYM_VAR;
    sym->varType = type;
    sym->name = strdup(name);
    sym->scope = scope;
    insert_sym(sym);
    
    return mk_tac(TAC_FORMAL, sym, NULL, NULL);
}

/* 处理函数定义 */
TAC* do_func(int retType, TAC* func, TAC* codes) {
    // 找到函数符号
    SYM* sym;
    TAC* t;
    for (t = func; t->previous != NULL; t = t->previous);
    sym = t->a;
    sym->retType = retType;
    
    // 拼接函数相关的TAC
    TAC* begin = mk_tac(TAC_BEGINFUNC, NULL, NULL, NULL);
    TAC* end = mk_tac(TAC_ENDFUNC, NULL, NULL, NULL);
    
    TAC* tac = join_tac(func, begin);
    tac = join_tac(tac, codes);
    tac = join_tac(tac, end);
    
    return tac;
}

/* 生成中间变量 */
SYM* mk_tmp() {
    char name[32];
    sprintf(name, "t%d", next_tmp++);
    return do_var(name);
}

/* 生成标签 */
SYM* mk_label(char* name) {
    char label_name[32];
    if (name == NULL) {
        sprintf(label_name, "L%d", next_label++);
        name = label_name;
    }
    
    SYM* sym = mk_sym();
    sym->name = strdup(name);
    sym->label = next_label;
    sym->type = SYM_LABEL;
    return insert_sym(sym);
}

/* 创建变量 */
SYM* do_var(char* name) {
    SYM* sym = mk_sym();
    sym->name = strdup(name);
    sym->type = SYM_VAR;
    sym->scope = scope;
    sym->value = 0;
    sym->varType = UNDEF_TYPE;
    sym->para = NULL;
    sym->retType = UNDEF_TYPE;
    sym->isConst = 0;
    
    return insert_sym(sym);
}

/* 创建并初始化变量 */
SYM* do_init_var(char* name, int value, int type) {
    SYM* sym = do_var(name);
    sym->value = value;
    sym->varType = type;
    return sym;
}

/* 创建三地址码 */
TAC* mk_tac(int op, SYM *a, SYM *b, SYM *c) {
    TAC* tac = (TAC*)malloc(sizeof(TAC));
    if (!tac) {
        error("内存分配失败");
        exit(1);
    }
    
    tac->op = op;
    tac->a = a;
    tac->b = b;
    tac->c = c;
    tac->next = NULL;
    tac->previous = NULL;
    
    return tac;
}

/* 连接TAC链表 */
TAC* join_tac(TAC* a, TAC* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    
    // Make a defensive copy of pointer b before manipulation
    TAC* result = b;
    TAC* t = b;
    
    // Use a hash table approach to detect cycles (simplified with array)
    void* visited[1000] = {NULL};
    int visit_count = 0;
    
    // Find the head of list b
    while (t->previous != NULL) {
        // Check for cycles
        for (int i = 0; i < visit_count; i++) {
            if (t->previous == visited[i]) {
                // Break the cycle silently instead of reporting error
                t->previous = NULL;
                goto done_searching;  // Exit the loops
            }
        }
        
        // Record visited node
        if (visit_count < 1000) {
            visited[visit_count++] = t;
        }
        
        // Move to previous node if it's safe
        t = t->previous;
    }
    
done_searching:
    // Link the lists
    t->previous = a;
    if (a != NULL) {
        a->next = t;
    }
    
    return result;
}

/* 查找符号 */
SYM* lookup_sym(char* name) {
    // First search for functions in global scope - more explicit search
    SYM* p = sym_tab_global;
    while (p != NULL) {
        if (p->type == SYM_FUNC && strcmp(p->name, name) == 0) {
            return p;  // Found function
        }
        p = p->next;
    }
    
    // Then search local scope for variables if in local scope
    if (scope == 1) {
        p = sym_tab_local;
        while (p != NULL) {
            if (strcmp(p->name, name) == 0) {
                return p;  // Found local variable
            }
            p = p->next;
        }
    }
    
    // Finally search global scope for non-function symbols
    p = sym_tab_global;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) {
            return p;  // Found global variable
        }
        p = p->next;
    }
    
    return NULL;  // Symbol not found
}

/* 插入符号到符号表 */
SYM* insert_sym(SYM* sym) {
    if (scope == 1) {
        // 局部作用域
        SYM* p = sym_tab_local;
        while (p != NULL) {
            if (strcmp(p->name, sym->name) == 0 && p->scope == scope) {
                error("标识符重定义: %s", sym->name);
                return p;
            }
            p = p->next;
        }
        
        // 添加到局部符号表
        sym->next = sym_tab_local;
        sym_tab_local = sym;
    } else {
        // 全局作用域
        SYM* p = sym_tab_global;
        while (p != NULL) {
            if (strcmp(p->name, sym->name) == 0) {
                error("标识符重定义: %s", sym->name);
                return p;
            }
            p = p->next;
        }
        
        // 添加到全局符号表
        sym->next = sym_tab_global;
        sym_tab_global = sym;
    }
    
    return sym;
}

/* 二元运算 */
EXP* do_bin(int binop, EXP *exp1, EXP *exp2) {
    // 类型检查
    if (exp1->ret->varType != INT_TYPE && exp1->ret->varType != UNDEF_TYPE) {
        error("类型错误: 二元运算只支持整型");
    }
    if (exp2->ret->varType != INT_TYPE && exp2->ret->varType != UNDEF_TYPE) {
        error("类型错误: 二元运算只支持整型");
    }
    
    SYM* tmp = mk_tmp();
    tmp->varType = INT_TYPE;
    
    TAC* tac = mk_tac(binop, tmp, exp1->ret, exp2->ret);
    tac = join_tac(exp1->tac, exp2->tac);
    tac = join_tac(tac, mk_tac(binop, tmp, exp1->ret, exp2->ret));
    
    return mk_exp(tmp, tac, NULL);
}

/* 创建表达式 */
EXP* mk_exp(SYM* ret, TAC* tac, EXP* next) {
    EXP* exp = (EXP*)malloc(sizeof(EXP));
    if (!exp) {
        error("内存分配失败");
        exit(1);
    }
    
    exp->ret = ret;
    exp->tac = tac;
    exp->next = next;
    exp->etc = NULL;
    
    return exp;
}

/* 比较操作 */
EXP* do_cmp(int binop, EXP *exp1, EXP *exp2) {
    SYM* tmp = mk_tmp();
    tmp->varType = BOOL_TYPE;
    
    TAC* tac = join_tac(exp1->tac, exp2->tac);
    tac = join_tac(tac, mk_tac(binop, tmp, exp1->ret, exp2->ret));
    
    return mk_exp(tmp, tac, NULL);
}

/* 函数调用 */
EXP* do_call_ret(char* name, EXP* args) {
    SYM* func = lookup_sym(name);
    if (func == NULL) {
        error("函数未定义: %s", name);
        return NULL;
    }
    if (func->type != SYM_FUNC) {
        error("标识符不是函数: %s", name);
        return NULL;
    }
    
    // 创建返回值
    SYM* ret = mk_tmp();
    ret->varType = func->retType;
    
    // 创建函数调用TAC
    TAC* tac = NULL;
    
    // 处理参数
    EXP* arg = args;
    int arg_count = 0;
    
    // 首先收集参数的TAC
    while (arg != NULL) {
        tac = join_tac(tac, arg->tac);
        arg = arg->next;
        arg_count++;
    }
    
    // 然后添加参数传递TAC
    arg = args;
    while (arg != NULL) {
        tac = join_tac(tac, mk_tac(TAC_ACTUAL, arg->ret, NULL, NULL));
        arg = arg->next;
    }
    
    // 函数参数个数检查
    if (func->para != NULL) {
        int param_count = 0;
        while (func->para[param_count] != 0 && param_count < arg_count) {
            param_count++;
        }
        
        if (param_count != arg_count) {
            error("函数 %s 需要 %d 个参数, 但提供了 %d 个", name, param_count, arg_count);
        }
    }
    
    // 最后添加函数调用TAC
    tac = join_tac(tac, mk_tac(TAC_CALL, ret, func, NULL));
    
    return mk_exp(ret, tac, NULL);
}

/* IF 语句 */
TAC* do_if(EXP *exp, TAC *blk) {
    SYM* label = mk_label(NULL);
    
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_IFZ, label, exp->ret, NULL));
    tac = join_tac(tac, blk);
    tac = join_tac(tac, mk_tac(TAC_LABEL, label, NULL, NULL));
    
    return tac;
}

/* IF-ELSE 语句 */
TAC* do_if_else(EXP *exp, TAC *blk1, TAC *blk2) {
    SYM* false_label = mk_label(NULL);
    SYM* end_label = mk_label(NULL);
    
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_IFZ, false_label, exp->ret, NULL));
    tac = join_tac(tac, blk1);
    tac = join_tac(tac, mk_tac(TAC_GOTO, end_label, NULL, NULL));
    tac = join_tac(tac, mk_tac(TAC_LABEL, false_label, NULL, NULL));
    tac = join_tac(tac, blk2);
    tac = join_tac(tac, mk_tac(TAC_LABEL, end_label, NULL, NULL));
    
    return tac;
}

/* RETURN 语句 */
TAC* do_return(EXP* exp) {
    if (exp == NULL) {
        return mk_tac(TAC_RETURN, NULL, NULL, NULL);
    }
    
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_RETURN, exp->ret, NULL, NULL));
    
    return tac;
}

/* INPUT 语句 */
TAC* do_input(char* name) {
    SYM* sym = lookup_sym(name);
    if (sym == NULL) {
        error("变量未定义: %s", name);
        return NULL;
    }
    
    return mk_tac(TAC_INPUT, sym, NULL, NULL);
}

/* OUTPUT 语句 */
TAC* do_output(EXP* exp) {
    if (exp == NULL) {
        return NULL;
    }
    
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_OUTPUT, exp->ret, NULL, NULL));
    
    return tac;
}

/* WHILE 循环 */
TAC* do_while(EXP* exp, TAC* body) {
    SYM* start_label = mk_label(NULL);
    SYM* end_label = mk_label(NULL);
    
    TAC* tac = mk_tac(TAC_LABEL, start_label, NULL, NULL);
    tac = join_tac(tac, exp->tac);
    tac = join_tac(tac, mk_tac(TAC_IFZ, end_label, exp->ret, NULL));
    tac = join_tac(tac, body);
    tac = join_tac(tac, mk_tac(TAC_GOTO, start_label, NULL, NULL));
    tac = join_tac(tac, mk_tac(TAC_LABEL, end_label, NULL, NULL));
    
    return tac;
}

/* 赋值语句 */
TAC* do_assign(SYM *var, EXP *exp) {
    // 类型检查和转换
    if (var->isConst) {
        error("无法修改常量变量: %s", var->name);
    }
    
    if (var->varType != UNDEF_TYPE && exp->ret->varType != UNDEF_TYPE && var->varType != exp->ret->varType) {
        error("类型不匹配: 变量 %s 的类型为 %d, 但表达式类型为 %d", var->name, var->varType, exp->ret->varType);
    }
    
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_COPY, var, exp->ret, NULL));
    
    return tac;
}

/* 添加类型 */
void add_type(int type, EXP* exp_list) {
    for (EXP* e = exp_list; e != NULL; e = e->next) {
        if (e->ret) {
            e->ret->varType = type;
        }
    }
}

/* 声明语句 */
TAC* do_declaration(EXP* exp_list) {
    if (exp_list == NULL) return NULL;
    
    TAC* tac = NULL;
    
    for (EXP* e = exp_list; e != NULL; e = e->next) {
        if (e->ret) {
            tac = join_tac(tac, mk_tac(TAC_VAR, e->ret, NULL, NULL));
            if (e->tac != NULL) {
                tac = join_tac(tac, e->tac);
            }
        }
    }
    
    return tac;
}

/* 创建常量 */
SYM* mk_const(int value) {
    char name[32];
    sprintf(name, "%d", value);
    
    SYM* sym = mk_sym();
    sym->name = strdup(name);
    sym->type = SYM_INT;
    sym->value = value;
    sym->varType = INT_TYPE;
    
    // 检查符号表中是否已存在该常量
    SYM* existing = lookup_sym(name);
    if (existing != NULL && existing->type == SYM_INT && existing->value == value) {
        free(sym->name);
        free(sym);
        return existing;
    }
    
    return insert_const(sym);
}

/* 插入常量 */
SYM* insert_const(SYM* sym) {
    sym->next = sym_tab_global;
    sym_tab_global = sym;
    return sym;
}

/* 创建字符串 */
SYM* mk_text(char* text) {
    SYM* sym = mk_sym();
    sym->name = strdup(text);
    sym->type = SYM_TEXT;
    sym->varType = STRING_TYPE;
    
    return insert_sym(sym);
}

/* 创建数组 */
SYM* mk_array(char* name, int size) {
    if (size <= 0) {
        error("数组大小必须为正数");
        return NULL;
    }
    
    SYM* sym = mk_sym();
    sym->name = strdup(name);
    sym->type = SYM_ARRAY;
    sym->scope = scope;
    sym->size = size;
    sym->varType = UNDEF_TYPE;
    
    return insert_sym(sym);
}

/* 数组索引 */
EXP* do_array_index(SYM* array, EXP* index) {
    if (array->type != SYM_ARRAY) {
        error("变量不是数组: %s", array->name);
        return NULL;
    }
    
    // 检查索引是否为整数
    if (index->ret->varType != INT_TYPE && index->ret->varType != UNDEF_TYPE) {
        error("数组索引必须为整数");
    }
    
    SYM* tmp = mk_tmp();
    tmp->varType = array->varType;
    tmp->address = array; // 保存数组基地址
    tmp->etc = index;     // 保存索引表达式
    
    TAC* tac = index->tac;
    tac = join_tac(tac, mk_tac(TAC_ARRAY_INDEX, tmp, array, index->ret));
    
    return mk_exp(tmp, tac, NULL);
}

/* 数组赋值 */
TAC* do_array_assign(SYM* array, EXP* index, EXP* value) {
    if (array->type != SYM_ARRAY) {
        error("变量不是数组: %s", array->name);
        return NULL;
    }
    
    if (array->isConst) {
        error("无法修改常量数组: %s", array->name);
    }
    
    // 检查索引是否为整数
    if (index->ret->varType != INT_TYPE && index->ret->varType != UNDEF_TYPE) {
        error("数组索引必须为整数");
    }
    
    // 类型检查
    if (array->varType != UNDEF_TYPE && value->ret->varType != UNDEF_TYPE && array->varType != value->ret->varType) {
        error("类型不匹配: 数组 %s 元素类型为 %d, 但赋值表达式类型为 %d", array->name, array->varType, value->ret->varType);
    }
    
    TAC* tac = join_tac(index->tac, value->tac);
    tac = join_tac(tac, mk_tac(TAC_ARRAY_ASSIGN, array, index->ret, value->ret));
    
    return tac;
}

/* 创建常量变量 */
SYM* do_const_var(char* name, int value) {
    SYM* sym = do_var(name);
    sym->isConst = 1;
    sym->value = value;
    return sym;
}

/* 布尔字面量 */
EXP* do_bool_literal(int value) {
    SYM* sym = mk_tmp();
    sym->varType = BOOL_TYPE;
    sym->value = value ? 1 : 0;
    return mk_exp(sym, NULL, NULL);
}

/* 逻辑操作 */
EXP* do_logic(int op, EXP *exp1, EXP *exp2) {
    // 类型检查
    if (exp1->ret->varType != BOOL_TYPE && exp1->ret->varType != UNDEF_TYPE) {
        error("类型错误: 逻辑运算需要布尔类型");
    }
    if (exp2->ret->varType != BOOL_TYPE && exp2->ret->varType != UNDEF_TYPE) {
        error("类型错误: 逻辑运算需要布尔类型");
    }
    
    SYM* tmp = mk_tmp();
    tmp->varType = BOOL_TYPE;
    
    TAC* tac = join_tac(exp1->tac, exp2->tac);
    tac = join_tac(tac, mk_tac(op, tmp, exp1->ret, exp2->ret));
    
    return mk_exp(tmp, tac, NULL);
}

/* 逻辑非操作 */
EXP* do_not(EXP *exp) {
    // 类型检查
    if (exp->ret->varType != BOOL_TYPE && exp->ret->varType != UNDEF_TYPE) {
        error("类型错误: 逻辑非运算需要布尔类型");
    }
    
    SYM* tmp = mk_tmp();
    tmp->varType = BOOL_TYPE;
    
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_NOT, tmp, exp->ret, NULL));
    
    return mk_exp(tmp, tac, NULL);
}

/* FOR 循环 */
TAC* do_for(TAC* init, EXP* cond, TAC* update, TAC* body) {
    SYM* start_label = mk_label(NULL);
    SYM* end_label = mk_label(NULL);
    SYM* cont_label = mk_label(NULL);
    
    TAC* tac = init;
    tac = join_tac(tac, mk_tac(TAC_LABEL, start_label, NULL, NULL));
    tac = join_tac(tac, cond->tac);
    tac = join_tac(tac, mk_tac(TAC_IFZ, end_label, cond->ret, NULL));
    tac = join_tac(tac, body);
    tac = join_tac(tac, mk_tac(TAC_LABEL, cont_label, NULL, NULL));
    tac = join_tac(tac, update);
    tac = join_tac(tac, mk_tac(TAC_GOTO, start_label, NULL, NULL));
    tac = join_tac(tac, mk_tac(TAC_LABEL, end_label, NULL, NULL));
    
    return tac;
}

/* 完成TAC生成 */
void tac_complete() {
    TAC* tac = tac_last;
    if (tac == NULL) return;
    
    tac_last->next = NULL;
    while (tac->previous != NULL) {
        tac->previous->next = tac;
        tac = tac->previous;
    }
    tac_first = tac;
}

/* 输出单条TAC */
void out_tac(FILE* f, TAC* tac) {
    if (!f || !tac) return;
    
    fprintf(f, "%p\t", (void*)tac);
    
    switch (tac->op) {
        case TAC_ADD:
            fprintf(f, "%s = %s + %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_SUB:
            fprintf(f, "%s = %s - %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_MUL:
            fprintf(f, "%s = %s * %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_DIV:
            fprintf(f, "%s = %s / %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_MOD:
            fprintf(f, "%s = %s %% %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_EQ:
            fprintf(f, "%s = %s == %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_NE:
            fprintf(f, "%s = %s != %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_LT:
            fprintf(f, "%s = %s < %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_LE:
            fprintf(f, "%s = %s <= %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_GT:
            fprintf(f, "%s = %s > %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_GE:
            fprintf(f, "%s = %s >= %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_NEG:
            fprintf(f, "%s = -%s\n", tac->a->name, tac->b->name);
            break;
        case TAC_COPY:
            fprintf(f, "%s = %s\n", tac->a->name, tac->b->name);
            break;
        case TAC_GOTO:
            fprintf(f, "goto %s\n", tac->a->name);
            break;
        case TAC_IFZ:
            fprintf(f, "ifz %s goto %s\n", tac->b->name, tac->a->name);
            break;
        case TAC_IFNZ:
            fprintf(f, "ifnz %s goto %s\n", tac->b->name, tac->a->name);
            break;
        case TAC_BEGINFUNC:
            fprintf(f, "begin\n");
            break;
        case TAC_ENDFUNC:
            fprintf(f, "end\n");
            break;
        case TAC_LABEL:
            fprintf(f, "label %s\n", tac->a->name);
            break;
        case TAC_VAR:
            fprintf(f, "var %s\n", tac->a->name);
            break;
        case TAC_FORMAL:
            fprintf(f, "formal %s\n", tac->a->name);
            break;
        case TAC_ACTUAL:
            fprintf(f, "actual %s\n", tac->a->name);
            break;
        case TAC_CALL:
            fprintf(f, "%s = call %s\n", tac->a->name, tac->b->name);
            break;
        case TAC_RETURN:
            if (tac->a)
                fprintf(f, "return %s\n", tac->a->name);
            else
                fprintf(f, "return\n");
            break;
        case TAC_INPUT:
            fprintf(f, "input %s\n", tac->a->name);
            break;
        case TAC_OUTPUT:
            fprintf(f, "output %s\n", tac->a->name);
            break;
        case TAC_AND:
            fprintf(f, "%s = %s && %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_OR:
            fprintf(f, "%s = %s || %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_NOT:
            fprintf(f, "%s = !%s\n", tac->a->name, tac->b->name);
            break;
        case TAC_ARRAY_INDEX:
            fprintf(f, "%s = %s[%s]\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        case TAC_ARRAY_ASSIGN:
            fprintf(f, "%s[%s] = %s\n", tac->a->name, tac->b->name, tac->c->name);
            break;
        default:
            fprintf(f, "未知操作码: %d\n", tac->op);
    }
}

/* 输出TAC列表 */
void out_tac_list() {
    if (!output_file) return;
    
    fprintf(output_file, ".code\n");
    for (TAC* tac = tac_first; tac != NULL; tac = tac->next) {
        out_tac(output_file, tac);
    }
}

/* 错误处理 */
void error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "错误: 行 %d: ", yylineno);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
