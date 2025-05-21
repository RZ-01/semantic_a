#include "tac.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

/* Global variable definitions */
extern FILE *output_file;
int scope = 0, next_tmp = 0, next_label = 0;
SYM *sym_tab_global = NULL, *sym_tab_local = NULL;
TAC *tac_first = NULL, *tac_last = NULL;

/* Initialize compiler environment */
void init() {
    sym_tab_global = NULL;
    sym_tab_local = NULL;
    scope = 0;
    next_tmp = 0;
    next_label = 0;
    tac_first = NULL;
    tac_last = NULL;
}

/* Create symbol table entry */
SYM* mk_sym() {
    SYM* sym = (SYM*)malloc(sizeof(SYM));
    if (!sym) {
        error("Memory allocation failed");
        exit(1);
    }
    memset(sym, 0, sizeof(SYM));
    return sym;
}

/* Get variable */
SYM* get_var(char* name) {
    SYM* sym = lookup_sym(name);
    if (!sym) {
        error("Variable undefined: %s", name);
    } else if (sym->type != SYM_VAR && sym->type != SYM_ARRAY) {
        error("Identifier is not a variable: %s", name);
    }
    return sym;
}

/* Declare function */
TAC* declare_func(char* name, TAC* parameters) {
    SYM* sym = lookup_sym(name);
    
    if (sym == NULL) {
        sym = mk_sym();
        sym->type = SYM_FUNC;
        sym->name = strdup(name);
        sym->scope = 0;
        sym->next = sym_tab_global;
        sym_tab_global = sym;
    } else {
        if (sym->type == SYM_FUNC) {
            error("Function already declared: %s", name);
        } else {
            error("Identifier already in use: %s", name);
        }
    }
    int count = 0;
    TAC* tac=mk_tac(TAC_LABEL, sym, NULL, NULL, yylineno);
    for (TAC* t = parameters; t != NULL; t = t->previous) count++;
    
    if (count > 0) {
        sym->para = (int*)malloc(sizeof(int) * (count + 1));  
        count = 0;
        for (TAC* t = parameters; t != NULL; t = t->previous) {
            sym->para[count++] = t->a->varType;
        }
        sym->para[count] = 0; 
    } else {
        sym->para = NULL;
    }
    
    tac=join_tac(tac,parameters);
    return tac;
}

/* Declare parameter */
TAC* declare_para(char* name, int type) {
    SYM* sym = lookup_sym(name);
    if (sym != NULL && sym->scope == scope) {
        error("Parameter name conflict: %s", name);
    }
    
    sym = mk_sym();
    sym->type = SYM_VAR;
    sym->varType = type;
    sym->name = strdup(name);
    sym->scope = scope;
    insert_sym(sym);
    
    return mk_tac(TAC_FORMAL, sym, NULL, NULL, yylineno);
}

/* Handle function definition */
TAC* do_func(int retType, TAC* func, TAC* codes) {
    SYM* sym;
    TAC* t;
    for (t = func; t->previous != NULL; t = t->previous);
    sym = t->a;
    sym->retType = retType;
    
    TAC* begin = mk_tac(TAC_BEGINFUNC, NULL, NULL, NULL, yylineno);
    TAC* end = mk_tac(TAC_ENDFUNC, NULL, NULL, NULL, yylineno);
    
    TAC* tac = join_tac(func, begin);
    tac = join_tac(tac, codes);
    tac = join_tac(tac, end);
    
    return tac;
}

/* Generate temporary variable */
SYM* mk_tmp() {
    char name[32];
    sprintf(name, "t%d", next_tmp++);
    return do_var(name);
}

/* Generate label */
SYM* mk_label(char* name) {
    char label_name[32];
    int label_no;
    if (name == NULL) {
        label_no = next_label++;
        sprintf(label_name, "L%d", label_no);
        name = label_name;
    } else {
        label_no = -1; // 外部传入名字时不编号
    }
    SYM* sym = mk_sym();
    sym->name = strdup(name);
    sym->label = label_no;
    sym->type = SYM_LABEL;
    return insert_sym(sym);
}

/* Create variable */
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

