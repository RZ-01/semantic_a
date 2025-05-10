/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "custom.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

int yylex(void);
void yyerror(char* msg);

#line 81 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 215 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 4,             /* STRING_LITERAL  */
  YYSYMBOL_INTEGER = 5,                    /* INTEGER  */
  YYSYMBOL_BOOL_LITERAL = 6,               /* BOOL_LITERAL  */
  YYSYMBOL_TYPE_INT = 7,                   /* TYPE_INT  */
  YYSYMBOL_TYPE_FLOAT = 8,                 /* TYPE_FLOAT  */
  YYSYMBOL_TYPE_BOOL = 9,                  /* TYPE_BOOL  */
  YYSYMBOL_TYPE_STRING = 10,               /* TYPE_STRING  */
  YYSYMBOL_CONST = 11,                     /* CONST  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_BREAK = 16,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 17,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_FUNCTION = 19,                  /* FUNCTION  */
  YYSYMBOL_VOID = 20,                      /* VOID  */
  YYSYMBOL_INPUT = 21,                     /* INPUT  */
  YYSYMBOL_OUTPUT = 22,                    /* OUTPUT  */
  YYSYMBOL_AND = 23,                       /* AND  */
  YYSYMBOL_OR = 24,                        /* OR  */
  YYSYMBOL_NOT = 25,                       /* NOT  */
  YYSYMBOL_EQ = 26,                        /* EQ  */
  YYSYMBOL_NE = 27,                        /* NE  */
  YYSYMBOL_LE = 28,                        /* LE  */
  YYSYMBOL_GE = 29,                        /* GE  */
  YYSYMBOL_INC = 30,                       /* INC  */
  YYSYMBOL_DEC = 31,                       /* DEC  */
  YYSYMBOL_ADD_ASSIGN = 32,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 33,                /* SUB_ASSIGN  */
  YYSYMBOL_MUL_ASSIGN = 34,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 35,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 36,                /* MOD_ASSIGN  */
  YYSYMBOL_37_ = 37,                       /* '='  */
  YYSYMBOL_38_ = 38,                       /* '<'  */
  YYSYMBOL_39_ = 39,                       /* '>'  */
  YYSYMBOL_40_ = 40,                       /* '+'  */
  YYSYMBOL_41_ = 41,                       /* '-'  */
  YYSYMBOL_42_ = 42,                       /* '*'  */
  YYSYMBOL_43_ = 43,                       /* '/'  */
  YYSYMBOL_44_ = 44,                       /* '%'  */
  YYSYMBOL_45_ = 45,                       /* '['  */
  YYSYMBOL_46_ = 46,                       /* ']'  */
  YYSYMBOL_47_ = 47,                       /* '('  */
  YYSYMBOL_48_ = 48,                       /* ';'  */
  YYSYMBOL_49_ = 49,                       /* ','  */
  YYSYMBOL_50_ = 50,                       /* ')'  */
  YYSYMBOL_51_ = 51,                       /* '{'  */
  YYSYMBOL_52_ = 52,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_global_items = 55,              /* global_items  */
  YYSYMBOL_global_item = 56,               /* global_item  */
  YYSYMBOL_type_specifier = 57,            /* type_specifier  */
  YYSYMBOL_const_qualifier = 58,           /* const_qualifier  */
  YYSYMBOL_var_declaration = 59,           /* var_declaration  */
  YYSYMBOL_init_declarator_list = 60,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 61,           /* init_declarator  */
  YYSYMBOL_function_def = 62,              /* function_def  */
  YYSYMBOL_63_1 = 63,                      /* @1  */
  YYSYMBOL_64_2 = 64,                      /* @2  */
  YYSYMBOL_parameter_list = 65,            /* parameter_list  */
  YYSYMBOL_compound_statement = 66,        /* compound_statement  */
  YYSYMBOL_statement_list = 67,            /* statement_list  */
  YYSYMBOL_statement = 68,                 /* statement  */
  YYSYMBOL_expression_statement = 69,      /* expression_statement  */
  YYSYMBOL_selection_statement = 70,       /* selection_statement  */
  YYSYMBOL_iteration_statement = 71,       /* iteration_statement  */
  YYSYMBOL_jump_statement = 72,            /* jump_statement  */
  YYSYMBOL_io_statement = 73,              /* io_statement  */
  YYSYMBOL_expression = 74,                /* expression  */
  YYSYMBOL_assignment_expression = 75,     /* assignment_expression  */
  YYSYMBOL_logical_expression = 76,        /* logical_expression  */
  YYSYMBOL_equality_expression = 77,       /* equality_expression  */
  YYSYMBOL_relational_expression = 78,     /* relational_expression  */
  YYSYMBOL_additive_expression = 79,       /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 80, /* multiplicative_expression  */
  YYSYMBOL_unary_expression = 81,          /* unary_expression  */
  YYSYMBOL_postfix_expression = 82,        /* postfix_expression  */
  YYSYMBOL_primary_expression = 83,        /* primary_expression  */
  YYSYMBOL_array_index = 84,               /* array_index  */
  YYSYMBOL_function_call = 85,             /* function_call  */
  YYSYMBOL_argument_list = 86,             /* argument_list  */
  YYSYMBOL_lvalue = 87                     /* lvalue  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   300

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  176

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    44,     2,     2,
      47,    50,    42,    40,    49,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
      38,    37,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    77,    78,    82,    83,    88,    89,    90,
      91,    95,    96,   101,   113,   114,   118,   121,   125,   132,
     132,   147,   147,   165,   166,   167,   172,   173,   177,   178,
     182,   183,   184,   185,   186,   187,   188,   192,   193,   198,
     201,   208,   211,   218,   219,   220,   221,   226,   227,   232,
     236,   237,   238,   244,   248,   252,   256,   260,   267,   268,
     269,   273,   274,   275,   279,   280,   281,   282,   283,   287,
     288,   289,   293,   294,   295,   296,   300,   301,   307,   308,
     314,   323,   324,   325,   326,   335,   347,   348,   349,   350,
     351,   355,   370,   371,   375,   376,   380
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "STRING_LITERAL", "INTEGER", "BOOL_LITERAL", "TYPE_INT", "TYPE_FLOAT",
  "TYPE_BOOL", "TYPE_STRING", "CONST", "IF", "ELSE", "WHILE", "FOR",
  "BREAK", "CONTINUE", "RETURN", "FUNCTION", "VOID", "INPUT", "OUTPUT",
  "AND", "OR", "NOT", "EQ", "NE", "LE", "GE", "INC", "DEC", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "'='", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'['", "']'", "'('", "';'",
  "','", "')'", "'{'", "'}'", "$accept", "program", "global_items",
  "global_item", "type_specifier", "const_qualifier", "var_declaration",
  "init_declarator_list", "init_declarator", "function_def", "@1", "@2",
  "parameter_list", "compound_statement", "statement_list", "statement",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "io_statement", "expression", "assignment_expression",
  "logical_expression", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", "unary_expression",
  "postfix_expression", "primary_expression", "array_index",
  "function_call", "argument_list", "lvalue", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-129)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-97)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -129,     9,    10,  -129,  -129,    83,  -129,    89,  -129,  -129,
    -129,  -129,  -129,  -129,    -1,    19,    23,   -17,   -13,   -33,
      11,  -129,    89,    89,   235,    43,  -129,    23,    48,    34,
      38,   253,  -129,  -129,  -129,   235,    52,    52,   235,   235,
    -129,  -129,    90,    80,    18,    82,    -2,  -129,  -129,  -129,
      40,  -129,   165,    25,  -129,  -129,    89,  -129,  -129,   235,
     144,  -129,  -129,   104,  -129,  -129,  -129,  -129,    50,   235,
     235,   235,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,  -129,  -129,   235,   235,   235,   235,   235,
     235,  -129,    99,    53,    53,    63,  -129,    68,    93,  -129,
      80,    80,    18,    18,    82,    82,    82,    82,    -2,    -2,
    -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,
    -129,     2,  -129,  -129,  -129,   235,  -129,    81,   108,   112,
     113,   119,   227,   157,   235,  -129,  -129,  -129,  -129,    64,
    -129,  -129,  -129,  -129,  -129,  -129,   120,  -129,   235,   235,
     231,  -129,  -129,  -129,   128,   129,   130,  -129,  -129,  -129,
     131,   132,   231,  -129,  -129,  -129,   115,   115,   235,   166,
    -129,   134,   115,   115,  -129,  -129
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,    11,     1,    12,     0,     4,     0,     5,     6,
       7,     8,     9,    10,     0,     0,     0,     0,     0,    16,
       0,    14,    23,    23,     0,     0,    13,     0,     0,     0,
       0,    86,    89,    87,    88,     0,     0,     0,     0,     0,
      17,    49,    50,    58,    61,    64,    69,    72,    76,    81,
      82,    83,     0,     0,    15,    24,     0,    21,    19,     0,
       0,    78,    82,     0,    96,    79,    80,    77,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    84,    85,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     0,     0,    92,    94,     0,    90,
      59,    60,    62,    63,    67,    68,    65,    66,    70,    71,
      73,    74,    75,    52,    53,    54,    55,    56,    57,    51,
      25,    11,    22,    20,    91,     0,    93,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    26,    35,    31,    11,
      28,    30,    32,    33,    34,    36,     0,    95,     0,     0,
       0,    45,    46,    43,     0,     0,     0,    27,    29,    38,
       0,     0,     0,    44,    47,    48,    11,    11,     0,    39,
      41,     0,    11,    11,    40,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -129,  -129,  -129,  -129,    -4,  -129,   178,  -129,   160,  -129,
    -129,  -129,   167,    45,  -129,  -128,  -125,  -129,  -129,  -129,
    -129,   -24,  -129,  -129,    72,    86,    78,    87,    -7,  -129,
    -129,   148,  -129,    67,   135
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     6,    28,     7,   137,    20,    21,     9,
      94,    93,    29,   138,   139,   140,   141,   142,   143,   144,
     145,   146,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    98,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      40,    15,    17,    16,    24,    31,    32,    33,    34,     3,
      -2,   158,    25,     4,   127,    68,   128,   129,   130,   131,
     132,     4,    18,   133,   134,   162,    19,    35,    61,     5,
      22,    67,    36,    37,    23,    95,    97,   168,   169,   170,
      79,    80,    81,    38,   174,   175,    73,    74,    53,    39,
     135,    55,    92,   121,   136,    64,    75,    76,   113,    26,
      27,   114,   115,   116,   117,   118,   119,    31,    32,    33,
      34,    91,   110,   111,   112,     4,   127,    82,   128,   129,
     130,   131,   132,    56,    57,   133,   134,    56,    58,    35,
      10,    11,    12,    13,    36,    37,    10,    11,    12,    13,
      99,    97,   120,    14,   121,    38,    71,    72,   154,   124,
     156,    39,   135,    69,    70,   121,   157,   125,    31,    32,
      33,    34,    77,    78,   160,   161,     4,   127,   148,   128,
     129,   130,   131,   132,    83,    84,   133,   134,   122,   123,
      35,   100,   101,   126,   171,    36,    37,    31,    32,    33,
      34,   104,   105,   106,   107,   149,    38,   102,   103,   150,
     155,   151,    39,   135,   108,   109,   121,   152,   159,    35,
      63,    65,    66,    63,    36,    37,   163,   164,   165,   172,
       8,   166,   167,    62,   173,    38,    62,    54,     0,     0,
      30,    39,   147,     0,    96,    83,    84,    85,    86,    87,
      88,    89,    90,     0,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      31,    32,    33,    34,    31,    32,    33,    34,    31,    32,
      33,    34,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,     0,     0,     0,    35,    36,    37,     0,
      35,    36,    37,     0,     0,    36,    37,     0,    38,     0,
       0,     0,    38,     0,    39,   153,    38,     0,    39,   135,
       0,     0,    39,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,     0,     0,     0,     0,     0,     0,     0,    59,     0,
      60
};

static const yytype_int16 yycheck[] =
{
      24,     5,     3,     7,    37,     3,     4,     5,     6,     0,
       0,   139,    45,    11,    12,    39,    14,    15,    16,    17,
      18,    11,     3,    21,    22,   150,     3,    25,    35,    19,
      47,    38,    30,    31,    47,    59,    60,   162,   166,   167,
      42,    43,    44,    41,   172,   173,    28,    29,     5,    47,
      48,     3,    56,    51,    52,     3,    38,    39,    82,    48,
      49,    85,    86,    87,    88,    89,    90,     3,     4,     5,
       6,    46,    79,    80,    81,    11,    12,    37,    14,    15,
      16,    17,    18,    49,    50,    21,    22,    49,    50,    25,
       7,     8,     9,    10,    30,    31,     7,     8,     9,    10,
      50,   125,     3,    20,    51,    41,    26,    27,   132,    46,
     134,    47,    48,    23,    24,    51,    52,    49,     3,     4,
       5,     6,    40,    41,   148,   149,    11,    12,    47,    14,
      15,    16,    17,    18,    30,    31,    21,    22,    93,    94,
      25,    69,    70,    50,   168,    30,    31,     3,     4,     5,
       6,    73,    74,    75,    76,    47,    41,    71,    72,    47,
       3,    48,    47,    48,    77,    78,    51,    48,    48,    25,
      35,    36,    37,    38,    30,    31,    48,    48,    48,    13,
       2,    50,    50,    35,    50,    41,    38,    27,    -1,    -1,
      23,    47,   125,    -1,    50,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
       3,     4,     5,     6,     3,     4,     5,     6,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    25,    30,    31,    -1,
      25,    30,    31,    -1,    -1,    30,    31,    -1,    41,    -1,
      -1,    -1,    41,    -1,    47,    48,    41,    -1,    47,    48,
      -1,    -1,    47,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    54,    55,     0,    11,    19,    56,    58,    59,    62,
       7,     8,     9,    10,    20,    57,    57,     3,     3,     3,
      60,    61,    47,    47,    37,    45,    48,    49,    57,    65,
      65,     3,     4,     5,     6,    25,    30,    31,    41,    47,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    87,     5,    61,     3,    49,    50,    50,    45,
      47,    81,    84,    87,     3,    87,    87,    81,    74,    23,
      24,    26,    27,    28,    29,    38,    39,    40,    41,    42,
      43,    44,    37,    30,    31,    32,    33,    34,    35,    36,
      37,    46,    57,    64,    63,    74,    50,    74,    86,    50,
      77,    77,    78,    78,    79,    79,    79,    79,    80,    80,
      81,    81,    81,    74,    74,    74,    74,    74,    74,    74,
       3,    51,    66,    66,    46,    49,    50,    12,    14,    15,
      16,    17,    18,    21,    22,    48,    52,    59,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    86,    47,    47,
      47,    48,    48,    48,    74,     3,    74,    52,    68,    48,
      74,    74,    69,    48,    48,    48,    50,    50,    69,    68,
      68,    74,    13,    50,    68,    68
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    58,    58,    59,    60,    60,    61,    61,    61,    63,
      62,    64,    62,    65,    65,    65,    66,    66,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    69,    69,    70,
      70,    71,    71,    72,    72,    72,    72,    73,    73,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    76,    76,
      76,    77,    77,    77,    78,    78,    78,    78,    78,    79,
      79,    79,    80,    80,    80,    80,    81,    81,    81,    81,
      81,    82,    82,    82,    82,    82,    83,    83,    83,    83,
      83,    84,    85,    85,    86,    86,    87
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     0,     1,     4,     1,     3,     1,     3,     4,     0,
       8,     0,     8,     0,     2,     4,     2,     3,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     5,
       7,     5,     7,     2,     3,     2,     2,     3,     3,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     2,
       2,     1,     1,     1,     2,     2,     1,     1,     1,     1,
       3,     4,     3,     4,     1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: global_items  */
