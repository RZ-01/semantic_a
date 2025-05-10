%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"
#include "y.tab.h"  

// Add a debug function to trace token recognition
void token_debug(const char* token_name, int token_value) {
    fprintf(stderr, "TOKEN: %s (%d)\n", token_name, token_value);
}
%}

%option yylineno
%option debug

digit       [0-9]
letter      [a-zA-Z]
id          {letter}({letter}|{digit}|_)*
whitespace  [ \t\r\n]+
integer     {digit}+
string      \"[^"]*\"
comment     \/\/.*\n

%%

"int"       { token_debug("TYPE_INT", TYPE_INT); return TYPE_INT; }
"float"     { token_debug("TYPE_FLOAT", TYPE_FLOAT); return TYPE_FLOAT; }
"bool"      { token_debug("TYPE_BOOL", TYPE_BOOL); return TYPE_BOOL; }
"string"    { token_debug("TYPE_STRING", TYPE_STRING); return TYPE_STRING; }
"const"     { token_debug("CONST", CONST); return CONST; }
"if"        { token_debug("IF", IF); return IF; }
"else"      { token_debug("ELSE", ELSE); return ELSE; }
"while"     { token_debug("WHILE", WHILE); return WHILE; }
"for"       { token_debug("FOR", FOR); return FOR; }
"return"    { token_debug("RETURN", RETURN); return RETURN; }
"break"     { token_debug("BREAK", BREAK); return BREAK; }
"continue"  { token_debug("CONTINUE", CONTINUE); return CONTINUE; }
"function"  { token_debug("FUNCTION", FUNCTION); return FUNCTION; }
"void"      { token_debug("VOID", VOID); return VOID; }
"true"      { yylval.value = 1; token_debug("BOOL_LITERAL", BOOL_LITERAL); return BOOL_LITERAL; }
"false"     { yylval.value = 0; token_debug("BOOL_LITERAL", BOOL_LITERAL); return BOOL_LITERAL; }
"input"     { token_debug("INPUT", INPUT); return INPUT; }
"output"    { token_debug("OUTPUT", OUTPUT); return OUTPUT; }

{id}        { yylval.string = strdup(yytext); token_debug("IDENTIFIER", IDENTIFIER); return IDENTIFIER; }
{integer}   { yylval.string = strdup(yytext); token_debug("INTEGER", INTEGER); return INTEGER; }
{string}    { yylval.string = strdup(yytext); token_debug("STRING_LITERAL", STRING_LITERAL); return STRING_LITERAL; }

"++"        { return INC; }
"--"        { return DEC; }
"+="        { return ADD_ASSIGN; }
"-="        { return SUB_ASSIGN; }
"*="        { return MUL_ASSIGN; }
"/="        { return DIV_ASSIGN; }
"%="        { return MOD_ASSIGN; }
"&&"        { return AND; }
"||"        { return OR; }
"=="        { return EQ; }
"!="        { return NE; }
"<="        { return LE; }
">="        { return GE; }
"!"         { return NOT; }

"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"%"         { return '%'; }
"="         { return '='; }
"<"         { return '<'; }
">"         { return '>'; }
"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
"["         { return '['; }
"]"         { return ']'; }
","         { return ','; }
";"         { return ';'; }
":"         { return ':'; }
"."         { return '.'; }

{whitespace} { /* 忽略空白字符 */ }
{comment}    { /* 忽略注释 */ }

.           { fprintf(stderr, "词法错误: 未知字符 '%s' 在第 %d 行\n", yytext, yylineno); exit(1); }

%%

int yywrap(void) {
    return 1;
}