/* Create and initialize variable */
SYM* do_init_var(char* name, int value, int type) {
    SYM* sym = do_var(name);
    sym->value = value;
    sym->varType = type;
    return sym;
}

/* Create and initialize variable with float value */
SYM* do_init_float_var(char* name, float value, int type) {
    SYM* sym = do_var(name);
    sym->float_value = value;
    sym->varType = type;
    return sym;
}

/* Create three-address code */
TAC* mk_tac(int op, SYM *a, SYM *b, SYM *c, int line) {
    TAC* tac = (TAC*)malloc(sizeof(TAC));
    if (!tac) {
        error("Memory allocation failed");
        exit(1);
    }
    
    tac->op = op;
    tac->a = a;
    tac->b = b;
    tac->c = c;
    tac->line = line;
    tac->next = NULL;
    tac->previous = NULL;
    
    return tac;
}

/* Join TAC lists */
TAC* join_tac(TAC* a, TAC* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    
    TAC* result = b;
    TAC* t = b;
    
    void* visited[1000] = {NULL};
    int visit_count = 0;
    
    while (t->previous != NULL) {
        for (int i = 0; i < visit_count; i++) {
            if (t->previous == visited[i]) {
                t->previous = NULL;
                goto done_searching;  // Exit the loops
            }
        }
        
        if (visit_count < 1000) {
            visited[visit_count++] = t;
        }
        
        t = t->previous;
    }
    
done_searching:
    t->previous = a;
    if (a != NULL) {
        a->next = t;
    }
    
    return result;
}

/* Lookup symbol */
SYM* lookup_sym(char* name) {
    SYM* p = sym_tab_global;
    while (p != NULL) {
        if (p->type == SYM_FUNC && strcmp(p->name, name) == 0) {
            return p;  // Found function
        }
        p = p->next;
    }
    
    if (scope == 1) {
        p = sym_tab_local;
        while (p != NULL) {
            if (strcmp(p->name, name) == 0) {
                return p;  // Found local variable
            }
            p = p->next;
        }
    }
    
    p = sym_tab_global;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) {
            return p;  // Found global variable
        }
        p = p->next;
    }
    
    return NULL;  // Symbol not found
}

/* Insert symbol into symbol table */
SYM* insert_sym(SYM* sym) {
    if (scope == 1) {
        // Local scope
        SYM* p = sym_tab_local;
        while (p != NULL) {
            if (strcmp(p->name, sym->name) == 0 && p->scope == scope) {
                error("Identifier redefined: %s", sym->name);
                return p;
            }
            p = p->next;
        }
        
        sym->next = sym_tab_local;
        sym_tab_local = sym;
    } else {
        // Global scope
        SYM* p = sym_tab_global;
        while (p != NULL) {
            if (strcmp(p->name, sym->name) == 0) {
                error("Identifier redefined: %s", sym->name);
                return p;
            }
            p = p->next;
        }
        
        sym->next = sym_tab_global;
        sym_tab_global = sym;
    }
    
    return sym;
}

SYM* insert_text(SYM* sym) {
    SYM* p = sym_tab_global;
    while (p != NULL) {
        if (strcmp(p->name, sym->name) == 0) {
            return p;
        }
        p = p->next;
    }
        
    sym->next = sym_tab_global;
    sym_tab_global = sym;
    
    return sym;
}

/* 类型转换辅助函数：如需将 sym 转为目标类型，则生成临时变量和 TAC_CAST 指令 */
SYM* insert_type_cast(SYM* src, int targetType, TAC** ptac) {
    if (src->varType == targetType || src->varType == UNDEF_TYPE || targetType == UNDEF_TYPE) {
        return src;
    }
    SYM* tmp = mk_tmp();
    tmp->varType = targetType;
    TAC* cast_tac = mk_tac(TAC_CAST, tmp, src, NULL, yylineno);
    if (ptac) {
        *ptac = join_tac(*ptac, cast_tac);
    }
    return tmp;
}