#line 70 "custom.y"
                 {
        tac_last = (yyvsp[0].tac);
        tac_complete();
    }
#line 1433 "y.tab.c"
    break;

  case 3: /* global_items: %empty  */
#line 77 "custom.y"
                           { (yyval.tac) = NULL; }
#line 1439 "y.tab.c"
    break;

  case 4: /* global_items: global_items global_item  */
#line 78 "custom.y"
                             { (yyval.tac) = join_tac((yyvsp[-1].tac), (yyvsp[0].tac)); }
#line 1445 "y.tab.c"
    break;

  case 5: /* global_item: var_declaration  */
#line 82 "custom.y"
                          { (yyval.tac) = (yyvsp[0].exp)->tac; }
#line 1451 "y.tab.c"
    break;

  case 6: /* global_item: function_def  */
#line 83 "custom.y"
                          { (yyval.tac) = (yyvsp[0].tac); }
#line 1457 "y.tab.c"
    break;

  case 7: /* type_specifier: TYPE_INT  */
#line 88 "custom.y"
                  { (yyval.type) = INT_TYPE; }
#line 1463 "y.tab.c"
    break;

  case 8: /* type_specifier: TYPE_FLOAT  */
#line 89 "custom.y"
                  { (yyval.type) = FLOAT_TYPE; }
