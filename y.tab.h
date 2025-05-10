/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRING_LITERAL = 259,          /* STRING_LITERAL  */
    INTEGER = 260,                 /* INTEGER  */
    BOOL_LITERAL = 261,            /* BOOL_LITERAL  */
    TYPE_INT = 262,                /* TYPE_INT  */
    TYPE_FLOAT = 263,              /* TYPE_FLOAT  */
    TYPE_BOOL = 264,               /* TYPE_BOOL  */
    TYPE_STRING = 265,             /* TYPE_STRING  */
    CONST = 266,                   /* CONST  */
    IF = 267,                      /* IF  */
    ELSE = 268,                    /* ELSE  */
    WHILE = 269,                   /* WHILE  */
    FOR = 270,                     /* FOR  */
    BREAK = 271,                   /* BREAK  */
    CONTINUE = 272,                /* CONTINUE  */
    RETURN = 273,                  /* RETURN  */
    FUNCTION = 274,                /* FUNCTION  */
    VOID = 275,                    /* VOID  */
    INPUT = 276,                   /* INPUT  */
    OUTPUT = 277,                  /* OUTPUT  */
    AND = 278,                     /* AND  */
    OR = 279,                      /* OR  */
    NOT = 280,                     /* NOT  */
    EQ = 281,                      /* EQ  */
    NE = 282,                      /* NE  */
    LE = 283,                      /* LE  */
    GE = 284,                      /* GE  */
    INC = 285,                     /* INC  */
    DEC = 286,                     /* DEC  */
    ADD_ASSIGN = 287,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 288,              /* SUB_ASSIGN  */
    MUL_ASSIGN = 289,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 290,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 291               /* MOD_ASSIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define STRING_LITERAL 259
#define INTEGER 260
#define BOOL_LITERAL 261
#define TYPE_INT 262
#define TYPE_FLOAT 263
#define TYPE_BOOL 264
#define TYPE_STRING 265
#define CONST 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define FOR 270
#define BREAK 271
#define CONTINUE 272
#define RETURN 273
#define FUNCTION 274
#define VOID 275
#define INPUT 276
#define OUTPUT 277
#define AND 278
#define OR 279
#define NOT 280
#define EQ 281
#define NE 282
#define LE 283
#define GE 284
#define INC 285
#define DEC 286
#define ADD_ASSIGN 287
#define SUB_ASSIGN 288
#define MUL_ASSIGN 289
#define DIV_ASSIGN 290
#define MOD_ASSIGN 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "custom.y"

  int     type;
  int     value;
  char   *string;
  SYM    *sym;
  TAC    *tac;
  EXP    *exp;

#line 148 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