/* Binary operation */
EXP* do_bin(int binop, EXP *exp1, EXP *exp2) {
    // Allow operations between float and int types
    if ((exp1->ret->varType != INT_TYPE && 
         exp1->ret->varType != FLOAT_TYPE && 
         exp1->ret->varType != UNDEF_TYPE) ||
        (exp2->ret->varType != INT_TYPE && 
         exp2->ret->varType != FLOAT_TYPE && 
         exp2->ret->varType != UNDEF_TYPE)) {
        error("Type error: Binary operations only support numeric types");
    }
    SYM* tmp = mk_tmp();
    // 如果有 float，结果为 float
    int resultType = (exp1->ret->varType == FLOAT_TYPE || exp2->ret->varType == FLOAT_TYPE) ? FLOAT_TYPE : INT_TYPE;
    tmp->varType = resultType;
    TAC* tac = NULL;
    SYM* left = exp1->ret;
    SYM* right = exp2->ret;
    // 自动类型提升
    if (left->varType != resultType) {
        left = insert_type_cast(left, resultType, &tac);
    }
    if (right->varType != resultType) {
        right = insert_type_cast(right, resultType, &tac);
    }
    tac = join_tac(tac, mk_tac(TAC_VAR, tmp, NULL, NULL, yylineno));
    tac = join_tac(tac, mk_tac(binop, tmp, left, right, yylineno));
    tac = join_tac(join_tac(exp1->tac, exp2->tac), tac);
    return mk_exp(tmp, tac, NULL);
}

/* Create expression */
EXP* mk_exp(SYM* ret, TAC* tac, EXP* next) {
    EXP* exp = (EXP*)malloc(sizeof(EXP));
    if (!exp) {
        error("Memory allocation failed");
        exit(1);
    }
    
    exp->ret = ret;
    exp->tac = tac;
    exp->next = next;
    exp->etc = NULL;
    
    return exp;
}

/* Comparison operation */
EXP* do_cmp(int binop, EXP *exp1, EXP *exp2) {
    // Allow comparisons between float and int types
    if ((exp1->ret->varType != INT_TYPE && 
         exp1->ret->varType != FLOAT_TYPE && 
         exp1->ret->varType != UNDEF_TYPE) ||
        (exp2->ret->varType != INT_TYPE && 
         exp2->ret->varType != FLOAT_TYPE && 
         exp2->ret->varType != UNDEF_TYPE)) {
        error("Type error: Comparison operations only support numeric types");
    }
    
    SYM* tmp = mk_tmp();
    tmp->varType = BOOL_TYPE;
    
    TAC* tac = join_tac(mk_tac(TAC_VAR,tmp,NULL,NULL, yylineno),join_tac(exp1->tac, exp2->tac));
    tac = join_tac(tac, mk_tac(binop, tmp, exp1->ret, exp2->ret, yylineno));
    
    return mk_exp(tmp, tac, NULL);
}

/* Create floating-point constant */
SYM* mk_float_const(float value) {
    char name[32];
    sprintf(name, "%f", value);
    
    SYM* sym = mk_sym();
    sym->name = strdup(name);
    sym->type = SYM_FLOAT;
    sym->float_value = value;
    sym->varType = FLOAT_TYPE;
    
    SYM* existing = lookup_sym(name);
    if (existing != NULL && existing->type == SYM_FLOAT && existing->float_value == value) {
        free(sym->name);
        free(sym);
        return existing;
    }
    
    return insert_const(sym);
}

/* Function call */
EXP* do_call_ret(char* name, EXP* args) {
    SYM* func = lookup_sym(name);
    if (func == NULL) {
        error("Function undefined: %s", name);
        return NULL;
    }
    if (func->type != SYM_FUNC) {
        error("Identifier is not a function: %s", name);
        return NULL;
    }
    
    SYM* ret = mk_tmp();
    ret->varType = func->retType;
    
    TAC* tac = NULL;
    
    EXP* arg = args;
    int arg_count = 0;
    while (arg != NULL) {
        tac = join_tac(tac, arg->tac);
        arg = arg->next;
        arg_count++;
    }
    
    arg = args;
    while (arg != NULL) {
        tac = join_tac(tac, mk_tac(TAC_ACTUAL, arg->ret, NULL, NULL, yylineno));
        arg = arg->next;
    }
    
    if (func->para != NULL) {
        int param_count = 0;
        while (func->para[param_count] != 0 && param_count < arg_count) {
            param_count++;
        }
        
        if (param_count != arg_count) {
            error("Function %s requires %d parameters, but %d were provided", name, param_count, arg_count);
        }
    }
    
    tac = join_tac(mk_tac(TAC_VAR,ret,NULL,NULL, yylineno),join_tac(tac, mk_tac(TAC_CALL, ret, func, NULL, yylineno)));
    
    return mk_exp(ret, tac, NULL);
}