#line 1469 "y.tab.c"
    break;

  case 9: /* type_specifier: TYPE_BOOL  */
#line 90 "custom.y"
                  { (yyval.type) = BOOL_TYPE; }
#line 1475 "y.tab.c"
    break;

  case 10: /* type_specifier: TYPE_STRING  */
#line 91 "custom.y"
                  { (yyval.type) = STRING_TYPE; }
#line 1481 "y.tab.c"
    break;

  case 11: /* const_qualifier: %empty  */
#line 95 "custom.y"
               { (yyval.value) = 0; }
#line 1487 "y.tab.c"
    break;

  case 12: /* const_qualifier: CONST  */
#line 96 "custom.y"
             { (yyval.value) = 1; }
#line 1493 "y.tab.c"
    break;

  case 13: /* var_declaration: const_qualifier type_specifier init_declarator_list ';'  */
#line 101 "custom.y"
                                                            {
        add_type((yyvsp[-2].type), (yyvsp[-1].exp));
        if ((yyvsp[-3].value)) {
            for (EXP* e = (yyvsp[-1].exp); e != NULL; e = e->next) {
                e->ret->isConst = 1;
            }
        }
        (yyval.exp) = mk_exp(NULL, do_declaration((yyvsp[-1].exp)), NULL);
    }
