%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

int yylex(void);
void yyerror(char* msg);

// ===== break label stack for nested loops =====
#define BREAK_LABEL_STACK_SIZE 64
SYM* break_label_stack[BREAK_LABEL_STACK_SIZE];
int break_label_top = -1;
void push_break_label(SYM* label) {
    if (break_label_top < BREAK_LABEL_STACK_SIZE - 1)
        break_label_stack[++break_label_top] = label;
    else {
        fprintf(stderr, "break label stack overflow\n");
        exit(1);
    }
}
SYM* top_break_label() {
    if (break_label_top >= 0)
        return break_label_stack[break_label_top];
    return NULL;
}
void pop_break_label() {
    if (break_label_top >= 0)
        break_label_top--;
}
// ===== end break label stack =====
%}

// Add debug directive
%debug

%union {
  int     type;
  int     value;
  char   *string;
  float   float_value;
  SYM    *sym;
  TAC    *tac;
  EXP    *exp;
}

%token <string> IDENTIFIER STRING_LITERAL
%token <string> INTEGER
%token <string> FLOAT_LITERAL
%token <value>  BOOL_LITERAL
%token TYPE_INT TYPE_FLOAT TYPE_BOOL TYPE_STRING CONST
%token IF ELSE WHILE FOR BREAK CONTINUE RETURN
%token FUNCTION VOID INPUT OUTPUT
%token AND OR NOT EQ NE LE GE
%token INC DEC ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN

%start program

%type <tac>
    program
    global_items global_item function_def
    statement_list statement compound_statement
    selection_statement iteration_statement jump_statement io_statement
    parameter_list

%type <exp>
    var_declaration init_declarator init_declarator_list expression
    expression_statement function_call argument_list
    assignment_expression logical_expression equality_expression
    relational_expression additive_expression multiplicative_expression
    primary_expression postfix_expression array_index unary_expression

%type <sym>  lvalue
%type <type> type_specifier
%type <value> const_qualifier

%right '='
%right ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%left OR
%left AND
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right NOT
%right INC DEC
%left '[' ']' '('

%%

program:
    global_items {
        tac_last = $1;
        tac_complete();
    }
;

global_items:
                  { $$ = NULL; }
  | global_items global_item { $$ = join_tac($1, $2); }
;

global_item:
    var_declaration       { $$ = $1->tac; }
  | function_def          { $$ = $1; }
;

type_specifier:
    TYPE_INT      { $$ = INT_TYPE; }
  | TYPE_FLOAT    { $$ = FLOAT_TYPE; }
  | TYPE_BOOL     { $$ = BOOL_TYPE; }
  | TYPE_STRING   { $$ = STRING_TYPE; }
;

const_qualifier:
  { $$ = 0; }
  | CONST    { $$ = 1; }
;

var_declaration:
    const_qualifier type_specifier init_declarator_list ';' {
        add_type($2, $3);
        if ($1) {
            for (EXP* e = $3; e != NULL; e = e->next) {
                e->ret->isConst = 1;
            }
        }
        $$ = mk_exp(NULL, do_declaration($3), NULL);
    }
;

init_declarator_list:
    init_declarator                           { $$ = $1; }
    | init_declarator ',' init_declarator_list   { $1->next = $3; $$ = $1; }
;

init_declarator:
    IDENTIFIER {
        $$ = mk_exp(do_var($1), NULL, NULL);
    }
  | IDENTIFIER '=' expression {
        SYM* sym = do_init_var($1, 0, UNDEF_TYPE);
        $$ = mk_exp(sym, do_assign(sym, $3), NULL);
    }
  | IDENTIFIER '[' INTEGER ']' {
        $$ = mk_exp(mk_array($1, atoi($3)), NULL, NULL);
    }
;

function_def:
    FUNCTION type_specifier IDENTIFIER '(' parameter_list ')' {
        // Create function symbol in global scope
        scope = 0;
        TAC* func = declare_func($3, $5);
        // Then switch to local scope for function body
        scope = 1; 
        sym_tab_local = NULL;
        $<tac>$ = func;  // Pass function declaration to body
    } compound_statement {
        // Complete function definition with body
        $$ = do_func($2, $<tac>7, $8);
        // Reset back to global scope after function
        scope = 0;
        sym_tab_local = NULL;
    }
  | FUNCTION VOID IDENTIFIER '(' parameter_list ')' {
        // Create function symbol in global scope
        scope = 0;
        TAC* func = declare_func($3, $5);
        // Then switch to local scope for function body
        scope = 1; 
        sym_tab_local = NULL;
        $<tac>$ = func;  // Pass function declaration to body
    } compound_statement {
        // Complete function definition with body
        $$ = do_func(UNDEF_TYPE, $<tac>7, $8);
        // Reset back to global scope after function
        scope = 0;
        sym_tab_local = NULL;
    }
;

parameter_list:
                                   { $$ = NULL; }
  | type_specifier IDENTIFIER                     { $$ = declare_para($2, $1); }
  | parameter_list ',' type_specifier IDENTIFIER  { $$ = join_tac($1, declare_para($4, $3)); }
;