/* IF statement */
TAC* do_if(EXP *exp, TAC *blk) {
    SYM* label = mk_label(NULL);
    
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_IFZ, label, exp->ret, NULL, yylineno));
    tac = join_tac(tac, blk);
    tac = join_tac(tac, mk_tac(TAC_LABEL, label, NULL, NULL, yylineno));
    
    return tac;
}

/* IF-ELSE statement */
TAC* do_if_else(EXP *exp, TAC *blk1, TAC *blk2) {
    SYM* false_label = mk_label(NULL);
    SYM* end_label = mk_label(NULL);
    
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_IFZ, false_label, exp->ret, NULL, yylineno));
    tac = join_tac(tac, blk1);
    tac = join_tac(tac, mk_tac(TAC_GOTO, end_label, NULL, NULL, yylineno));
    tac = join_tac(tac, mk_tac(TAC_LABEL, false_label, NULL, NULL, yylineno));
    tac = join_tac(tac, blk2);
    tac = join_tac(tac, mk_tac(TAC_LABEL, end_label, NULL, NULL, yylineno));
    
    return tac;
}

/* RETURN statement */
TAC* do_return(EXP* exp) {
    if (exp == NULL) {
        return mk_tac(TAC_RETURN, NULL, NULL, NULL, yylineno);
    }
    
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_RETURN, exp->ret, NULL, NULL, yylineno));
    
    return tac;
}

/* INPUT statement */
TAC* do_input(char* name) {
    SYM* sym = lookup_sym(name);
    if (sym == NULL) {
        error("Variable undefined: %s", name);
        return NULL;
    }
    
    return mk_tac(TAC_INPUT, sym, NULL, NULL, yylineno);
}

/* OUTPUT statement */
TAC* do_output(EXP* exp) {
    if (exp == NULL) {
        return NULL;
    }
    
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_OUTPUT, exp->ret, NULL, NULL, yylineno));
    
    return tac;
}

/* WHILE loop */
TAC* do_while(EXP* exp, TAC* body, SYM* break_label) {
    SYM* start_label = mk_label(NULL);
    if (!break_label) {
        break_label = mk_label(NULL);
    }
    
    TAC* tac = mk_tac(TAC_LABEL, start_label, NULL, NULL, yylineno);
    tac = join_tac(tac, exp->tac);
    tac = join_tac(tac, mk_tac(TAC_IFZ, break_label, exp->ret, NULL, yylineno));
    TAC* current = body;
    while (current != NULL) {
        if (current->op == TAC_GOTO && current->a == NULL) {
            current->a = break_label;
        }
        current = current->next;
    }
    SYM* inner_break = lookup_sym("L1");
    if (!inner_break) {
        inner_break = mk_label("L1");
    }
    
    tac = join_tac(tac, body);
    tac = join_tac(tac, mk_tac(TAC_GOTO, start_label, NULL, NULL, yylineno));
    tac = join_tac(tac, mk_tac(TAC_LABEL, break_label, NULL, NULL, yylineno));
    
    return tac;
}

/* Assignment statement */
TAC* do_assign(SYM *var, EXP *exp) {
    if (var->isConst) {
        error("Cannot modify constant variable: %s", var->name);
    }
    if (var->varType != UNDEF_TYPE && exp->ret->varType != UNDEF_TYPE && var->varType != exp->ret->varType) {
        // 支持 int/float 自动转换
        if ((var->varType == FLOAT_TYPE && exp->ret->varType == INT_TYPE) ||
            (var->varType == INT_TYPE && exp->ret->varType == FLOAT_TYPE)) {
            SYM* casted = insert_type_cast(exp->ret, var->varType, &exp->tac);
            TAC* tac = exp->tac;
            tac = join_tac(tac, mk_tac(TAC_COPY, var, casted, NULL, yylineno));
            return tac;
        } else {
            error("Type mismatch: Variable %s is of type %d, but expression is of type %d", var->name, var->varType, exp->ret->varType);
        }
    }
    TAC* tac = exp->tac;
    tac = join_tac(tac, mk_tac(TAC_COPY, var, exp->ret, NULL, yylineno));
    return tac;
}