#line 1507 "y.tab.c"
    break;

  case 14: /* init_declarator_list: init_declarator  */
#line 113 "custom.y"
                                              { (yyval.exp) = (yyvsp[0].exp); }
#line 1513 "y.tab.c"
    break;

  case 15: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 114 "custom.y"
                                              { (yyvsp[-2].exp)->next = (yyvsp[0].exp); (yyval.exp) = (yyvsp[-2].exp); }
#line 1519 "y.tab.c"
    break;

  case 16: /* init_declarator: IDENTIFIER  */
#line 118 "custom.y"
               {
        (yyval.exp) = mk_exp(do_var((yyvsp[0].string)), NULL, NULL);
    }
#line 1527 "y.tab.c"
    break;

  case 17: /* init_declarator: IDENTIFIER '=' expression  */
#line 121 "custom.y"
                              {
        SYM* sym = do_init_var((yyvsp[-2].string), 0, UNDEF_TYPE);
        (yyval.exp) = mk_exp(sym, do_assign(sym, (yyvsp[0].exp)), NULL);
    }
#line 1536 "y.tab.c"
    break;

  case 18: /* init_declarator: IDENTIFIER '[' INTEGER ']'  */
#line 125 "custom.y"
                               {
        (yyval.exp) = mk_exp(mk_array((yyvsp[-3].string), atoi((yyvsp[-1].string))), NULL, NULL);
    }
#line 1544 "y.tab.c"
    break;

  case 19: /* @1: %empty  */
#line 132 "custom.y"
                                                              {
        // Create function symbol in global scope
        scope = 0;
        TAC* func = declare_func((yyvsp[-3].string), (yyvsp[-1].tac));
        // Then switch to local scope for function body
        scope = 1; 
        sym_tab_local = NULL;
        (yyval.tac) = func;  // Pass function declaration to body
    }
#line 1558 "y.tab.c"
    break;

  case 20: /* function_def: FUNCTION type_specifier IDENTIFIER '(' parameter_list ')' @1 compound_statement  */
