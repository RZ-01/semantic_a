%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

int yylex();
void yyerror(char* msg);

%}

%union
{
  int type;
  char *string;
  SYM *sym;
  TAC *tac;
  EXP	*exp;
}

%token<string>IDENTIFIER INTEGER TYPE_INTEGER TEXT TYPE_DOUBLE TYPE_CHAR TYPE_VOID
%type<type>declaration_specifiers
%type<tac>function_declarator parameter_list parameter function_definition block function_declaration declaration statement sentences if_statement elif return_statement while_statement output_statement input_statement for_statement
%type<exp>expression argument_list argument call_expression identifier identifier_list assignment_statement
%type<sym> assignable

%token IF ELSEIF ELSE RETURN INPUT OUTPUT WHILE EQ NEQ GE LE CALL FOR

%left '.'
%right '='
%nonassoc EQ NEQ GE LE '>' '<'
%left '+' '-'
%left '*' '/'

%%

start:function_declaration{
  tac_last=$1;
  tac_complete();
}
;

function_declaration:function_declaration function_definition{
  $$=join_tac($1,$2);
}
|function_declaration declaration{
  $$=join_tac($1,$2);
}
|function_definition{
  $$=$1;
}
|declaration{
  $$=$1;
}
;


function_definition:declaration_specifiers function_declarator block{
  scope=0;
  $$=do_func($1,$2,$3);
}
;

function_declarator:IDENTIFIER '(' parameter_list ')'{
  $$=declare_func($1,$3);
  scope=1;
  sym_tab_local=NULL;
}
|IDENTIFIER '(' ')'{
  $$=declare_func($1,NULL);
  scope=1;
  sym_tab_local=NULL;
}
;

parameter_list:parameter_list ',' parameter{
  $$=join_tac($1,$3);
}
|parameter{
  $$=$1;
}
;

parameter:declaration_specifiers IDENTIFIER{
  $$=declare_para($2,$1);
}
;


declaration_specifiers:TYPE_INTEGER{
  $$=INT_TYPE;
}
|TYPE_DOUBLE{
  $$=DOUBLE_TYPE;
}
|TYPE_CHAR{
  $$=CHAR_TYPE;
}
|TYPE_VOID{
  $$=VOID_TYPE;
}
;

declaration:declaration_specifiers identifier_list ';'{
  add_type($1,$2->ret);
  $$=do_declaration($2);
}
;

identifier_list:identifier_list ',' identifier{
  $3->next=$1;
  $$=$3;
}
|identifier{
  $$=$1;
}
;

identifier:IDENTIFIER{
  $$=mk_exp(do_var($1),NULL,NULL);
}
|IDENTIFIER '=' expression{
  SYM* sym=do_init_var($1,$3->ret->value);
  $$=mk_exp(sym,do_assign(sym,$3),NULL);
}
;

sentences:statement{
  $$=$1;
}
|declaration{
  $$=$1;
}
|sentences statement{
  $$=join_tac($1,$2);
}
|sentences declaration{
  $$=join_tac($1,$2);
}
;

block:'{' sentences '}'{
  $$=$2;
}
|'{' '}'{
  $$=NULL;
}
;

statement:if_statement{
  $$=$1;
}
|return_statement ';'{
  $$=$1;
}
|input_statement ';'{
  $$=$1;
}
|output_statement ';'{
  $$=$1;
}
|while_statement{
  $$=$1;
}
|for_statement{
  $$=$1;
}
|block{
  $$=$1;
}
|assignment_statement ';'{
  $$=$1->tac;
}
|expression ';'{
  $$=$1->tac;
}
;

if_statement:IF '(' expression ')' block elif{
  $$=do_if($3,$5,$6);
}
|IF '(' expression ')' block{
  $$=do_if($3,$5,NULL);
}
;

elif:ELSEIF '(' expression ')' block elif{
  $$=do_if($3,$5,$6);
}
|ELSEIF '(' expression ')' block{
  $$=do_if($3,$5,NULL);
}
|ELSE block{
  $$=do_else($2);
}
;

return_statement:RETURN expression{
  $$=do_return($2);
}
;

input_statement:INPUT IDENTIFIER{
  $$=do_input($2);
}
;

output_statement:OUTPUT expression{
  $$=do_output($2);
}
|OUTPUT TEXT{
  SYM* text=mk_text($2);
  $$=do_output(mk_exp(text,NULL,NULL));
}
;

while_statement:WHILE '(' expression ')' block{
  $$=do_while($3,$5);
}
;

for_statement:FOR '(' assignment_statement ';' expression ';' assignment_statement ')' block{
  $$=do_for_loop($3->tac,$5,$7->tac,$9); /* Updated to use do_for_loop */
}
|
FOR '(' declaration ';' expression ';' assignment_statement ')' block{
  $$=do_for_loop($3,$5,$7->tac,$9); /* Updated to use do_for_loop */
}
;

assignment_statement:assignable '=' expression{
  $$=mk_exp($1, do_assign($1,$3), NULL);
}
| assignable '=' assignment_statement {
  $$=mk_exp($1, do_assign($1,$3), NULL);
}
;

assignable:IDENTIFIER{
  $$=get_var($1);
}
;

expression:IDENTIFIER{
  $$=mk_exp(get_var($1),NULL,NULL);
}
| INTEGER{
  $$=mk_exp(mk_const(atoi($1)),NULL,NULL);
}
| expression '+' expression{
  $$=do_bin(TAC_ADD,$1,$3);
}
| expression '-' expression {
  $$=do_bin(TAC_SUB,$1,$3);
}
| expression '*' expression {
  $$=do_bin(TAC_MUL,$1,$3);
}
| expression '/' expression{
  $$=do_bin(TAC_DIV,$1,$3);
}
| '(' expression ')'{
  $$=$2;
}
| expression EQ expression{
  $$=do_cmp(TAC_EQ,$1,$3);
}
| expression NEQ expression{
  $$=do_cmp(TAC_NEG,$1,$3);
}
| expression '>' expression{
  $$=do_cmp(TAC_GT,$1,$3);
}
| expression '<' expression{
  $$=do_cmp(TAC_LT,$1,$3);
}
| expression GE expression{
  $$=do_cmp(TAC_GE,$1,$3);
}
| expression LE expression{
  $$=do_cmp(TAC_LE,$1,$3);
}
| call_expression{
  $$=$1;
}
;

argument_list:argument_list ',' argument{
  $3->next=$1;
  $$=$3;
}
|argument{
  $$=$1;
}
;

argument:expression{
  $$=$1;
}
;

call_expression:CALL IDENTIFIER '(' ')'{
  $$=do_call_ret($2,NULL);
}
|CALL IDENTIFIER '(' argument_list ')'{
  $$=do_call_ret($2,$4);
}
;

%%
	
void yyerror(char* msg) 
{
	printf("%s: line %d\n", msg, yylineno);
	exit(0);
}