/* Add type */
void add_type(int type, EXP* exp_list) {
    for (EXP* e = exp_list; e != NULL; e = e->next) {
        if (e->ret) {
            e->ret->varType = type;
        }
    }
}

/* Declaration statement */
TAC* do_declaration(EXP* exp_list) {
    if (exp_list == NULL) return NULL;
    
    TAC* tac = NULL;
    
    for (EXP* e = exp_list; e != NULL; e = e->next) {
        if (e->ret) {
            tac = join_tac(tac, mk_tac(TAC_VAR, e->ret, NULL, NULL, yylineno));
            if (e->tac != NULL) {
                tac = join_tac(tac, e->tac);
            }
        }
    }
    
    return tac;
}

/* Create constant */
SYM* mk_const(int value) {
    char name[32];
    sprintf(name, "%d", value);
    
    SYM* sym = mk_sym();
    sym->name = strdup(name);
    sym->type = SYM_INT;
    sym->value = value;
    sym->varType = INT_TYPE;
    
    SYM* existing = lookup_sym(name);
    if (existing != NULL && existing->type == SYM_INT && existing->value == value) {
        free(sym->name);
        free(sym);
        return existing;
    }
    
    return insert_const(sym);
}

/* Insert constant */
SYM* insert_const(SYM* sym) {
    sym->next = sym_tab_global;
    sym_tab_global = sym;
    return sym;
}

/* Create string */
SYM* mk_text(char* text) {
    SYM* sym = mk_sym();
    sym->name = strdup(text);
    sym->type = SYM_TEXT;
    sym->varType = STRING_TYPE;
    sym->label=next_label++;
    
    return insert_text(sym);
}