#line 140 "custom.y"
                         {
        // Complete function definition with body
        (yyval.tac) = do_func((yyvsp[-6].type), (yyvsp[-1].tac), (yyvsp[0].tac));
        // Reset back to global scope after function
        scope = 0;
        sym_tab_local = NULL;
    }
#line 1570 "y.tab.c"
    break;

  case 21: /* @2: %empty  */
#line 147 "custom.y"
                                                    {
        // Create function symbol in global scope
        scope = 0;
        TAC* func = declare_func((yyvsp[-3].string), (yyvsp[-1].tac));
        // Then switch to local scope for function body
        scope = 1; 
        sym_tab_local = NULL;
        (yyval.tac) = func;  // Pass function declaration to body
    }
#line 1584 "y.tab.c"
    break;

  case 22: /* function_def: FUNCTION VOID IDENTIFIER '(' parameter_list ')' @2 compound_statement  */
#line 155 "custom.y"
                         {
        // Complete function definition with body
        (yyval.tac) = do_func(UNDEF_TYPE, (yyvsp[-1].tac), (yyvsp[0].tac));
        // Reset back to global scope after function
        scope = 0;
        sym_tab_local = NULL;
    }
#line 1596 "y.tab.c"
    break;

  case 23: /* parameter_list: %empty  */
#line 165 "custom.y"
                                                   { (yyval.tac) = NULL; }
#line 1602 "y.tab.c"
    break;

  case 24: /* parameter_list: type_specifier IDENTIFIER  */
#line 166 "custom.y"
                                                  { (yyval.tac) = declare_para((yyvsp[0].string), (yyvsp[-1].type)); }
#line 1608 "y.tab.c"
    break;

  case 25: /* parameter_list: parameter_list ',' type_specifier IDENTIFIER  */
#line 167 "custom.y"
                                                  { (yyval.tac) = join_tac((yyvsp[-3].tac), declare_para((yyvsp[0].string), (yyvsp[-1].type))); }
#line 1614 "y.tab.c"
    break;

  case 26: /* compound_statement: '{' '}'  */
#line 172 "custom.y"
                               { (yyval.tac) = NULL; }
#line 1620 "y.tab.c"
    break;

  case 27: /* compound_statement: '{' statement_list '}'  */
#line 173 "custom.y"
                               { (yyval.tac) = (yyvsp[-1].tac); }
#line 1626 "y.tab.c"
    break;

  case 28: /* statement_list: statement  */
#line 177 "custom.y"
                               { (yyval.tac) = (yyvsp[0].tac); }
#line 1632 "y.tab.c"
    break;

  case 29: /* statement_list: statement_list statement  */
#line 178 "custom.y"
                               { (yyval.tac) = join_tac((yyvsp[-1].tac), (yyvsp[0].tac)); }
#line 1638 "y.tab.c"
    break;

  case 30: /* statement: expression_statement  */
#line 182 "custom.y"
                               { (yyval.tac) = (yyvsp[0].exp)->tac; }
#line 1644 "y.tab.c"
    break;

  case 31: /* statement: compound_statement  */
#line 183 "custom.y"
                               { (yyval.tac) = (yyvsp[0].tac); }
#line 1650 "y.tab.c"
    break;

  case 32: /* statement: selection_statement  */
#line 184 "custom.y"
                               { (yyval.tac) = (yyvsp[0].tac); }
#line 1656 "y.tab.c"
    break;

  case 33: /* statement: iteration_statement  */
#line 185 "custom.y"
                               { (yyval.tac) = (yyvsp[0].tac); }
#line 1662 "y.tab.c"
    break;

  case 34: /* statement: jump_statement  */
#line 186 "custom.y"
                               { (yyval.tac) = (yyvsp[0].tac); }
#line 1668 "y.tab.c"
    break;

  case 35: /* statement: var_declaration  */
#line 187 "custom.y"
                               { (yyval.tac) = (yyvsp[0].exp)->tac; }
#line 1674 "y.tab.c"
    break;

  case 36: /* statement: io_statement  */
#line 188 "custom.y"
                               { (yyval.tac) = (yyvsp[0].tac); }
#line 1680 "y.tab.c"
    break;

  case 37: /* expression_statement: ';'  */
#line 192 "custom.y"
                               { (yyval.exp) = mk_exp(NULL, NULL, NULL); }
#line 1686 "y.tab.c"
    break;

  case 38: /* expression_statement: expression ';'  */
#line 193 "custom.y"
                               { (yyval.exp) = (yyvsp[-1].exp); }
#line 1692 "y.tab.c"
    break;

  case 39: /* selection_statement: IF '(' expression ')' statement  */
#line 198 "custom.y"
                                    {
        (yyval.tac) = do_if((yyvsp[-2].exp), (yyvsp[0].tac));
    }
#line 1700 "y.tab.c"
    break;

  case 40: /* selection_statement: IF '(' expression ')' statement ELSE statement  */
#line 201 "custom.y"
                                                   {
        (yyval.tac) = do_if_else((yyvsp[-4].exp), (yyvsp[-2].tac), (yyvsp[0].tac));
    }