compound_statement:
    '{' '}'                    { $$ = NULL; }
  | '{' statement_list '}'     { $$ = $2; }
;

statement_list:
    statement                  { $$ = $1; }
  | statement_list statement   { $$ = join_tac($1, $2); }
;

statement:
    expression_statement       { $$ = $1->tac; }
  | compound_statement         { $$ = $1; }
  | selection_statement        { $$ = $1; }
  | iteration_statement        { $$ = $1; }
  | jump_statement             { $$ = $1; }
  | var_declaration            { $$ = $1->tac; }
  | io_statement               { $$ = $1; }
;

expression_statement:
    ';'                        { $$ = mk_exp(NULL, NULL, NULL); }
  | expression ';'             { $$ = $1; }
;

selection_statement:
    IF '(' expression ')' statement {
        $$ = do_if($3, $5);
    }
  | IF '(' expression ')' statement ELSE statement {
        $$ = do_if_else($3, $5, $7);
    }
;

iteration_statement:
    WHILE '(' expression ')' {
        SYM* end_label = mk_label(NULL);
        push_break_label(end_label);
        $<sym>$ = end_label;  // 保存标签以供后续使用
    } statement {
        TAC* tac = do_while($3, $6, $<sym>5);
        pop_break_label();
        $$ = tac;
    }
  | FOR '(' expression_statement expression_statement expression ')' {
        SYM* end_label = mk_label(NULL);
        push_break_label(end_label);
        // 不赋值 $$
    } statement {
        TAC* tac = do_for($3->tac, $4, $5->tac, $8, $<sym>7);
        pop_break_label();
        $$ = tac;
    }
  | FOR '(' var_declaration expression_statement expression ')' {
        SYM* end_label = mk_label(NULL);
        push_break_label(end_label);
        // 不赋值 $$
    } statement {
        TAC* tac = do_for($3->tac, $4, $5->tac, $8, $<sym>7);
        pop_break_label();
        $$ = tac;
    }
;

jump_statement:
    RETURN ';'                 { $$ = do_return(NULL); }
  | RETURN expression ';'      { $$ = do_return($2); }
  | BREAK ';'                  {
        SYM* label = top_break_label();
        if (!label) {
            error("break 不在循环中");
            $$ = NULL;
        } else {
            // 创建一个指向 break 标签的 goto
            $$ = mk_tac(TAC_GOTO, label, NULL, NULL, yylineno);
        }
    }
  | CONTINUE ';'               { /* 简化版不处理 */ $$ = NULL; }
;

io_statement:
    INPUT IDENTIFIER ';'       { $$ = do_input($2); }
  | OUTPUT expression ';'      { $$ = do_output($2); }
;

expression:
    assignment_expression      { $$ = $1; }
;

assignment_expression:
    logical_expression         { $$ = $1; }
  | lvalue '=' expression      { $$ = mk_exp($1, do_assign($1, $3), NULL); }
  | array_index '=' expression {
        SYM* arr = $1->ret->address;
        EXP* idx = $1->ret->etc;
        TAC* tac = do_array_assign(arr, idx, $3);
        $$ = mk_exp($3->ret, join_tac(join_tac($1->tac, $3->tac), tac), NULL);
    }
  | lvalue ADD_ASSIGN expression {
        EXP* tmp = do_bin(TAC_ADD, mk_exp($1, NULL, NULL), $3);
        $$ = mk_exp($1, do_assign($1, tmp), NULL);
    }
  | lvalue SUB_ASSIGN expression {
        EXP* tmp = do_bin(TAC_SUB, mk_exp($1, NULL, NULL), $3);
        $$ = mk_exp($1, do_assign($1, tmp), NULL);
    }
  | lvalue MUL_ASSIGN expression {
        EXP* tmp = do_bin(TAC_MUL, mk_exp($1, NULL, NULL), $3);
        $$ = mk_exp($1, do_assign($1, tmp), NULL);
    }
  | lvalue DIV_ASSIGN expression {
        EXP* tmp = do_bin(TAC_DIV, mk_exp($1, NULL, NULL), $3);
        $$ = mk_exp($1, do_assign($1, tmp), NULL);
    }
  | lvalue MOD_ASSIGN expression {
        EXP* tmp = do_bin(TAC_MOD, mk_exp($1, NULL, NULL), $3);
        $$ = mk_exp($1, do_assign($1, tmp), NULL);
    }
;

logical_expression:
    equality_expression        { $$ = $1; }
  | logical_expression AND equality_expression { $$ = do_logic(TAC_AND, $1, $3); }
  | logical_expression OR equality_expression  { $$ = do_logic(TAC_OR, $1, $3); }
;

equality_expression:
    relational_expression      { $$ = $1; }
  | equality_expression EQ relational_expression { $$ = do_cmp(TAC_EQ, $1, $3); }
  | equality_expression NE relational_expression { $$ = do_cmp(TAC_NE, $1, $3); }
;

