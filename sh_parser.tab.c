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
#line 1 "sh_parser.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "map.h"
#include "list.h"
#include "basm_wizard.h"
#include "string_module.h"

#ifdef DEBUG
    #define DBG_MSG(...) printf(__VA_ARGS__);
#else
    #define DBG_MSG(...) ((void)0)
#endif

typedef long long SLOT_T;
char zero_str[] = "0";
char  one_str[] = "1";
char  minus_one_str[] = "-1";
char _0x80000000[] = "-2147483648";

extern int yylineno;
extern FILE *yyin;
FILE* p_output_file = NULL;

Map global_vars_map;
int next_global_stack_slot = 0;
int next_local_stack_slot = 0;
int word_cnt = 0;
unsigned int label_cnt = 0;
char* list_end_label = NULL;
char*   if_end_label = NULL;
struct list_node* code_block;
struct list_node* final_code = NULL;


char dbg_start[] = "_____________dbg_start";
char dbg_end[] =   "_____________dbg_end";

char* create_named_string(char* str){ return create_string_s(str, ++label_cnt); }

extern int yyparse();
void yyerror(const char *s);
int  yylex(void);
int get_stack_slot(int* stack_slot);
void free_stack_slot(int* stack_slot);
char* lltostr(long long value);
int fill_gaps(void);
void write_to_output_file(struct list_node *node, void *arg);
char* alloc_global_var(char* name);
void dbg_list(char* str, struct list_node* node);
void convert_to_exitcode(struct list_node** list);
void gen_bin_op(struct list_node** p_list, char* op);
void gen_eq(struct list_node** p_list);
void gen_ne(struct list_node** p_list);
void gen_lt(struct list_node** p_list);
void gen_le(struct list_node** p_list);
void gen_gt(struct list_node** p_list);
void gen_ge(struct list_node** p_list);


#line 136 "sh_parser.tab.c"

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