#line 1708 "y.tab.c"
    break;

  case 41: /* iteration_statement: WHILE '(' expression ')' statement  */
#line 208 "custom.y"
                                       {
        (yyval.tac) = do_while((yyvsp[-2].exp), (yyvsp[0].tac));
    }
#line 1716 "y.tab.c"
    break;

  case 42: /* iteration_statement: FOR '(' expression_statement expression_statement expression ')' statement  */
#line 211 "custom.y"
                                                                               {
        (yyval.tac) = do_for((yyvsp[-4].exp)->tac, (yyvsp[-3].exp), (yyvsp[-2].exp)->tac, (yyvsp[0].tac));
    }
#line 1724 "y.tab.c"
    break;

  case 43: /* jump_statement: RETURN ';'  */
#line 218 "custom.y"
                               { (yyval.tac) = do_return(NULL); }
#line 1730 "y.tab.c"
    break;

  case 44: /* jump_statement: RETURN expression ';'  */
#line 219 "custom.y"
                               { (yyval.tac) = do_return((yyvsp[-1].exp)); }
#line 1736 "y.tab.c"
    break;

  case 45: /* jump_statement: BREAK ';'  */
#line 220 "custom.y"
                               { /* 简化版不处理 */ (yyval.tac) = NULL; }
#line 1742 "y.tab.c"
    break;

  case 46: /* jump_statement: CONTINUE ';'  */
#line 221 "custom.y"
                               { /* 简化版不处理 */ (yyval.tac) = NULL; }
#line 1748 "y.tab.c"
    break;

  case 47: /* io_statement: INPUT IDENTIFIER ';'  */
#line 226 "custom.y"
                               { (yyval.tac) = do_input((yyvsp[-1].string)); }
#line 1754 "y.tab.c"
    break;

  case 48: /* io_statement: OUTPUT expression ';'  */
#line 227 "custom.y"
                               { (yyval.tac) = do_output((yyvsp[-1].exp)); }
#line 1760 "y.tab.c"
    break;

  case 49: /* expression: assignment_expression  */
#line 232 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 1766 "y.tab.c"
    break;

  case 50: /* assignment_expression: logical_expression  */
#line 236 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 1772 "y.tab.c"
    break;

  case 51: /* assignment_expression: lvalue '=' expression  */
#line 237 "custom.y"
                               { (yyval.exp) = mk_exp((yyvsp[-2].sym), do_assign((yyvsp[-2].sym), (yyvsp[0].exp)), NULL); }
#line 1778 "y.tab.c"
    break;

  case 52: /* assignment_expression: array_index '=' expression  */
#line 238 "custom.y"
                               {
        SYM* arr = (yyvsp[-2].exp)->ret->address;
        EXP* idx = (yyvsp[-2].exp)->ret->etc;
        TAC* tac = do_array_assign(arr, idx, (yyvsp[0].exp));
        (yyval.exp) = mk_exp((yyvsp[0].exp)->ret, join_tac(join_tac((yyvsp[-2].exp)->tac, (yyvsp[0].exp)->tac), tac), NULL);
    }
#line 1789 "y.tab.c"
    break;

  case 53: /* assignment_expression: lvalue ADD_ASSIGN expression  */
#line 244 "custom.y"
                                 {
        EXP* tmp = do_bin(TAC_ADD, mk_exp((yyvsp[-2].sym), NULL, NULL), (yyvsp[0].exp));
        (yyval.exp) = mk_exp((yyvsp[-2].sym), do_assign((yyvsp[-2].sym), tmp), NULL);
    }
#line 1798 "y.tab.c"
    break;

  case 54: /* assignment_expression: lvalue SUB_ASSIGN expression  */
#line 248 "custom.y"
                                 {
        EXP* tmp = do_bin(TAC_SUB, mk_exp((yyvsp[-2].sym), NULL, NULL), (yyvsp[0].exp));
        (yyval.exp) = mk_exp((yyvsp[-2].sym), do_assign((yyvsp[-2].sym), tmp), NULL);
    }
#line 1807 "y.tab.c"
    break;

  case 55: /* assignment_expression: lvalue MUL_ASSIGN expression  */
#line 252 "custom.y"
                                 {
        EXP* tmp = do_bin(TAC_MUL, mk_exp((yyvsp[-2].sym), NULL, NULL), (yyvsp[0].exp));
        (yyval.exp) = mk_exp((yyvsp[-2].sym), do_assign((yyvsp[-2].sym), tmp), NULL);
    }
#line 1816 "y.tab.c"
    break;

  case 56: /* assignment_expression: lvalue DIV_ASSIGN expression  */
#line 256 "custom.y"
                                 {
        EXP* tmp = do_bin(TAC_DIV, mk_exp((yyvsp[-2].sym), NULL, NULL), (yyvsp[0].exp));
        (yyval.exp) = mk_exp((yyvsp[-2].sym), do_assign((yyvsp[-2].sym), tmp), NULL);
    }
#line 1825 "y.tab.c"
    break;

  case 57: /* assignment_expression: lvalue MOD_ASSIGN expression  */