/* Create array */
SYM* mk_array(char* name, int size) {
    if (size <= 0) {
        error("Array size must be positive");
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

/* Array index */
EXP* do_array_index(SYM* array, EXP* index) {
    if (array->type != SYM_ARRAY) {
        error("Variable is not an array: %s", array->name);
        return NULL;
    }
    // Check if index is an integer
    if (index->ret->varType != INT_TYPE && index->ret->varType != UNDEF_TYPE) {
        error("Array index must be an integer");
    }
    SYM* tmp = mk_tmp();
    tmp->varType = array->varType;
    tmp->address = array; // Save array base address
    tmp->etc = index;     // Save index expression
    TAC* tac = index->tac;
    tac = join_tac(mk_tac(TAC_VAR, tmp, NULL, NULL, yylineno), join_tac(tac, mk_tac(TAC_ARRAY_INDEX, tmp, array, index->ret, yylineno)));
    return mk_exp(tmp, tac, NULL);
}

/* Array assignment */
TAC* do_array_assign(SYM* array, EXP* index, EXP* value) {
    if (array->type != SYM_ARRAY) {
        error("Variable is not an array: %s", array->name);
        return NULL;
    }
    if (array->isConst) {
        error("Cannot modify constant array: %s", array->name);
    }
    if (index->ret->varType != INT_TYPE && index->ret->varType != UNDEF_TYPE) {
        error("Array index must be an integer");
    }
    // 类型自动转换
    SYM* val = value->ret;
    TAC* tac = join_tac(index->tac, value->tac);
    if (array->varType != UNDEF_TYPE && val->varType != UNDEF_TYPE && array->varType != val->varType) {
        if ((array->varType == FLOAT_TYPE && val->varType == INT_TYPE) ||
            (array->varType == INT_TYPE && val->varType == FLOAT_TYPE)) {
            val = insert_type_cast(val, array->varType, &tac);
        } else {
            error("Type mismatch: Array %s element type is %d, but assignment expression type is %d", array->name, array->varType, val->varType);
        }
    }
    tac = join_tac(tac, mk_tac(TAC_ARRAY_ASSIGN, array, index->ret, val, yylineno));
    return tac;
}

/* Create constant variable */
SYM* do_const_var(char* name, int value) {
    SYM* sym = do_var(name);
    sym->isConst = 1;
    sym->value = value;
    return sym;
}

/* Boolean literal */
EXP* do_bool_literal(int value) {
    SYM* sym = mk_tmp();
    sym->varType = BOOL_TYPE;
    sym->value = value ? 1 : 0;
    return mk_exp(sym, mk_tac(TAC_VAR,sym,NULL,NULL, yylineno), NULL);
}

/* Logical operation */
EXP* do_logic(int op, EXP *exp1, EXP *exp2) {
    if (exp1->ret->varType != BOOL_TYPE && exp1->ret->varType != UNDEF_TYPE) {
        error("Type error: Logical operations require boolean type");
    }
    if (exp2->ret->varType != BOOL_TYPE && exp2->ret->varType != UNDEF_TYPE) {
        error("Type error: Logical operations require boolean type");
    }
    
    SYM* tmp = mk_tmp();
    tmp->varType = BOOL_TYPE;
    
    TAC* tac = join_tac(mk_tac(TAC_VAR,tmp,NULL,NULL, yylineno),join_tac(exp1->tac, exp2->tac));
    tac = join_tac(tac, mk_tac(op, tmp, exp1->ret, exp2->ret, yylineno));
    
    return mk_exp(tmp, tac, NULL);
}

/* Logical NOT operation */
EXP* do_not(EXP *exp) {
    if (exp->ret->varType != BOOL_TYPE && exp->ret->varType != UNDEF_TYPE) {
        error("Type error: Logical NOT operation requires boolean type");
    }
    
    SYM* tmp = mk_tmp();
    tmp->varType = BOOL_TYPE;
    
    TAC* tac = join_tac(mk_tac(TAC_VAR,tmp,NULL,NULL, yylineno),exp->tac);
    tac = join_tac(tac, mk_tac(TAC_NOT, tmp, exp->ret, NULL, yylineno));
    
    return mk_exp(tmp, tac, NULL);
}

/* FOR loop */
TAC* do_for(TAC* init, EXP* cond, TAC* update, TAC* body, SYM* break_label) {
    SYM* start_label = mk_label(NULL);
    SYM* cont_label = mk_label(NULL);
    // end_label 由外部传入（break_label）
    TAC* tac = init;
    tac = join_tac(tac, mk_tac(TAC_LABEL, start_label, NULL, NULL, yylineno));
    tac = join_tac(tac, cond->tac);
    tac = join_tac(tac, mk_tac(TAC_IFZ, break_label, cond->ret, NULL, yylineno));
    tac = join_tac(tac, body);
    tac = join_tac(tac, mk_tac(TAC_LABEL, cont_label, NULL, NULL, yylineno));
    tac = join_tac(tac, update);
    tac = join_tac(tac, mk_tac(TAC_GOTO, start_label, NULL, NULL, yylineno));
    tac = join_tac(tac, mk_tac(TAC_LABEL, break_label, NULL, NULL, yylineno));
    return tac;
}

/* Complete TAC generation */
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

void out_str(FILE *f, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(f, format, args);
    va_end(args);
}

/* Output single TAC */
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
            if (tac->a->type == SYM_ARRAY) {
                fprintf(f, "var %s[%d]\n", tac->a->name, tac->a->size);
            } else {
                fprintf(f, "var %s\n", tac->a->name);
            }
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
        case TAC_CAST:
            fprintf(f, "%s = (cast) %s\n", tac->a->name, tac->b->name);
            break;
        default:
            fprintf(f, "Unknown opcode: %d\n", tac->op);
    }
}

/* Output TAC list */
void out_tac_list() {
    if (!output_file) return;
    
    fprintf(output_file, ".code\n");
    for (TAC* tac = tac_first; tac != NULL; tac = tac->next) {
        out_tac(output_file, tac);
    }
}

/* Error handling */
void error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Error: Line %d: ", yylineno);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