#include "sh_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_WORD = 4,                       /* WORD  */
  YYSYMBOL_VAR = 5,                        /* VAR  */
  YYSYMBOL_VAR_VALUE = 6,                  /* VAR_VALUE  */
  YYSYMBOL_assignment = 7,                 /* assignment  */
  YYSYMBOL_COMMENT = 8,                    /* COMMENT  */
  YYSYMBOL_NEWLINE = 9,                    /* NEWLINE  */
  YYSYMBOL_EXITCODE = 10,                  /* EXITCODE  */
  YYSYMBOL_semicolon = 11,                 /* semicolon  */
  YYSYMBOL_opening_curve = 12,             /* opening_curve  */
  YYSYMBOL_closing_curve = 13,             /* closing_curve  */
  YYSYMBOL_stick_ampersand = 14,           /* stick_ampersand  */
  YYSYMBOL_semicolon_ampersand = 15,       /* semicolon_ampersand  */
  YYSYMBOL__case = 16,                     /* _case  */
  YYSYMBOL__coproc = 17,                   /* _coproc  */
  YYSYMBOL__do = 18,                       /* _do  */
  YYSYMBOL__done = 19,                     /* _done  */
  YYSYMBOL__elif = 20,                     /* _elif  */
  YYSYMBOL__else = 21,                     /* _else  */
  YYSYMBOL__esac = 22,                     /* _esac  */
  YYSYMBOL__fi = 23,                       /* _fi  */
  YYSYMBOL__for = 24,                      /* _for  */
  YYSYMBOL__function = 25,                 /* _function  */
  YYSYMBOL__if = 26,                       /* _if  */
  YYSYMBOL__in = 27,                       /* _in  */
  YYSYMBOL__select = 28,                   /* _select  */
  YYSYMBOL__then = 29,                     /* _then  */
  YYSYMBOL__until = 30,                    /* _until  */
  YYSYMBOL__while = 31,                    /* _while  */
  YYSYMBOL__time = 32,                     /* _time  */
  YYSYMBOL__exclamation_mark = 33,         /* _exclamation_mark  */
  YYSYMBOL__opening_brace = 34,            /* _opening_brace  */
  YYSYMBOL__closing_brace = 35,            /* _closing_brace  */
  YYSYMBOL__db_opening_square_bracket = 36, /* _db_opening_square_bracket  */
  YYSYMBOL__db_closing_square_bracket = 37, /* _db_closing_square_bracket  */
  YYSYMBOL_more_ampersand = 38,            /* more_ampersand  */
  YYSYMBOL_ampersand_more = 39,            /* ampersand_more  */
  YYSYMBOL_dollar_db_opening_curve = 40,   /* dollar_db_opening_curve  */
  YYSYMBOL_dollar_opening_curve = 41,      /* dollar_opening_curve  */
  YYSYMBOL_backtick = 42,                  /* backtick  */
  YYSYMBOL_less_more = 43,                 /* less_more  */
  YYSYMBOL_opening_square_bracket = 44,    /* opening_square_bracket  */
  YYSYMBOL_closing_square_bracket = 45,    /* closing_square_bracket  */
  YYSYMBOL_u_cond_op = 46,                 /* u_cond_op  */
  YYSYMBOL_bin_cond_op = 47,               /* bin_cond_op  */
  YYSYMBOL_ERROR = 48,                     /* ERROR  */
  YYSYMBOL_declaration_command = 49,       /* declaration_command  */
  YYSYMBOL_echo = 50,                      /* echo  */
  YYSYMBOL_eq_option = 51,                 /* eq_option  */
  YYSYMBOL_ne_option = 52,                 /* ne_option  */
  YYSYMBOL_lt_option = 53,                 /* lt_option  */
  YYSYMBOL_le_option = 54,                 /* le_option  */
  YYSYMBOL_gt_option = 55,                 /* gt_option  */
  YYSYMBOL_ge_option = 56,                 /* ge_option  */
  YYSYMBOL_comma = 57,                     /* comma  */
  YYSYMBOL_eq = 58,                        /* eq  */
  YYSYMBOL_mul_eq = 59,                    /* mul_eq  */
  YYSYMBOL_div_eq = 60,                    /* div_eq  */
  YYSYMBOL_mod_eq = 61,                    /* mod_eq  */
  YYSYMBOL_plus_eq = 62,                   /* plus_eq  */
  YYSYMBOL_minus_eq = 63,                  /* minus_eq  */
  YYSYMBOL_shl_eq = 64,                    /* shl_eq  */
  YYSYMBOL_shr_eq = 65,                    /* shr_eq  */
  YYSYMBOL_ampersand_eq = 66,              /* ampersand_eq  */
  YYSYMBOL_xor_eq = 67,                    /* xor_eq  */
  YYSYMBOL_stick_eq = 68,                  /* stick_eq  */
  YYSYMBOL_question = 69,                  /* question  */
  YYSYMBOL_colon = 70,                     /* colon  */
  YYSYMBOL_db_stick = 71,                  /* db_stick  */
  YYSYMBOL_db_ampersand = 72,              /* db_ampersand  */
  YYSYMBOL_stick = 73,                     /* stick  */
  YYSYMBOL_xor = 74,                       /* xor  */
  YYSYMBOL_ampersand = 75,                 /* ampersand  */
  YYSYMBOL_db_eq = 76,                     /* db_eq  */
  YYSYMBOL_exclamation_eq = 77,            /* exclamation_eq  */
  YYSYMBOL_less_eq = 78,                   /* less_eq  */
  YYSYMBOL_more_eq = 79,                   /* more_eq  */
  YYSYMBOL_more = 80,                      /* more  */
  YYSYMBOL_less = 81,                      /* less  */
  YYSYMBOL_shl = 82,                       /* shl  */
  YYSYMBOL_shr = 83,                       /* shr  */
  YYSYMBOL_plus = 84,                      /* plus  */
  YYSYMBOL_minus = 85,                     /* minus  */
  YYSYMBOL_mul = 86,                       /* mul  */
  YYSYMBOL_division = 87,                  /* division  */
  YYSYMBOL_mod = 88,                       /* mod  */
  YYSYMBOL_power = 89,                     /* power  */
  YYSYMBOL_tilda = 90,                     /* tilda  */
  YYSYMBOL_pre_inc = 91,                   /* pre_inc  */
  YYSYMBOL_pre_dec = 92,                   /* pre_dec  */
  YYSYMBOL_post_inc = 93,                  /* post_inc  */
  YYSYMBOL_post_dec = 94,                  /* post_dec  */
  YYSYMBOL_LIST_PRI_2 = 95,                /* LIST_PRI_2  */
  YYSYMBOL_LIST_PRI_1 = 96,                /* LIST_PRI_1  */
  YYSYMBOL_ASSIGNMENT_PRI = 97,            /* ASSIGNMENT_PRI  */
  YYSYMBOL_TRIPLE_OP = 98,                 /* TRIPLE_OP  */
  YYSYMBOL_UNARY = 99,                     /* UNARY  */
  YYSYMBOL_PAREN = 100,                    /* PAREN  */
  YYSYMBOL_YYACCEPT = 101,                 /* $accept  */
  YYSYMBOL_db_opening_curve = 102,         /* db_opening_curve  */
  YYSYMBOL_db_closing_curve = 103,         /* db_closing_curve  */
  YYSYMBOL_input = 104,                    /* input  */
  YYSYMBOL_word = 105,                     /* word  */
  YYSYMBOL_words = 106,                    /* words  */
  YYSYMBOL_assignment_structure = 107,     /* assignment_structure  */
  YYSYMBOL_command = 108,                  /* command  */
  YYSYMBOL_pipeline_members_connector = 109, /* pipeline_members_connector  */
  YYSYMBOL_pipeline_body = 110,            /* pipeline_body  */
  YYSYMBOL_pipeline = 111,                 /* pipeline  */
  YYSYMBOL_list_tail = 112,                /* list_tail  */
  YYSYMBOL_list_members_connector_pri_2 = 113, /* list_members_connector_pri_2  */
  YYSYMBOL_list_members_connector_pri_1 = 114, /* list_members_connector_pri_1  */
  YYSYMBOL_list_body = 115,                /* list_body  */
  YYSYMBOL_list = 116,                     /* list  */
  YYSYMBOL_compound_command = 117,         /* compound_command  */
  YYSYMBOL_empty_or_NEWLINE = 118,         /* empty_or_NEWLINE  */
  YYSYMBOL_while_cycle = 119,              /* while_cycle  */
  YYSYMBOL_elif_structure = 120,           /* elif_structure  */
  YYSYMBOL_elif_structures = 121,          /* elif_structures  */
  YYSYMBOL_else_structure = 122,           /* else_structure  */
  YYSYMBOL_if_structure = 123,             /* if_structure  */
  YYSYMBOL_op_eq = 124,                    /* op_eq  */
  YYSYMBOL_post_c_op = 125,                /* post_c_op  */
  YYSYMBOL_pre_c_op = 126,                 /* pre_c_op  */
  YYSYMBOL_expr = 127,                     /* expr  */
  YYSYMBOL_cmp_expr_squared = 128,         /* cmp_expr_squared  */
  YYSYMBOL_cmp_expr_curved = 129           /* cmp_expr_curved  */
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   577

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  101
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  199

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   355


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   161,   161,   165,   170,   179,   186,   187,   190,   193,
     196,   207,   218,   226,   230,   240,   248,   268,   271,   277,
     291,   292,   293,   294,   298,   301,   312,   315,   331,   332,
     333,   336,   337,   338,   341,   342,   343,   344,   348,   351,
     363,   377,   388,   402,   405,   408,   414,   420,   426,   429,
     443,   444,   451,   480,   506,   509,   512,   521,   524,   543,
     592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     605,   606,   610,   611,   620,   623,   632,   641,   656,   669,
     682,   690,   693,   708,   716,   723,   730,   737,   744,   751,
     758,   765,   772,   779,   786,   793,   800,   807,   810,   831,
     841,   848,   855,   862,   869,   876,   883,   893,   900,   907,
     914,   921,   928
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
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "WORD", "VAR",
  "VAR_VALUE", "assignment", "COMMENT", "NEWLINE", "EXITCODE", "semicolon",
  "opening_curve", "closing_curve", "stick_ampersand",
  "semicolon_ampersand", "_case", "_coproc", "_do", "_done", "_elif",
  "_else", "_esac", "_fi", "_for", "_function", "_if", "_in", "_select",
  "_then", "_until", "_while", "_time", "_exclamation_mark",
  "_opening_brace", "_closing_brace", "_db_opening_square_bracket",
  "_db_closing_square_bracket", "more_ampersand", "ampersand_more",
  "dollar_db_opening_curve", "dollar_opening_curve", "backtick",
  "less_more", "opening_square_bracket", "closing_square_bracket",
  "u_cond_op", "bin_cond_op", "ERROR", "declaration_command", "echo",
  "eq_option", "ne_option", "lt_option", "le_option", "gt_option",
  "ge_option", "comma", "eq", "mul_eq", "div_eq", "mod_eq", "plus_eq",
  "minus_eq", "shl_eq", "shr_eq", "ampersand_eq", "xor_eq", "stick_eq",
  "question", "colon", "db_stick", "db_ampersand", "stick", "xor",
  "ampersand", "db_eq", "exclamation_eq", "less_eq", "more_eq", "more",
  "less", "shl", "shr", "plus", "minus", "mul", "division", "mod", "power",
  "tilda", "pre_inc", "pre_dec", "post_inc", "post_dec", "LIST_PRI_2",
  "LIST_PRI_1", "ASSIGNMENT_PRI", "TRIPLE_OP", "UNARY", "PAREN", "$accept",
  "db_opening_curve", "db_closing_curve", "input", "word", "words",
  "assignment_structure", "command", "pipeline_members_connector",
  "pipeline_body", "pipeline", "list_tail", "list_members_connector_pri_2",
  "list_members_connector_pri_1", "list_body", "list", "compound_command",
  "empty_or_NEWLINE", "while_cycle", "elif_structure", "elif_structures",
  "else_structure", "if_structure", "op_eq", "post_c_op", "pre_c_op",
  "expr", "cmp_expr_squared", "cmp_expr_curved", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-70)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-34)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -5,   -70,     9,   212,   -70,   223,    -1,   212,   212,   265,
      -5,    34,    34,   297,    34,   -70,   -70,   -12,   -70,     8,
      -5,   -70,   -70,   -70,   -70,   -70,   -70,   -70,    -5,    34,
     212,   212,   -70,   -70,   212,   -15,    -2,   -12,   212,   303,
      34,    34,    34,    34,    34,    34,   -70,   -70,   -70,    21,
     271,     5,   -70,   -10,   -70,    71,    27,    36,   265,   242,
     208,    50,    51,   -70,   212,   212,   -70,   297,    71,    30,
      20,    52,    -5,    -5,     8,    34,   -70,   -70,   -70,   -70,
     -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,    34,   -70,
     383,   125,    -6,    -6,    -6,    -6,   -70,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    34,   -70,   -70,    53,   -70,   -70,   -70,
     -70,   254,   -70,   -70,   -70,   -70,   -70,   124,   -70,   -70,
     -70,   -70,   212,   212,    33,   383,   362,   -70,   362,   362,
     362,   362,   362,   362,   383,   329,   404,   425,   446,   467,
     488,   -31,   -31,   247,   247,   247,   247,   304,   304,   224,
     224,   -64,   -64,   -64,   -64,   -70,   -70,    57,    58,    62,
     -70,    34,   -70,    -5,   -70,    -8,   -70,   383,   212,    -5,
     -70,    48,    54,   212,   -70,    -5,   -70,   212,   -70
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      50,    51,     0,     0,     1,     0,    50,     0,     0,     0,
      50,     0,     0,     0,     0,    18,    24,    26,    38,    41,
      50,    17,    49,    48,     5,    10,    11,     6,    50,     0,
       0,     0,    15,     2,     0,     0,     0,    27,     0,    10,
       0,     0,     0,     0,     0,     0,    72,    73,    74,     0,
       0,     0,    97,     0,    19,     0,    21,    20,     0,    29,
      28,    35,    34,    42,     0,     0,     4,     0,     0,     0,
       0,     0,    50,    50,     0,     0,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     0,    78,
      75,     0,    82,    81,    80,    83,    79,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    47,     0,    45,    23,    22,
      25,    30,    37,    36,    40,    39,    13,    50,     9,     7,
       8,    43,     0,     0,     0,    76,    77,   100,   101,   102,
     103,   104,   105,   106,    99,     0,    95,    94,    92,    93,
      91,   107,   108,   110,   112,   111,   109,    90,    89,    85,
      84,    86,    87,    88,    96,     3,    14,     0,    54,     0,
      44,     0,    16,    50,    55,    57,    52,    98,     0,    50,
      56,     0,     0,     0,    59,    50,    58,     0,    53
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -70,   -70,    14,   -70,     2,   -70,   -70,    55,   -70,    76,
     -43,    40,   -70,   -70,    77,    -7,   -70,     0,   -70,   -69,
     -70,   -70,   -70,   -70,   -70,   -70,   -11,   105,   -70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    14,   127,     2,    48,   137,    15,    16,    58,    17,
      18,    63,    64,    65,    19,    20,    21,     3,    22,   184,
     185,   191,    23,    88,    89,    49,    50,    51,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    36,    56,    55,     1,   104,    34,    32,     1,     4,
      38,    33,   183,   189,    72,    54,    73,    59,    68,    60,
      66,   134,   135,    69,    70,   123,    96,    71,    67,    90,
      91,    92,    93,    94,    95,   125,   128,    24,   104,    39,
      26,    40,   124,   139,    27,   129,    41,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   132,
     133,    57,   140,   104,   145,   141,   175,    42,   180,   136,
     182,   194,   142,   143,    29,    30,    31,   146,   183,    61,
      62,   186,   138,   195,   126,    37,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   130,   144,    74,   190,    53,    43,    44,
       0,     0,     0,     0,    45,    46,    47,    24,   103,    25,
      26,     0,     0,     1,    27,   178,   179,   177,   147,   176,
     104,     0,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,     0,     0,     0,    29,    30,    31,     0,     0,     0,
     187,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   192,   103,   188,     0,     0,   196,     0,     0,   193,
     198,     0,     0,     0,   104,   197,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   -31,     0,   131,     0,     5,
     -31,     0,     0,     0,     6,     0,    24,     0,    25,    26,
       0,     0,     0,    27,   -31,    28,     0,     0,     7,   -31,
       0,   -31,   -31,     8,   -31,     9,    10,     0,    11,   -32,
       0,     0,   -31,     0,   -32,     0,    12,     0,   -31,     0,
       0,   -33,    13,    29,    30,    31,   -33,     0,   -32,     0,
       0,     0,     5,   -32,     0,   -32,   -32,     6,   -32,     0,
     -33,     0,     0,     0,     0,   -33,   -32,   -33,   -33,     0,
     -33,     7,   -32,   104,     0,     0,     8,     0,   -33,    10,
      24,    11,    25,    26,   -33,     0,     0,    27,     0,    12,
     120,   121,   122,   123,     0,    13,   104,     0,     0,     0,
       0,     0,    97,    98,    99,   100,   101,   102,   103,   116,
     117,   118,   119,   120,   121,   122,   123,    29,    30,    31,
     104,     0,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,     0,   104,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   103,     0,   118,   119,
     120,   121,   122,   123,     0,     0,    86,    87,   104,   181,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,     0,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   104,     0,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   104,     0,     0,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   104,     0,     0,     0,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   104,     0,     0,     0,     0,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   104,     0,     0,     0,
       0,     0,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   104,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123
};