#line 260 "custom.y"
                                 {
        EXP* tmp = do_bin(TAC_MOD, mk_exp((yyvsp[-2].sym), NULL, NULL), (yyvsp[0].exp));
        (yyval.exp) = mk_exp((yyvsp[-2].sym), do_assign((yyvsp[-2].sym), tmp), NULL);
    }
#line 1834 "y.tab.c"
    break;

  case 58: /* logical_expression: equality_expression  */
#line 267 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 1840 "y.tab.c"
    break;

  case 59: /* logical_expression: logical_expression AND equality_expression  */
#line 268 "custom.y"
                                               { (yyval.exp) = do_logic(TAC_AND, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1846 "y.tab.c"
    break;

  case 60: /* logical_expression: logical_expression OR equality_expression  */
#line 269 "custom.y"
                                               { (yyval.exp) = do_logic(TAC_OR, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1852 "y.tab.c"
    break;

  case 61: /* equality_expression: relational_expression  */
#line 273 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 1858 "y.tab.c"
    break;

  case 62: /* equality_expression: equality_expression EQ relational_expression  */
#line 274 "custom.y"
                                                 { (yyval.exp) = do_cmp(TAC_EQ, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1864 "y.tab.c"
    break;

  case 63: /* equality_expression: equality_expression NE relational_expression  */
#line 275 "custom.y"
                                                 { (yyval.exp) = do_cmp(TAC_NE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1870 "y.tab.c"
    break;

  case 64: /* relational_expression: additive_expression  */
#line 279 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 1876 "y.tab.c"
    break;

  case 65: /* relational_expression: relational_expression '<' additive_expression  */
#line 280 "custom.y"
                                                  { (yyval.exp) = do_cmp(TAC_LT, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1882 "y.tab.c"
    break;

  case 66: /* relational_expression: relational_expression '>' additive_expression  */
#line 281 "custom.y"
                                                  { (yyval.exp) = do_cmp(TAC_GT, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1888 "y.tab.c"
    break;

  case 67: /* relational_expression: relational_expression LE additive_expression  */
#line 282 "custom.y"
                                                  { (yyval.exp) = do_cmp(TAC_LE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1894 "y.tab.c"
    break;

  case 68: /* relational_expression: relational_expression GE additive_expression  */
#line 283 "custom.y"
                                                  { (yyval.exp) = do_cmp(TAC_GE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1900 "y.tab.c"
    break;

  case 69: /* additive_expression: multiplicative_expression  */
#line 287 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 1906 "y.tab.c"
    break;

  case 70: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 288 "custom.y"
                                                      { (yyval.exp) = do_bin(TAC_ADD, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1912 "y.tab.c"
    break;

  case 71: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 289 "custom.y"
                                                      { (yyval.exp) = do_bin(TAC_SUB, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1918 "y.tab.c"
    break;

  case 72: /* multiplicative_expression: unary_expression  */
#line 293 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 1924 "y.tab.c"
    break;

  case 73: /* multiplicative_expression: multiplicative_expression '*' unary_expression  */
#line 294 "custom.y"
                                                   { (yyval.exp) = do_bin(TAC_MUL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1930 "y.tab.c"
    break;

  case 74: /* multiplicative_expression: multiplicative_expression '/' unary_expression  */
#line 295 "custom.y"
                                                   { (yyval.exp) = do_bin(TAC_DIV, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1936 "y.tab.c"
    break;

  case 75: /* multiplicative_expression: multiplicative_expression '%' unary_expression  */
#line 296 "custom.y"
                                                   { (yyval.exp) = do_bin(TAC_MOD, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1942 "y.tab.c"
    break;

  case 76: /* unary_expression: postfix_expression  */
#line 300 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 1948 "y.tab.c"
    break;

  case 77: /* unary_expression: '-' unary_expression  */
#line 301 "custom.y"
                               {
        SYM* tmp = mk_tmp();
        tmp->varType = INT_TYPE;
        TAC* tac = join_tac((yyvsp[0].exp)->tac, mk_tac(TAC_NEG, tmp, (yyvsp[0].exp)->ret, NULL));
        (yyval.exp) = mk_exp(tmp, tac, NULL);
    }
#line 1959 "y.tab.c"
    break;

  case 78: /* unary_expression: NOT unary_expression  */
#line 307 "custom.y"
                               { (yyval.exp) = do_not((yyvsp[0].exp)); }
#line 1965 "y.tab.c"
    break;

  case 79: /* unary_expression: INC lvalue  */
#line 308 "custom.y"
                               {
        SYM* one = mk_const(1);
        EXP* tmp = do_bin(TAC_ADD, mk_exp((yyvsp[0].sym), NULL, NULL), mk_exp(one, NULL, NULL));
        TAC* tac = join_tac(tmp->tac, do_assign((yyvsp[0].sym), tmp));
        (yyval.exp) = mk_exp((yyvsp[0].sym), tac, NULL);
    }
#line 1976 "y.tab.c"
    break;

  case 80: /* unary_expression: DEC lvalue  */
#line 314 "custom.y"
                               {
        SYM* one = mk_const(1);
        EXP* tmp = do_bin(TAC_SUB, mk_exp((yyvsp[0].sym), NULL, NULL), mk_exp(one, NULL, NULL));
        TAC* tac = join_tac(tmp->tac, do_assign((yyvsp[0].sym), tmp));
        (yyval.exp) = mk_exp((yyvsp[0].sym), tac, NULL);
    }
#line 1987 "y.tab.c"
    break;

  case 81: /* postfix_expression: primary_expression  */
#line 323 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 1993 "y.tab.c"
    break;

  case 82: /* postfix_expression: array_index  */
#line 324 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 1999 "y.tab.c"
    break;

  case 83: /* postfix_expression: function_call  */
#line 325 "custom.y"
                               { (yyval.exp) = (yyvsp[0].exp); }
#line 2005 "y.tab.c"
    break;

  case 84: /* postfix_expression: lvalue INC  */
#line 326 "custom.y"
                               {
        SYM* tmp = mk_tmp();
        SYM* one = mk_const(1);
        TAC* tac = mk_tac(TAC_COPY, tmp, (yyvsp[-1].sym), NULL);
        EXP* inc = do_bin(TAC_ADD, mk_exp((yyvsp[-1].sym), NULL, NULL), mk_exp(one, NULL, NULL));
        tac = join_tac(tac, inc->tac);
        tac = join_tac(tac, do_assign((yyvsp[-1].sym), inc));
        (yyval.exp) = mk_exp(tmp, tac, NULL);
    }
#line 2019 "y.tab.c"
    break;

  case 85: /* postfix_expression: lvalue DEC  */
#line 335 "custom.y"
                               {
        SYM* tmp = mk_tmp();
        SYM* one = mk_const(1);
        TAC* tac = mk_tac(TAC_COPY, tmp, (yyvsp[-1].sym), NULL);
        EXP* dec = do_bin(TAC_SUB, mk_exp((yyvsp[-1].sym), NULL, NULL), mk_exp(one, NULL, NULL));
        tac = join_tac(tac, dec->tac);
        tac = join_tac(tac, do_assign((yyvsp[-1].sym), dec));
        (yyval.exp) = mk_exp(tmp, tac, NULL);
    }
#line 2033 "y.tab.c"
    break;

  case 86: /* primary_expression: IDENTIFIER  */
#line 347 "custom.y"
                               { (yyval.exp) = mk_exp(get_var((yyvsp[0].string)), NULL, NULL); }
#line 2039 "y.tab.c"
    break;

  case 87: /* primary_expression: INTEGER  */
#line 348 "custom.y"
                               { (yyval.exp) = mk_exp(mk_const(atoi((yyvsp[0].string))), NULL, NULL); }
#line 2045 "y.tab.c"
    break;

  case 88: /* primary_expression: BOOL_LITERAL  */
#line 349 "custom.y"
                               { (yyval.exp) = do_bool_literal((yyvsp[0].value)); }
#line 2051 "y.tab.c"
    break;

  case 89: /* primary_expression: STRING_LITERAL  */
#line 350 "custom.y"
                               { (yyval.exp) = mk_exp(mk_text((yyvsp[0].string)), NULL, NULL); }
#line 2057 "y.tab.c"
    break;

  case 90: /* primary_expression: '(' expression ')'  */
#line 351 "custom.y"
                               { (yyval.exp) = (yyvsp[-1].exp); }
#line 2063 "y.tab.c"
    break;

  case 91: /* array_index: IDENTIFIER '[' expression ']'  */
#line 355 "custom.y"
                                  {
        SYM* array = lookup_sym((yyvsp[-3].string));
        if (array == NULL) {
            error("变量未定义: %s", (yyvsp[-3].string));
            (yyval.exp) = NULL;
        } else if (array->type != SYM_ARRAY) {
            error("变量不是数组: %s", (yyvsp[-3].string));
            (yyval.exp) = NULL;
        } else {
            (yyval.exp) = do_array_index(array, (yyvsp[-1].exp));
        }
    }
#line 2080 "y.tab.c"
    break;

  case 92: /* function_call: IDENTIFIER '(' ')'  */
#line 370 "custom.y"
                                     { (yyval.exp) = do_call_ret((yyvsp[-2].string), NULL); }
#line 2086 "y.tab.c"
    break;

  case 93: /* function_call: IDENTIFIER '(' argument_list ')'  */
#line 371 "custom.y"
                                     { (yyval.exp) = do_call_ret((yyvsp[-3].string), (yyvsp[-1].exp)); }
#line 2092 "y.tab.c"
    break;

  case 94: /* argument_list: expression  */
#line 375 "custom.y"
                                      { (yyval.exp) = (yyvsp[0].exp); }
#line 2098 "y.tab.c"
    break;

  case 95: /* argument_list: expression ',' argument_list  */
#line 376 "custom.y"
                                      { (yyvsp[-2].exp)->next = (yyvsp[0].exp); (yyval.exp) = (yyvsp[-2].exp); }
#line 2104 "y.tab.c"
    break;

  case 96: /* lvalue: IDENTIFIER  */
#line 380 "custom.y"
                                      { (yyval.sym) = get_var((yyvsp[0].string)); }
#line 2110 "y.tab.c"
    break;


#line 2114 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 383 "custom.y"


void yyerror(char* msg) {
    fprintf(stderr, "%s: 第 %d 行\n", msg, yylineno);
    exit(1);
}