relational_expression:
    additive_expression        { $$ = $1; }
  | relational_expression '<' additive_expression { $$ = do_cmp(TAC_LT, $1, $3); }
  | relational_expression '>' additive_expression { $$ = do_cmp(TAC_GT, $1, $3); }
  | relational_expression LE additive_expression  { $$ = do_cmp(TAC_LE, $1, $3); }
  | relational_expression GE additive_expression  { $$ = do_cmp(TAC_GE, $1, $3); }
;

additive_expression:
    multiplicative_expression  { $$ = $1; }
  | additive_expression '+' multiplicative_expression { $$ = do_bin(TAC_ADD, $1, $3); }
  | additive_expression '-' multiplicative_expression { $$ = do_bin(TAC_SUB, $1, $3); }
;

multiplicative_expression:
    unary_expression           { $$ = $1; }
  | multiplicative_expression '*' unary_expression { $$ = do_bin(TAC_MUL, $1, $3); }
  | multiplicative_expression '/' unary_expression { $$ = do_bin(TAC_DIV, $1, $3); }
  | multiplicative_expression '%' unary_expression { $$ = do_bin(TAC_MOD, $1, $3); }
;

unary_expression:
    postfix_expression         { $$ = $1; }
  | '-' unary_expression       {
        SYM* tmp = mk_tmp();
        tmp->varType = INT_TYPE;
        TAC* tac = join_tac(mk_tac(TAC_VAR,tmp,NULL,NULL, yylineno),join_tac($2->tac, mk_tac(TAC_NEG, tmp, $2->ret, NULL, yylineno)));
        $$ = mk_exp(tmp, tac, NULL);
    }
  | NOT unary_expression       { $$ = do_not($2); }
  | INC lvalue                 {
        SYM* one = mk_const(1);
        EXP* tmp = do_bin(TAC_ADD, mk_exp($2, NULL, NULL), mk_exp(one, NULL, NULL));
        TAC* tac = join_tac(tmp->tac, do_assign($2, tmp));
        $$ = mk_exp($2, tac, NULL);
    }
  | DEC lvalue                 {
        SYM* one = mk_const(1);
        EXP* tmp = do_bin(TAC_SUB, mk_exp($2, NULL, NULL), mk_exp(one, NULL, NULL));
        TAC* tac = join_tac(tmp->tac, do_assign($2, tmp));
        $$ = mk_exp($2, tac, NULL);
    }
;

postfix_expression:
    primary_expression         { $$ = $1; }
  | array_index                { $$ = $1; }
  | function_call              { $$ = $1; }
  | lvalue INC                 {
        SYM* tmp = mk_tmp();
        SYM* one = mk_const(1);
        TAC* tac = join_tac(mk_tac(TAC_VAR,tmp,NULL,NULL, yylineno),mk_tac(TAC_COPY, tmp, $1, NULL, yylineno));
        EXP* inc = do_bin(TAC_ADD, mk_exp($1, NULL, NULL), mk_exp(one, NULL, NULL));
        tac = join_tac(tac, inc->tac);
        tac = join_tac(tac, do_assign($1, inc));
        $$ = mk_exp(tmp, tac, NULL);
    }
  | lvalue DEC                 {
        SYM* tmp = mk_tmp();
        SYM* one = mk_const(1);
        TAC* tac = join_tac(mk_tac(TAC_VAR,tmp,NULL,NULL, yylineno),mk_tac(TAC_COPY, tmp, $1, NULL, yylineno));
        EXP* dec = do_bin(TAC_SUB, mk_exp($1, NULL, NULL), mk_exp(one, NULL, NULL));
        tac = join_tac(tac, dec->tac);
        tac = join_tac(tac, do_assign($1, dec));
        $$ = mk_exp(tmp, tac, NULL);
    }
;

primary_expression:
    IDENTIFIER                 { $$ = mk_exp(get_var($1), NULL, NULL); }
  | INTEGER                    { $$ = mk_exp(mk_const(atoi($1)), NULL, NULL); }
  | FLOAT_LITERAL              { $$ = mk_exp(mk_float_const(atof($1)), NULL, NULL); }
  | BOOL_LITERAL               { $$ = do_bool_literal($1); }
  | STRING_LITERAL             { $$ = mk_exp(mk_text($1), NULL, NULL); }
  | '(' expression ')'         { $$ = $2; }
;

array_index:
    IDENTIFIER '[' expression ']' {
        SYM* array = lookup_sym($1);
        if (array == NULL) {
            error("变量未定义: %s", $1);
            $$ = NULL;
        } else if (array->type != SYM_ARRAY) {
            error("变量不是数组: %s", $1);
            $$ = NULL;
        } else {
            $$ = do_array_index(array, $3);
        }
    }
;

function_call:
    IDENTIFIER '(' ')'               { $$ = do_call_ret($1, NULL); }
  | IDENTIFIER '(' argument_list ')' { $$ = do_call_ret($1, $3); }
;

argument_list:
    expression                        { $$ = $1; }
  | expression ',' argument_list      { $1->next = $3; $$ = $1; }
;

lvalue:
    IDENTIFIER                        { $$ = get_var($1); }
;

%%

void yyerror(char* msg) {
    fprintf(stderr, "%s: 第 %d 行\n", msg, yylineno);
    exit(1);
}