static const yytype_int16 yycheck[] =
{
       7,     8,    14,    14,     9,    69,     6,     5,     9,     0,
      10,    12,    20,    21,    29,    13,    18,     9,    29,    11,
      20,    64,    65,    30,    31,    89,     5,    34,    28,    40,
      41,    42,    43,    44,    45,    45,     9,     3,    69,     5,
       6,     7,    37,    13,    10,     9,    12,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,     9,
       9,    73,    42,    69,    75,    13,    13,    33,    35,    67,
      13,    23,    72,    73,    40,    41,    42,    88,    20,    71,
      72,    19,    68,    29,    13,     9,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,    58,    74,    38,   185,    12,    84,    85,
      -1,    -1,    -1,    -1,    90,    91,    92,     3,    57,     5,
       6,    -1,    -1,     9,    10,   142,   143,   137,    13,   137,
      69,    -1,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    -1,    -1,    -1,    40,    41,    42,    -1,    -1,    -1,
     181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   188,    57,   183,    -1,    -1,   193,    -1,    -1,   189,
     197,    -1,    -1,    -1,    69,   195,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,     7,    -1,     9,    -1,     7,
      12,    -1,    -1,    -1,    12,    -1,     3,    -1,     5,     6,
      -1,    -1,    -1,    10,    26,    12,    -1,    -1,    26,    31,
      -1,    33,    34,    31,    36,    33,    34,    -1,    36,     7,
      -1,    -1,    44,    -1,    12,    -1,    44,    -1,    50,    -1,
      -1,     7,    50,    40,    41,    42,    12,    -1,    26,    -1,
      -1,    -1,     7,    31,    -1,    33,    34,    12,    36,    -1,
      26,    -1,    -1,    -1,    -1,    31,    44,    33,    34,    -1,
      36,    26,    50,    69,    -1,    -1,    31,    -1,    44,    34,
       3,    36,     5,     6,    50,    -1,    -1,    10,    -1,    44,
      86,    87,    88,    89,    -1,    50,    69,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    82,
      83,    84,    85,    86,    87,    88,    89,    40,    41,    42,
      69,    -1,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    84,    85,
      86,    87,    88,    89,    -1,    -1,    93,    94,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    69,    -1,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    69,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    69,    -1,    -1,    -1,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    69,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    69,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,   104,   118,     0,     7,    12,    26,    31,    33,
      34,    36,    44,    50,   102,   107,   108,   110,   111,   115,
     116,   117,   119,   123,     3,     5,     6,    10,    12,    40,
      41,    42,   105,    12,   118,   116,   116,   110,   118,     5,
       7,    12,    33,    84,    85,    90,    91,    92,   105,   126,
     127,   128,   129,   128,   105,   127,    14,    73,   109,     9,
      11,    71,    72,   112,   113,   114,   118,   118,   127,   116,
     116,   116,    29,    18,   115,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    93,    94,   124,   125,
     127,   127,   127,   127,   127,   127,     5,    51,    52,    53,
      54,    55,    56,    57,    69,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    37,    45,    13,   103,     9,     9,
     108,     9,     9,     9,   111,   111,   105,   106,   103,    13,
      42,    13,   118,   118,   112,   127,   127,    13,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,    13,   105,   118,   116,   116,
      35,    70,    13,    20,   120,   121,    19,   127,   118,    21,
     120,   122,   116,   118,    23,    29,   116,   118,   116
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   101,   102,   103,   104,   105,   105,   105,   105,   105,
     105,   105,   105,   106,   106,   107,   107,   108,   108,   108,
     109,   109,   109,   109,   110,   110,   111,   111,   112,   112,
     112,   113,   113,   113,   114,   114,   114,   114,   115,   115,
     115,   116,   116,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   119,   120,   121,   121,   121,   122,   122,   123,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   125,   126,   126,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   128,   128,   128,   128,   128,   128,   129,   129,   129,
     129,   129,   129
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     3,     1,     1,     3,     3,     3,
       1,     1,     3,     1,     2,     2,     6,     1,     1,     2,
       1,     1,     2,     2,     1,     3,     1,     2,     1,     1,
       2,     1,     1,     2,     1,     1,     2,     2,     1,     3,
       3,     1,     2,     4,     5,     3,     3,     3,     1,     1,
       0,     1,     6,     6,     0,     1,     2,     0,     3,     8,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     3,     2,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3
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
  case 2: /* db_opening_curve: opening_curve opening_curve  */
#line 161 "sh_parser.y"
                                {}
#line 1480 "sh_parser.tab.c"
    break;

  case 3: /* db_closing_curve: closing_curve closing_curve  */
#line 165 "sh_parser.y"
                                {}
#line 1486 "sh_parser.tab.c"
    break;

  case 4: /* input: empty_or_NEWLINE list empty_or_NEWLINE  */
#line 170 "sh_parser.y"
                                           {DBG_MSG("rule:  input -> empty_or_NEWLINE list empty_or_NEWLINE\n"); 
        final_code = (yyvsp[-1].instr);
        printf("[+] I mind it a bash script\n");}
#line 1494 "sh_parser.tab.c"
    break;

  case 5: /* word: NUM  */
#line 179 "sh_parser.y"
          {DBG_MSG("rule:  word -> NUM\n");
        list_init(&code_block);
        _list_insert_tail(&code_block, instr_create(MOV,  REGD, (yyvsp[0].string)));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        (yyval.instr)=code_block;
        // dbg_list("word->NUM", $$);
    }
#line 1506 "sh_parser.tab.c"
    break;

  case 6: /* word: EXITCODE  */
#line 186 "sh_parser.y"
               {DBG_MSG("rule:  word -> EXITCODE\n");(yyval.instr)=NULL;}
#line 1512 "sh_parser.tab.c"
    break;

  case 7: /* word: dollar_opening_curve list closing_curve  */
#line 187 "sh_parser.y"
                                              {DBG_MSG("rule:  word -> dollar_opening_curve list closing_curve\n");
    }
#line 1519 "sh_parser.tab.c"
    break;

  case 8: /* word: backtick list backtick  */
#line 190 "sh_parser.y"
                             {DBG_MSG("rule:  word -> backtick list backtick\n");
    
    }
#line 1527 "sh_parser.tab.c"
    break;

  case 9: /* word: dollar_db_opening_curve expr db_closing_curve  */
#line 193 "sh_parser.y"
                                                    {DBG_MSG("rule:  word -> dollar_opening_db_curve expr db_closing_curve\n");
        (yyval.instr)=(yyvsp[-1].instr);
    }
#line 1535 "sh_parser.tab.c"
    break;

  case 10: /* word: VAR  */
#line 196 "sh_parser.y"
          { DBG_MSG("rule:  word -> VAR\n"); 
        list_init(&code_block);
        char* stack_slot_str;
        if (!map_get(&global_vars_map, (yyvsp[0].string), &stack_slot_str)) {
            yyerror("var -> VAR: undeclared variable");
            YYABORT;
        }
        _list_insert_tail(&code_block, instr_create(READ, REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        (yyval.instr)=code_block;
    }
#line 1551 "sh_parser.tab.c"
    break;

  case 11: /* word: VAR_VALUE  */
#line 207 "sh_parser.y"
                { DBG_MSG("rule: word -> VAR_VALUE\n"); 
        list_init(&code_block);
        char* stack_slot_str;
        if (!map_get(&global_vars_map, (yyvsp[0].string), &stack_slot_str)) {
            yyerror("var_value -> VAR_VALUE: undeclared variable");
            YYABORT;
        }
        _list_insert_tail(&code_block, instr_create(READ, REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        (yyval.instr)=code_block;
    }
#line 1567 "sh_parser.tab.c"
    break;

  case 12: /* word: dollar_db_opening_curve expr db_closing_curve  */
#line 218 "sh_parser.y"
                                                    {
        DBG_MSG("rule: word -> dollar_db_opening_curve expr db_closing_curve\n");
        (yyval.instr)=(yyvsp[-1].instr);
    }
#line 1576 "sh_parser.tab.c"
    break;

  case 13: /* words: word  */
#line 226 "sh_parser.y"
         {DBG_MSG("rule:  words -> word\n");
        (yyval.instr)=(yyvsp[0].instr);
        word_cnt=1;
    }
#line 1585 "sh_parser.tab.c"
    break;

  case 14: /* words: words word  */
#line 230 "sh_parser.y"
                 {DBG_MSG("rule:  words -> words word\n");
        list_splice_tail(&(yyvsp[-1].instr), &(yyvsp[0].instr));
        (yyval.instr)=(yyvsp[-1].instr);
        word_cnt++;
    }
#line 1595 "sh_parser.tab.c"
    break;

  case 15: /* assignment_structure: assignment word  */
#line 240 "sh_parser.y"
                                 { DBG_MSG("rule: assignment_structure -> assignment word\n"); 
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        char* stack_slot_str = alloc_global_var((yyvsp[-1].string));
        _list_insert_tail(&code_block, instr_create(POP, REGD, NULL));
        _list_insert_tail(&code_block, instr_create(WRITE, REGD, stack_slot_str));     
        (yyval.instr)=code_block; 
    }
#line 1608 "sh_parser.tab.c"
    break;

  case 16: /* assignment_structure: assignment opening_curve empty_or_NEWLINE words empty_or_NEWLINE closing_curve  */
#line 248 "sh_parser.y"
                                                                                     { 
        DBG_MSG("rule:  assignment_structure -> assignment opening_curve empty_or_NEWLINE arithmetic_exts empty_or_NEWLINE closing_curve\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));

        for (int i=word_cnt-1; i>=0; i--) {
            char* elem_name = create_string((yyvsp[-5].string), i);
            char* stack_slot_str = alloc_global_var(elem_name);
            free(elem_name);
            _list_insert_tail(&code_block, instr_create(POP, REGD, NULL));
            _list_insert_tail(&code_block, instr_create(WRITE, REGD, stack_slot_str));
        }

        (yyval.instr)=code_block;
        word_cnt = 0;
    }
#line 1629 "sh_parser.tab.c"
    break;

  case 17: /* command: compound_command  */
#line 268 "sh_parser.y"
                            { DBG_MSG("rule:  command -> compound_command\n"); 
        (yyval.instr)=(yyvsp[0].instr); // command and compound_command are in charge for converting return value into exit code
    }
#line 1637 "sh_parser.tab.c"
    break;

  case 18: /* command: assignment_structure  */
#line 271 "sh_parser.y"
                            { DBG_MSG("rule:  command -> assignment_structure\n"); 
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        _list_insert_tail(&code_block, instr_create(PUSH,zero_str, NULL));
        (yyval.instr)=code_block;
    }
#line 1648 "sh_parser.tab.c"
    break;

  case 19: /* command: echo word  */
#line 277 "sh_parser.y"
                            { DBG_MSG("rule:  command -> echo word\n"); 
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        _list_insert_tail(&code_block, instr_create(POP, REGD, NULL));
        _list_insert_tail(&code_block, instr_create(OUT, REGD, NULL));
        _list_insert_tail(&code_block, instr_create(PUSH,zero_str, NULL));
        (yyval.instr)=code_block;  
    }
#line 1661 "sh_parser.tab.c"
    break;

  case 20: /* pipeline_members_connector: stick  */
#line 291 "sh_parser.y"
                                  { DBG_MSG("rule: pipeline_members_connector -> stick\n"); }
#line 1667 "sh_parser.tab.c"
    break;

  case 21: /* pipeline_members_connector: stick_ampersand  */
#line 292 "sh_parser.y"
                                  { DBG_MSG("rule: pipeline_members_connector -> stick_ampersand\n"); }
#line 1673 "sh_parser.tab.c"
    break;

  case 22: /* pipeline_members_connector: stick NEWLINE  */
#line 293 "sh_parser.y"
                                  { DBG_MSG("rule: pipeline_members_connector -> stick NEWLINE\n"); }
#line 1679 "sh_parser.tab.c"
    break;

  case 23: /* pipeline_members_connector: stick_ampersand NEWLINE  */
#line 294 "sh_parser.y"
                                  { DBG_MSG("rule: pipeline_members_connector -> stick_ampersand NEWLINE\n"); }
#line 1685 "sh_parser.tab.c"
    break;

  case 24: /* pipeline_body: command  */
#line 298 "sh_parser.y"
            {DBG_MSG("rule:  pipeline_body -> command\n");
        (yyval.instr)=(yyvsp[0].instr);
    }
#line 1693 "sh_parser.tab.c"
    break;

  case 25: /* pipeline_body: pipeline_body pipeline_members_connector command  */
#line 301 "sh_parser.y"
                                                       {DBG_MSG("rule:  pipeline_body -> pipeline_body pipeline_members_connector command\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        // pop out an exit code of previous pipeline
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        (yyval.instr)=code_block;
    }
#line 1706 "sh_parser.tab.c"
    break;

  case 26: /* pipeline: pipeline_body  */
#line 312 "sh_parser.y"
                  {DBG_MSG("rule:  pipeline -> pipeline_body\n");
        (yyval.instr)=(yyvsp[0].instr);
    }
#line 1714 "sh_parser.tab.c"
    break;

  case 27: /* pipeline: _exclamation_mark pipeline_body  */
#line 315 "sh_parser.y"
                                      {DBG_MSG("rule:  pipeline -> _exclamation_mark pipeline_body\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        // pop out an exit code of previous pipeline
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        _list_insert_tail(&code_block, instr_create(MOV,  REGA,  one_str));
        // command is highly expected to return exit code, not a return value
        _list_insert_tail(&code_block, instr_create(SUB,  REGA,  REGD));
        _list_insert_tail(&code_block, instr_create(PUSH, REGA,  NULL));
        (yyval.instr)=code_block;
    }
#line 1730 "sh_parser.tab.c"
    break;

  case 28: /* list_tail: semicolon  */
#line 331 "sh_parser.y"
                            {DBG_MSG("rule:  list_tail -> semicolon\n");}
#line 1736 "sh_parser.tab.c"
    break;

  case 29: /* list_tail: NEWLINE  */
#line 332 "sh_parser.y"
                            {DBG_MSG("rule:  list_tail -> NEWLINE\n");}
#line 1742 "sh_parser.tab.c"
    break;

  case 30: /* list_tail: semicolon NEWLINE  */
#line 333 "sh_parser.y"
                            {DBG_MSG("rule:  list_tail -> semicolon NEWLINE\n");}
#line 1748 "sh_parser.tab.c"
    break;

  case 31: /* list_members_connector_pri_2: semicolon  */
#line 336 "sh_parser.y"
                            { DBG_MSG("rule:  list_members_connector_pri_2 -> semicolon\n"); }
#line 1754 "sh_parser.tab.c"
    break;

  case 32: /* list_members_connector_pri_2: NEWLINE  */
#line 337 "sh_parser.y"
                            { DBG_MSG("rule:  list_members_connector_pri_2 -> NEWLINE\n"); }
#line 1760 "sh_parser.tab.c"
    break;

  case 33: /* list_members_connector_pri_2: semicolon NEWLINE  */
#line 338 "sh_parser.y"
                            { DBG_MSG("rule:  list_members_connector_pri_2 -> semicolon NEWLINE\n"); }
#line 1766 "sh_parser.tab.c"
    break;

  case 34: /* list_members_connector_pri_1: db_ampersand  */
#line 341 "sh_parser.y"
                            { DBG_MSG("rule:  list_members_connector_pri_1 -> db_ampersand\n"); (yyval.string)=JZ;}
#line 1772 "sh_parser.tab.c"
    break;

  case 35: /* list_members_connector_pri_1: db_stick  */
#line 342 "sh_parser.y"
                            { DBG_MSG("rule:  list_members_connector_pri_1 -> db_stick\n"); (yyval.string)=JNZ;}
#line 1778 "sh_parser.tab.c"
    break;

  case 36: /* list_members_connector_pri_1: db_ampersand NEWLINE  */
#line 343 "sh_parser.y"
                            { DBG_MSG("rule:  list_members_connector_pri_1 -> db_ampersand NEWLINE\n"); (yyval.string)=JZ;}
#line 1784 "sh_parser.tab.c"
    break;

  case 37: /* list_members_connector_pri_1: db_stick NEWLINE  */
#line 344 "sh_parser.y"
                            { DBG_MSG("rule:  list_members_connector_pri_1 -> db_stick NEWLINE\n"); (yyval.string)=JNZ;}
#line 1790 "sh_parser.tab.c"
    break;

  case 38: /* list_body: pipeline  */
#line 348 "sh_parser.y"
               {DBG_MSG("rule:  list_body -> pipeline\n");
        (yyval.instr)=(yyvsp[0].instr);
    }
#line 1798 "sh_parser.tab.c"
    break;

  case 39: /* list_body: list_body list_members_connector_pri_1 pipeline  */
#line 351 "sh_parser.y"
                                                                       {DBG_MSG("rule:  list_body -> list_body list_members_connector_pri_1 pipeline\n");
        if (!list_end_label) {
            list_end_label = create_named_string("__list_end");
        }
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));      
        _list_insert_tail(&code_block, instr_create(POP, REGD,           NULL));
        _list_insert_tail(&code_block, instr_create(CMP, REGD,           one_str));
        _list_insert_tail(&code_block, instr_create((yyvsp[-1].string),  list_end_label, NULL));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        (yyval.instr)=code_block;
    }
#line 1815 "sh_parser.tab.c"
    break;

  case 40: /* list_body: list_body list_members_connector_pri_2 pipeline  */
#line 363 "sh_parser.y"
                                                                       {DBG_MSG("rule:  list_body -> list_body list_members_connector_pri_2 pipeline\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        // pop out an exit code of previous list
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        (yyval.instr)=code_block;
    }
#line 1828 "sh_parser.tab.c"
    break;

  case 41: /* list: list_body  */
#line 377 "sh_parser.y"
              {DBG_MSG("rule:  list -> list_body\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        if (list_end_label) {
            _list_insert_tail(&code_block, instr_create(list_end_label, NULL, NULL));
            list_end_label = NULL;
        }
            
        (yyval.instr)=code_block;
            
    }
#line 1844 "sh_parser.tab.c"
    break;

  case 42: /* list: list_body list_tail  */
#line 388 "sh_parser.y"
                          {DBG_MSG("rule:  list -> list_body list_tail\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-1].instr));
        if (list_end_label) {
            _list_insert_tail(&code_block, instr_create(list_end_label, NULL, NULL));
            list_end_label = NULL;
        }
        (yyval.instr)=code_block;
    }
#line 1858 "sh_parser.tab.c"
    break;

  case 43: /* compound_command: opening_curve empty_or_NEWLINE list closing_curve  */
#line 402 "sh_parser.y"
                                                                               {DBG_MSG("rule:  compound_command -> opening_curve empty_or_NEWLINE list closing_curve\n");
        (yyval.instr)=(yyvsp[-1].instr);
    }
#line 1866 "sh_parser.tab.c"
    break;

  case 44: /* compound_command: _opening_brace empty_or_NEWLINE list_body list_tail _closing_brace  */
#line 405 "sh_parser.y"
                                                                               {DBG_MSG("rule:  compound_command -> _opening_brace empty_or_NEWLINE list_body list_tail _closing_brace\n");
        (yyval.instr)=(yyvsp[-2].instr);
    }
#line 1874 "sh_parser.tab.c"
    break;

  case 45: /* compound_command: db_opening_curve expr db_closing_curve  */
#line 408 "sh_parser.y"
                                                                               {DBG_MSG("rule:  compound_command -> db_opening_curve expr db_closing_curve\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-1].instr));
        convert_to_exitcode(&code_block);
        (yyval.instr)=code_block;  
    }
#line 1885 "sh_parser.tab.c"
    break;

  case 46: /* compound_command: _db_opening_square_bracket cmp_expr_squared _db_closing_square_bracket  */
#line 414 "sh_parser.y"
                                                                                        {DBG_MSG("rule:  compound_command -> _db_opening_square_bracket cmp_expr_squared _db_closing_square_bracket\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-1].instr));
        convert_to_exitcode(&code_block);
        (yyval.instr)=code_block;
    }
#line 1896 "sh_parser.tab.c"
    break;

  case 47: /* compound_command: opening_square_bracket cmp_expr_squared closing_square_bracket  */
#line 420 "sh_parser.y"
                                                                                        {DBG_MSG("rule:  compound_command -> opening_square_bracket cmp_expr_squared closing_square_bracket\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-1].instr));
        convert_to_exitcode(&code_block);
        (yyval.instr)=code_block;
    }
#line 1907 "sh_parser.tab.c"
    break;

  case 48: /* compound_command: if_structure  */
#line 426 "sh_parser.y"
                   {DBG_MSG("rule:  compound_command -> if_structure\n");
    
    }
#line 1915 "sh_parser.tab.c"
    break;

  case 49: /* compound_command: while_cycle  */
#line 429 "sh_parser.y"
                  { DBG_MSG("rule:  compound_command -> while_cycle\n"); 
        (yyval.instr)=(yyvsp[0].instr);
    }
#line 1923 "sh_parser.tab.c"
    break;

  case 50: /* empty_or_NEWLINE: %empty  */
#line 443 "sh_parser.y"
                                { DBG_MSG("rule:  empty_or_NEWLINE -> /* empty */\n"); }
#line 1929 "sh_parser.tab.c"
    break;

  case 51: /* empty_or_NEWLINE: NEWLINE  */
#line 444 "sh_parser.y"
                                { DBG_MSG("rule:  empty_or_NEWLINE -> NEWLINE\n"); }
#line 1935 "sh_parser.tab.c"
    break;

  case 52: /* while_cycle: _while list _do empty_or_NEWLINE list _done  */
#line 451 "sh_parser.y"
                                                { DBG_MSG("rule:  while_cycle -> _while list _do empty_or_NEWLINE list _done\n"); 
        char* check = create_named_string("__chk_while_cond");
        char* end = create_named_string("__while_end");
        char* start = create_named_string("__while_start");
        char* action = create_named_string("__while_action");
        list_init(&code_block);
        _list_insert_tail(&code_block, instr_create(start,NULL,  NULL));
        // adding one push is cheeper than adding the double block
        _list_insert_tail(&code_block, instr_create(PUSH, one_str, NULL));
        _list_insert_tail(&code_block, instr_create(check,NULL,  NULL));
        list_splice_tail(&code_block, &(yyvsp[-4].instr));
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        _list_insert_tail(&code_block, instr_create(CMP,  REGD,  one_str));
        _list_insert_tail(&code_block, instr_create(JZ,   end,   NULL));
        /* pop regd aligns stack clearing stack of the exit code of the PREVIOUS list2*/
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        _list_insert_tail(&code_block, instr_create(action,NULL,  NULL));
        list_splice_tail(&code_block, &(yyvsp[-1].instr));
        _list_insert_tail(&code_block, instr_create(JMP,  check, NULL));
        _list_insert_tail(&code_block, instr_create(end,  NULL,  NULL));
        //convert_to_exitcode(&code_block);
        (yyval.instr)=code_block;
    }
#line 1963 "sh_parser.tab.c"
    break;

  case 53: /* elif_structure: _elif empty_or_NEWLINE list _then empty_or_NEWLINE list  */
#line 480 "sh_parser.y"
                                                              {DBG_MSG("rule:  elif_structure -> _elif empty_or_NEWLINE list _then empty_or_NEWLINE list\n");
        if (!if_end_label) {
            if_end_label = create_named_string("__if_end");
        }
        char* next = create_named_string("__elif_next");
        char* end = create_named_string("__elif_end");
        char* start = create_named_string("__elif_start");

        list_init(&code_block);
        _list_insert_tail(&code_block, instr_create(start,NULL,  NULL));
        
        list_splice_tail(&code_block, &(yyvsp[-3].instr));
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        _list_insert_tail(&code_block, instr_create(CMP,  REGD,  one_str));
        _list_insert_tail(&code_block, instr_create(JZ,   next,   NULL));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        _list_insert_tail(&code_block, instr_create(JMP,  if_end_label, NULL));
        
        _list_insert_tail(&code_block, instr_create(next,  NULL,  NULL));
        
        _list_insert_tail(&code_block, instr_create(end,NULL,  NULL));
        (yyval.instr)=code_block;
    }
#line 1991 "sh_parser.tab.c"
    break;

  case 54: /* elif_structures: %empty  */
#line 506 "sh_parser.y"
    {DBG_MSG("rule:  elif_structures -> empty\n");
        (yyval.instr)=NULL;
    }
#line 1999 "sh_parser.tab.c"
    break;

  case 55: /* elif_structures: elif_structure  */
#line 509 "sh_parser.y"
                     {DBG_MSG("rule:  elif_structures -> elif_structure\n");
        (yyval.instr)=(yyvsp[0].instr);
    }
#line 2007 "sh_parser.tab.c"
    break;

  case 56: /* elif_structures: elif_structures elif_structure  */
#line 512 "sh_parser.y"
                                     {DBG_MSG("rule:  elif_structures -> elif_structures elif_structure\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-1].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        (yyval.instr)=code_block;
    }
#line 2018 "sh_parser.tab.c"
    break;

  case 57: /* else_structure: %empty  */
#line 521 "sh_parser.y"
    {DBG_MSG("rule:  else_structure -> empty\n");
        (yyval.instr)=NULL;
    }
#line 2026 "sh_parser.tab.c"
    break;

  case 58: /* else_structure: _else empty_or_NEWLINE list  */
#line 524 "sh_parser.y"
                                  {DBG_MSG("rule:  else_structure -> _else empty_or_NEWLINE list\n");
        if (!if_end_label) {
            if_end_label = create_named_string("__if_end");
        }
        char* end = create_named_string("__else_end");
        char* start = create_named_string("__else_start");

        list_init(&code_block);
        _list_insert_tail(&code_block, instr_create(start,NULL,  NULL));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        _list_insert_tail(&code_block, instr_create(end,NULL,  NULL));
        (yyval.instr)=code_block;
    }
#line 2044 "sh_parser.tab.c"
    break;

  case 59: /* if_structure: _if list _then empty_or_NEWLINE list elif_structures else_structure _fi  */
#line 543 "sh_parser.y"
                                                                             {DBG_MSG("rule:  if_structure -> _if list _then list elif_structures else_structure _fi\n");
        char* end =  create_named_string("__if_end_qwe");
        char* start = create_named_string("__if_start");
        char* next = create_named_string("__if_next");

        list_init(&code_block);
        _list_insert_tail(&code_block, instr_create(start,NULL,  NULL));
        
        list_splice_tail(&code_block, &(yyvsp[-6].instr));
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        _list_insert_tail(&code_block, instr_create(CMP,  REGD,  one_str));

        if (if_end_label) {
            _list_insert_tail(&code_block, instr_create(JZ,   next,   NULL));
            list_splice_tail(&code_block, &(yyvsp[-3].instr));
            _list_insert_tail(&code_block, instr_create(JMP,  if_end_label, NULL));
            _list_insert_tail(&code_block, instr_create(next,  NULL,  NULL));
            list_splice_tail(&code_block, &(yyvsp[-2].instr));
            if ((yyvsp[-1].instr)) {
                list_splice_tail(&code_block, &(yyvsp[-1].instr));
            }
            else {
                _list_insert_tail(&code_block, instr_create(PUSH,  zero_str, NULL));
            }
            
            _list_insert_tail(&code_block, instr_create(if_end_label,  NULL,  NULL));
            if_end_label = NULL;
        }
        else {
            if_end_label = create_named_string("__if_end");
            _list_insert_tail(&code_block, instr_create(JZ,   next,   NULL));
            list_splice_tail(&code_block, &(yyvsp[-3].instr));
            _list_insert_tail(&code_block, instr_create(JMP,  if_end_label, NULL));
            _list_insert_tail(&code_block, instr_create(next,  NULL,  NULL));
            _list_insert_tail(&code_block, instr_create(PUSH,  zero_str, NULL));
            _list_insert_tail(&code_block, instr_create(if_end_label,  NULL,  NULL));
            if_end_label = NULL;
        }
        

        _list_insert_tail(&code_block, instr_create(end, NULL,  NULL));
        (yyval.instr)=code_block;
    }
#line 2092 "sh_parser.tab.c"
    break;

  case 60: /* op_eq: mul_eq  */
#line 592 "sh_parser.y"
                    { DBG_MSG("rule:  op_eq -> mul_eq\n"); (yyval.string)=MUL;}
#line 2098 "sh_parser.tab.c"
    break;

  case 61: /* op_eq: div_eq  */
#line 593 "sh_parser.y"
                    { DBG_MSG("rule:  op_eq -> div_eq\n"); (yyval.string)=DIV;}
#line 2104 "sh_parser.tab.c"
    break;

  case 62: /* op_eq: mod_eq  */
#line 594 "sh_parser.y"
                    { DBG_MSG("rule:  op_eq -> mod_eq\n"); (yyval.string)=MOD;}
#line 2110 "sh_parser.tab.c"
    break;

  case 63: /* op_eq: plus_eq  */
#line 595 "sh_parser.y"
                    { DBG_MSG("rule:  op_eq -> plus_eq\n"); (yyval.string)=ADD;}
#line 2116 "sh_parser.tab.c"
    break;

  case 64: /* op_eq: minus_eq  */
#line 596 "sh_parser.y"
                    { DBG_MSG("rule:  op_eq -> minus_eq\n"); (yyval.string)=SUB;}
#line 2122 "sh_parser.tab.c"
    break;

  case 65: /* op_eq: shl_eq  */
#line 597 "sh_parser.y"
                    { DBG_MSG("rule:  op_eq -> shl_eq\n"); (yyval.string)=SHL;}
#line 2128 "sh_parser.tab.c"
    break;

  case 66: /* op_eq: shr_eq  */
#line 598 "sh_parser.y"
                    { DBG_MSG("rule:  op_eq -> shr_eq\n"); (yyval.string)=SHR;}
#line 2134 "sh_parser.tab.c"
    break;

  case 67: /* op_eq: ampersand_eq  */
#line 599 "sh_parser.y"
                    { DBG_MSG("rule:  op_eq -> ampersand_eq\n"); (yyval.string)=AND;}
#line 2140 "sh_parser.tab.c"
    break;

  case 68: /* op_eq: xor_eq  */
#line 600 "sh_parser.y"
                    { DBG_MSG("rule:  op_eq -> xor_eq\n"); (yyval.string)=XOR;}
#line 2146 "sh_parser.tab.c"
    break;

  case 69: /* op_eq: stick_eq  */
#line 601 "sh_parser.y"
                    { DBG_MSG("rule:  op_eq -> stick_eq\n"); (yyval.string)=OR;}
#line 2152 "sh_parser.tab.c"
    break;

  case 70: /* post_c_op: post_inc  */
#line 605 "sh_parser.y"
               {DBG_MSG("rule:  post_c_op -> post_inc\n"); (yyval.string)=ADD;}
#line 2158 "sh_parser.tab.c"
    break;

  case 71: /* post_c_op: post_dec  */
#line 606 "sh_parser.y"
               {DBG_MSG("rule:  post_c_op -> post_dec\n"); (yyval.string)=SUB;}
#line 2164 "sh_parser.tab.c"
    break;

  case 72: /* pre_c_op: pre_inc  */
#line 610 "sh_parser.y"
              {DBG_MSG("rule:  pre_c_op -> pre_inc\n"); (yyval.string)=ADD;}
#line 2170 "sh_parser.tab.c"
    break;

  case 73: /* pre_c_op: pre_dec  */
#line 611 "sh_parser.y"
              {DBG_MSG("rule:  pre_c_op -> pre_dec\n"); (yyval.string)=SUB;}
#line 2176 "sh_parser.tab.c"
    break;

  case 74: /* expr: word  */
#line 620 "sh_parser.y"
           {DBG_MSG("rule:  expr -> word\n");
        (yyval.instr)=(yyvsp[0].instr);
    }
#line 2184 "sh_parser.tab.c"
    break;

  case 75: /* expr: assignment expr  */
#line 623 "sh_parser.y"
                                           { DBG_MSG("rule: expr -> assignment word\n"); 
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        char* stack_slot_str = alloc_global_var((yyvsp[-1].string));
        _list_insert_tail(&code_block, instr_create(POP, REGD, NULL));
        _list_insert_tail(&code_block, instr_create(WRITE, REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));    
        (yyval.instr)=code_block; 
    }
#line 2198 "sh_parser.tab.c"
    break;

  case 76: /* expr: VAR eq expr  */
#line 632 "sh_parser.y"
                                       {DBG_MSG("rule:  expr -> expr eq expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        char* stack_slot_str = alloc_global_var((yyvsp[-2].string));
        _list_insert_tail(&code_block, instr_create(POP,  REGD, NULL));
        _list_insert_tail(&code_block, instr_create(WRITE,REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        (yyval.instr)=code_block;
    }
#line 2212 "sh_parser.tab.c"
    break;

  case 77: /* expr: VAR op_eq expr  */
#line 641 "sh_parser.y"
                     {DBG_MSG("rule:  expr -> expr op_eq expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        char* stack_slot_str;
        if (!map_get(&global_vars_map, (yyvsp[-2].string), &stack_slot_str)) {
            yyerror("expr -> VAR post_c_op: undeclared variable");
            YYABORT;
        }
        _list_insert_tail(&code_block, instr_create(POP,  REGD, NULL));
        _list_insert_tail(&code_block, instr_create(READ, REGA, stack_slot_str));
        _list_insert_tail(&code_block, instr_create((yyvsp[-1].string),   REGA, REGD));
        _list_insert_tail(&code_block, instr_create(WRITE,REGA, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGA, NULL));
        (yyval.instr)=code_block;
    }
#line 2232 "sh_parser.tab.c"
    break;

  case 78: /* expr: VAR post_c_op  */
#line 656 "sh_parser.y"
                    {DBG_MSG("rule:  expr -> VAR post_c_op\n");
        list_init(&code_block);
        char* stack_slot_str;
        if (!map_get(&global_vars_map, (yyvsp[-1].string), &stack_slot_str)) {
            yyerror("expr -> VAR post_c_op: undeclared variable");
            YYABORT;
        }
        _list_insert_tail(&code_block, instr_create(READ, REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        _list_insert_tail(&code_block, instr_create((yyvsp[0].string),   REGD, one_str));
        _list_insert_tail(&code_block, instr_create(WRITE,REGD, stack_slot_str));
        (yyval.instr)=code_block;
    }
#line 2250 "sh_parser.tab.c"
    break;

  case 79: /* expr: pre_c_op VAR  */
#line 669 "sh_parser.y"
                   {DBG_MSG("rule:  expr -> pre_c_op VAR\n");
        list_init(&code_block);
        char* stack_slot_str;
        if (!map_get(&global_vars_map, (yyvsp[0].string), &stack_slot_str)) {
            yyerror("expr -> pre_c_op VAR: undeclared variable");
            YYABORT;
        }
        _list_insert_tail(&code_block, instr_create(READ, REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create((yyvsp[-1].string),   REGD, one_str));
        _list_insert_tail(&code_block, instr_create(WRITE,REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        (yyval.instr)=code_block;
    }
#line 2268 "sh_parser.tab.c"
    break;

  case 80: /* expr: minus expr  */
#line 682 "sh_parser.y"
                             { DBG_MSG("rule:  expr -> minus expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        _list_insert_tail(&code_block, instr_create(POP,  REGD, NULL));
        _list_insert_tail(&code_block, instr_create(MUL,  REGD, minus_one_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        (yyval.instr)=code_block;        
    }
#line 2281 "sh_parser.tab.c"
    break;

  case 81: /* expr: plus expr  */
#line 690 "sh_parser.y"
                            { DBG_MSG("rule:  expr -> plus expr\n");
        (yyval.instr)=(yyvsp[0].instr);        
    }
#line 2289 "sh_parser.tab.c"
    break;

  case 82: /* expr: _exclamation_mark expr  */
#line 693 "sh_parser.y"
                             { DBG_MSG("rule:  expr -> _exclamation_mark expr\n");
        char* label_1 = create_named_string("__expr_eq_0_");
        char* label_2 = create_named_string("__exclamation_end");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        _list_insert_tail(&code_block, instr_create(POP,  REGD,     NULL));
        _list_insert_tail(&code_block, instr_create(TEST, REGD,     one_str));
        _list_insert_tail(&code_block, instr_create(JZ,   label_1,  NULL));
        _list_insert_tail(&code_block, instr_create(PUSH, one_str,  NULL));
        _list_insert_tail(&code_block, instr_create(JMP,  label_2,  NULL));
        _list_insert_tail(&code_block, instr_create(label_1, NULL,  NULL));
        _list_insert_tail(&code_block, instr_create(PUSH, zero_str, NULL));
        _list_insert_tail(&code_block, instr_create(label_2, NULL,  NULL));
        (yyval.instr)=code_block;         
    }
#line 2309 "sh_parser.tab.c"
    break;

  case 83: /* expr: tilda expr  */
#line 708 "sh_parser.y"
                 { DBG_MSG("rule:  expr -> tilda expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        _list_insert_tail(&code_block, instr_create(POP,  REGD, NULL));
        _list_insert_tail(&code_block, instr_create(NOT,  REGD, REGD));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        (yyval.instr)=code_block;  
    }
#line 2322 "sh_parser.tab.c"
    break;

  case 84: /* expr: expr minus expr  */
#line 716 "sh_parser.y"
                      {DBG_MSG("rule:  expr -> expr minus expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block, SUB);
        (yyval.instr)=code_block;
    }
#line 2334 "sh_parser.tab.c"
    break;

  case 85: /* expr: expr plus expr  */
#line 723 "sh_parser.y"
                     {DBG_MSG("rule:  expr -> expr minus expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block, ADD);
        (yyval.instr)=code_block;
    }
#line 2346 "sh_parser.tab.c"
    break;

  case 86: /* expr: expr mul expr  */
#line 730 "sh_parser.y"
                    {DBG_MSG("rule:  expr -> expr mul expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block, MUL);
        (yyval.instr)=code_block;
    }
#line 2358 "sh_parser.tab.c"
    break;

  case 87: /* expr: expr division expr  */
#line 737 "sh_parser.y"
                         {DBG_MSG("rule:  expr -> expr division expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block, DIV);
        (yyval.instr)=code_block;
    }
#line 2370 "sh_parser.tab.c"
    break;

  case 88: /* expr: expr mod expr  */
#line 744 "sh_parser.y"
                    {DBG_MSG("rule:  expr -> expr mod expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block,  MOD);
        (yyval.instr)=code_block;
    }
#line 2382 "sh_parser.tab.c"
    break;

  case 89: /* expr: expr shr expr  */
#line 751 "sh_parser.y"
                    {DBG_MSG("rule:  expr -> expr shr expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block,  SHR);
        (yyval.instr)=code_block;
    }
#line 2394 "sh_parser.tab.c"
    break;

  case 90: /* expr: expr shl expr  */
#line 758 "sh_parser.y"
                    {DBG_MSG("rule:  expr -> expr shl expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block,  SHL);
        (yyval.instr)=code_block;
    }
#line 2406 "sh_parser.tab.c"
    break;

  case 91: /* expr: expr ampersand expr  */
#line 765 "sh_parser.y"
                          {DBG_MSG("rule:  expr -> expr ampersand expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block,  AND);
        (yyval.instr)=code_block;
    }
#line 2418 "sh_parser.tab.c"
    break;

  case 92: /* expr: expr stick expr  */
#line 772 "sh_parser.y"
                      {DBG_MSG("rule:  expr -> expr stick expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block, OR );
        (yyval.instr)=code_block;
    }
#line 2430 "sh_parser.tab.c"
    break;

  case 93: /* expr: expr xor expr  */
#line 779 "sh_parser.y"
                    {DBG_MSG("rule:  expr -> expr xor expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block,  XOR);
        (yyval.instr)=code_block;
    }
#line 2442 "sh_parser.tab.c"
    break;

  case 94: /* expr: expr db_ampersand expr  */
#line 786 "sh_parser.y"
                             {DBG_MSG("rule:  expr -> expr db_ampersand expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block,  AND);
        (yyval.instr)=code_block;
    }
#line 2454 "sh_parser.tab.c"
    break;

  case 95: /* expr: expr db_stick expr  */
#line 793 "sh_parser.y"
                         {DBG_MSG("rule:  expr -> expr db_stick expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block,  OR);
        (yyval.instr)=code_block;
    }
#line 2466 "sh_parser.tab.c"
    break;

  case 96: /* expr: expr power expr  */
#line 800 "sh_parser.y"
                      {DBG_MSG("rule:  expr -> expr power expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_bin_op(&code_block,  POW);
        (yyval.instr)=code_block;
    }
#line 2478 "sh_parser.tab.c"
    break;

  case 97: /* expr: cmp_expr_curved  */
#line 807 "sh_parser.y"
                      {DBG_MSG("rule:  expr -> cmp_expr_curved\n");
        (yyval.instr)=(yyvsp[0].instr);
    }
#line 2486 "sh_parser.tab.c"
    break;

  case 98: /* expr: expr question expr colon expr  */
#line 810 "sh_parser.y"
                                                    {DBG_MSG("rule:  expr -> expr question expr colon expr\n");
        char* label_1 = create_named_string("__triple_op_cond_eq_0_");
        char* label_2 = create_named_string("__triple_op_end");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        list_splice_tail(&code_block, &(yyvsp[-4].instr));
        _list_insert_tail(&code_block, instr_create(POP,     REGD,    NULL));
        _list_insert_tail(&code_block, instr_create(TEST,    REGD,    one_str));
        _list_insert_tail(&code_block, instr_create(JZ,      label_1, NULL));
        _list_insert_tail(&code_block, instr_create(POP,     REGD,    NULL));
        _list_insert_tail(&code_block, instr_create(POP,     REGA,    NULL)); 
        _list_insert_tail(&code_block, instr_create(PUSH,    REGD,    NULL)); 
        // extract both expr results from stack and put only expr3 result back in stack
        _list_insert_tail(&code_block, instr_create(label_1, NULL,    NULL));
        _list_insert_tail(&code_block, instr_create(POP,     REGD,    NULL)); 
        // for convention expr result is put into stack for further usage.
        // expr2 result is already in stack. so just clear stack of expr3 result.  
        _list_insert_tail(&code_block, instr_create(label_2, NULL,    NULL));
        (yyval.instr)=code_block;
    }
#line 2512 "sh_parser.tab.c"
    break;

  case 99: /* expr: expr comma expr  */
#line 831 "sh_parser.y"
                      {DBG_MSG("rule:  expr -> expr comma expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        _list_insert_tail(&code_block, instr_create(POP,     REGD,    NULL));
        _list_insert_tail(&code_block, instr_create(POP,     REGA,    NULL)); 
        _list_insert_tail(&code_block, instr_create(PUSH,    REGD,    NULL));
        // only expr2 result matters
        (yyval.instr)=code_block; 
    }
#line 2527 "sh_parser.tab.c"
    break;

  case 100: /* expr: opening_curve expr closing_curve  */
#line 841 "sh_parser.y"
                                       {DBG_MSG("rule:  expr -> opening_curve expr closing_curve\n");
        (yyval.instr)=(yyvsp[-1].instr);
    }
#line 2535 "sh_parser.tab.c"
    break;

  case 101: /* cmp_expr_squared: expr eq_option expr  */
#line 848 "sh_parser.y"
                          {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_eq(&code_block);
        (yyval.instr)=code_block;
    }
#line 2547 "sh_parser.tab.c"
    break;

  case 102: /* cmp_expr_squared: expr ne_option expr  */
#line 855 "sh_parser.y"
                          {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_ne(&code_block);        
        (yyval.instr)=code_block;
    }
#line 2559 "sh_parser.tab.c"
    break;

  case 103: /* cmp_expr_squared: expr lt_option expr  */
#line 862 "sh_parser.y"
                          {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_lt(&code_block);
        (yyval.instr)=code_block;
    }
#line 2571 "sh_parser.tab.c"
    break;

  case 104: /* cmp_expr_squared: expr le_option expr  */
#line 869 "sh_parser.y"
                          {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_le(&code_block);
        (yyval.instr)=code_block;
    }
#line 2583 "sh_parser.tab.c"
    break;

  case 105: /* cmp_expr_squared: expr gt_option expr  */
#line 876 "sh_parser.y"
                          {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_gt(&code_block);
        (yyval.instr)=code_block;
    }
#line 2595 "sh_parser.tab.c"
    break;

  case 106: /* cmp_expr_squared: expr ge_option expr  */
#line 883 "sh_parser.y"
                          {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_ge(&code_block);
        (yyval.instr)=code_block;
    }
#line 2607 "sh_parser.tab.c"
    break;

  case 107: /* cmp_expr_curved: expr db_eq expr  */
#line 893 "sh_parser.y"
                      {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_eq(&code_block);
        (yyval.instr)=code_block;
    }
#line 2619 "sh_parser.tab.c"
    break;

  case 108: /* cmp_expr_curved: expr exclamation_eq expr  */
#line 900 "sh_parser.y"
                               {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_ne(&code_block);        
        (yyval.instr)=code_block;
    }
#line 2631 "sh_parser.tab.c"
    break;

  case 109: /* cmp_expr_curved: expr less expr  */
#line 907 "sh_parser.y"
                     {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_lt(&code_block);
        (yyval.instr)=code_block;
    }
#line 2643 "sh_parser.tab.c"
    break;

  case 110: /* cmp_expr_curved: expr less_eq expr  */
#line 914 "sh_parser.y"
                        {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_le(&code_block);
        (yyval.instr)=code_block;
    }
#line 2655 "sh_parser.tab.c"
    break;

  case 111: /* cmp_expr_curved: expr more expr  */
#line 921 "sh_parser.y"
                     {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_gt(&code_block);
        (yyval.instr)=code_block;
    }
#line 2667 "sh_parser.tab.c"
    break;

  case 112: /* cmp_expr_curved: expr more_eq expr  */
#line 928 "sh_parser.y"
                        {
        list_init(&code_block);
        list_splice_tail(&code_block, &(yyvsp[-2].instr));
        list_splice_tail(&code_block, &(yyvsp[0].instr));
        gen_ge(&code_block);
        (yyval.instr)=code_block;
    }
#line 2679 "sh_parser.tab.c"
    break;


#line 2683 "sh_parser.tab.c"

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

#line 950 "sh_parser.y"


/*
    | db_opening_curve expr db_closing_curve {DBG_MSG("rule:  expr -> db_opening_curve expr db_closing_curve\n");
        $$=$2;
    }
    | dollar_db_opening_curve expr db_closing_curve {DBG_MSG("rule:  expr -> dollar_db_opening_curve expr db_closing_curve\n");
        $$=$2;
    }

          plus {DBG_MSG("rule:  bin_op -> plus\n"); $$=ADD;}
        | minus {DBG_MSG("rule:  bin_op -> minus\n"); $$=SUB;}


*/


int get_stack_slot(int* stack_slot)
{
    return (*stack_slot)++;
}

void free_stack_slot(int* stack_slot)
{
    (*stack_slot)--;
}

char* lltostr(long long value)
{
    char* str = (char*)calloc(20, 1);
    snprintf(str, sizeof(str), "%ld", value);
    return str;
}

int fill_gaps(void)
{
    return 0;
}

void reserve_global_stack(void)
{
    Instruction* ins = instr_create(PUSH, zero_str, NULL);
    int i;
    for (i=0; i<next_global_stack_slot; i++) {
        instr_print(ins, p_output_file);
    }
    free(ins);
}

void yyerror(const char *s) {
    fprintf(stderr, "[-] %s [line: %d]\n", s, yylineno);
}

void write_to_output_file(struct list_node *node, void *arg)
{
    instr_print((Instruction*)node, (FILE*)arg);
}

char* alloc_global_var(char* name)
{
    char* stack_slot_str;
    if (!map_get(&global_vars_map, name, &stack_slot_str)) {
        SLOT_T stack_slot = get_stack_slot(&next_global_stack_slot);
        stack_slot_str = lltostr(stack_slot);
        map_add(&global_vars_map, name, stack_slot_str);
    }
    return stack_slot_str;
}

void gen_bin_op(struct list_node** p_list, char* op)
{
    _list_insert_tail(p_list, instr_create(POP,  REGB, NULL));
    _list_insert_tail(p_list, instr_create(POP,  REGA, NULL));
    _list_insert_tail(p_list, instr_create(op,   REGA, REGB));
    _list_insert_tail(p_list, instr_create(PUSH, REGA, NULL));
}

void convert_to_exitcode(struct list_node** p_list)
{
    char* _zero = create_named_string("__ret_val_eq_0_");
    char* start = create_named_string("__conv_start");
    char* end = create_named_string("__conv_end");
    _list_insert_tail(p_list, instr_create(start, NULL,NULL));
    _list_insert_tail(p_list, instr_create(POP,  REGD,     NULL));
    _list_insert_tail(p_list, instr_create(TEST, REGD,     one_str));
    _list_insert_tail(p_list, instr_create(JZ,   _zero,  NULL));
    _list_insert_tail(p_list, instr_create(PUSH, zero_str, NULL));
    _list_insert_tail(p_list, instr_create(JMP,  end,  NULL));
    _list_insert_tail(p_list, instr_create(_zero, NULL,  NULL));
    _list_insert_tail(p_list, instr_create(PUSH, one_str,  NULL));
    _list_insert_tail(p_list, instr_create(end, NULL,  NULL));
}

void gen_eq(struct list_node** p_list)
{
    char* equal = create_named_string("__equal");
    char* end = create_named_string("__cmp_end");
    _list_insert_tail(p_list, instr_create(POP, REGB, NULL));
    _list_insert_tail(p_list, instr_create(POP, REGA, NULL));
    _list_insert_tail(p_list, instr_create(CMP, REGA, REGB));
    _list_insert_tail(p_list, instr_create(JZ,  equal, NULL));
    _list_insert_tail(p_list, instr_create(PUSH,zero_str, NULL));
    _list_insert_tail(p_list, instr_create(JMP, end,   NULL));
    _list_insert_tail(p_list, instr_create(equal,NULL, NULL));
    _list_insert_tail(p_list, instr_create(PUSH,one_str, NULL));
    _list_insert_tail(p_list, instr_create(end, NULL, NULL));
}

void gen_ne(struct list_node** p_list)
{
    char* equal = create_named_string("__equal");
    char* end = create_named_string("__cmp_end");
    _list_insert_tail(p_list, instr_create(POP, REGB, NULL));
    _list_insert_tail(p_list, instr_create(POP, REGA, NULL));
    _list_insert_tail(p_list, instr_create(CMP, REGA, REGB));
    _list_insert_tail(p_list, instr_create(JZ,  equal, NULL));
    _list_insert_tail(p_list, instr_create(PUSH,one_str, NULL));
    _list_insert_tail(p_list, instr_create(JMP, end,   NULL));
    _list_insert_tail(p_list, instr_create(equal,NULL, NULL));
    _list_insert_tail(p_list, instr_create(PUSH,zero_str, NULL));
    _list_insert_tail(p_list, instr_create(end, NULL, NULL));
}

void gen_lt(struct list_node** p_list)
{
    char* equal = create_named_string("__equal");
    char* end = create_named_string("__cmp_end");
    char* lt = create_named_string("__lt");
    _list_insert_tail(p_list, instr_create(POP, REGB, NULL));
    _list_insert_tail(p_list, instr_create(POP, REGA, NULL));
    _list_insert_tail(p_list, instr_create(SUB, REGA, REGB));
    _list_insert_tail(p_list, instr_create(JZ,  equal, NULL));
    _list_insert_tail(p_list, instr_create(AND, REGA, _0x80000000));
    _list_insert_tail(p_list, instr_create(JNZ, lt,   NULL));
    _list_insert_tail(p_list, instr_create(PUSH,zero_str, NULL));
    _list_insert_tail(p_list, instr_create(JMP, end,   NULL));
    
    _list_insert_tail(p_list, instr_create(lt,  NULL, NULL));
    _list_insert_tail(p_list, instr_create(PUSH,one_str, NULL));
    _list_insert_tail(p_list, instr_create(JMP, end,   NULL));
    
    _list_insert_tail(p_list, instr_create(equal,NULL, NULL));
    _list_insert_tail(p_list, instr_create(PUSH,zero_str, NULL));
    
    _list_insert_tail(p_list, instr_create(end, NULL, NULL));
}

void gen_le(struct list_node** p_list)
{
    char* equal = create_named_string("__equal");
    char* end = create_named_string("__cmp_end");
    char* le = create_named_string("__le");
    _list_insert_tail(p_list, instr_create(POP, REGB,     NULL));
    _list_insert_tail(p_list, instr_create(POP, REGA,     NULL));
    _list_insert_tail(p_list, instr_create(SUB, REGA,     REGB));
    _list_insert_tail(p_list, instr_create(JZ,  equal,    NULL));
    _list_insert_tail(p_list, instr_create(AND, REGA,     _0x80000000));
    _list_insert_tail(p_list, instr_create(JNZ, le,       NULL));
    _list_insert_tail(p_list, instr_create(PUSH,zero_str,  NULL));
    _list_insert_tail(p_list, instr_create(JMP, end,      NULL));
    
    _list_insert_tail(p_list, instr_create(le,  NULL,     NULL));
    _list_insert_tail(p_list, instr_create(PUSH,one_str, NULL));
    _list_insert_tail(p_list, instr_create(JMP, end,      NULL));
    
    _list_insert_tail(p_list, instr_create(equal,NULL,    NULL));
    _list_insert_tail(p_list, instr_create(PUSH, one_str,NULL));
    
    _list_insert_tail(p_list, instr_create(end, NULL,     NULL));
}

void gen_gt(struct list_node** p_list)
{
    char* equal = create_named_string("__equal");
    char* end = create_named_string("__cmp_end");
    char* gt = create_named_string("__gt");
    _list_insert_tail(p_list, instr_create(POP, REGB, NULL));
    _list_insert_tail(p_list, instr_create(POP, REGA, NULL));
    _list_insert_tail(p_list, instr_create(SUB, REGA, REGB));
    _list_insert_tail(p_list, instr_create(JZ,  equal, NULL));
    _list_insert_tail(p_list, instr_create(AND, REGA, _0x80000000));
    _list_insert_tail(p_list, instr_create(JZ,  gt,   NULL));
    _list_insert_tail(p_list, instr_create(PUSH,zero_str, NULL));
    _list_insert_tail(p_list, instr_create(JMP, end,   NULL));
    
    _list_insert_tail(p_list, instr_create(gt,  NULL, NULL));
    _list_insert_tail(p_list, instr_create(PUSH,one_str, NULL));
    _list_insert_tail(p_list, instr_create(JMP, end,   NULL));
    
    _list_insert_tail(p_list, instr_create(equal,NULL, NULL));
    _list_insert_tail(p_list, instr_create(PUSH,zero_str, NULL));
    
    _list_insert_tail(p_list, instr_create(end, NULL, NULL));
}

void gen_ge(struct list_node** p_list)
{
    char* equal = create_named_string("__equal");
    char* end = create_named_string("__cmp_end");
    char* ge = create_named_string("__ge");
    _list_insert_tail(p_list, instr_create(POP, REGB, NULL));
    _list_insert_tail(p_list, instr_create(POP, REGA, NULL));
    _list_insert_tail(p_list, instr_create(SUB, REGA, REGB));
    _list_insert_tail(p_list, instr_create(JZ,  equal, NULL));
    _list_insert_tail(p_list, instr_create(AND, REGA, _0x80000000));
    _list_insert_tail(p_list, instr_create(JZ,  ge,   NULL));
    _list_insert_tail(p_list, instr_create(PUSH,zero_str, NULL));
    _list_insert_tail(p_list, instr_create(JMP, end,   NULL));
    
    _list_insert_tail(p_list, instr_create(ge,  NULL, NULL));
    _list_insert_tail(p_list, instr_create(PUSH,one_str, NULL));
    _list_insert_tail(p_list, instr_create(JMP, end,   NULL));
    
    _list_insert_tail(p_list, instr_create(equal,NULL, NULL));
    _list_insert_tail(p_list, instr_create(PUSH, one_str, NULL));
    
    _list_insert_tail(p_list, instr_create(end, NULL, NULL));
}

void dbg_list(char* str, struct list_node* node)
{
    fprintf(p_output_file, "=====%s\n", str);
    list_foreach(node, write_to_output_file, p_output_file);
    fprintf(p_output_file, "-----\n");
}

// #define ITSELF 

#ifdef ITSELF 

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: yy_parser <.sh> <.basm>\n");
        return 0;
    }

    p_output_file = fopen(argv[2], "w");
    if (!p_output_file) {
        printf("Failed to open output file");
        return 0;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fclose(p_output_file);
        printf("Failed to open input file\n");
        return 0;
    }

    yylineno = 0;

    list_init(&code_block);
    map_init(&global_vars_map, NOT_EXIST_ADD);

    printf("[*] Examining the input...\n");
    int exit_code = yyparse();

    if (exit_code == 0) {
        exit_code = fill_gaps();
    }
    else {
        printf("[-] yyparse() failed\n");
        goto the_end;
    }

    if (exit_code == 0) {
        printf("[*] Writing to output file...\n");
        reserve_global_stack();
        list_foreach(final_code, write_to_output_file, p_output_file);
    }
    else {
        printf("[-] fill_gaps() failed\n");
    }

the_end:

    free_all_strings();
    map_free(&global_vars_map, 1);

    
    fclose(yyin);
    fclose(p_output_file);

    //printf("sh_pars returned %d\n", exit_code);

    return exit_code;
}

#else

int assemble_sh_to_basm(char* input_file, char* output_file)
{
    p_output_file = fopen(output_file, "w");
    if (!p_output_file) {
        printf("Failed to open output file");
        return 0;
    }

    yyin = fopen(input_file, "r");
    if (!yyin) {
        fclose(p_output_file);
        printf("Failed to open input file\n");
        return 0;
    }

    yylineno = 0;

    list_init(&code_block);
    map_init(&global_vars_map, NOT_EXIST_ADD);

    printf("[*] Examining the input...\n");
    int exit_code = yyparse();

    if (exit_code == 0) {
        exit_code = fill_gaps();
    }
    else {
        printf("[-] yyparse() failed\n");
        goto the_end;
    }

    if (exit_code == 0) {
        printf("[*] Writing to output file...\n");
        list_foreach(final_code, write_to_output_file, p_output_file);
    }
    else {
        printf("[-] fill_gaps() failed\n");
    }

the_end:

    map_free(&global_vars_map, 1);

    
    fclose(yyin);
    fclose(p_output_file);

    //printf("sh_pars returned %d\n", exit_code);

    return exit_code;
}

#endif

