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

#ifndef YY_YY_SH_PARSER_TAB_H_INCLUDED
# define YY_YY_SH_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
    NUM = 258,                     /* NUM  */
    WORD = 259,                    /* WORD  */
    VAR = 260,                     /* VAR  */
    VAR_VALUE = 261,               /* VAR_VALUE  */
    assignment = 262,              /* assignment  */
    COMMENT = 263,                 /* COMMENT  */
    NEWLINE = 264,                 /* NEWLINE  */
    EXITCODE = 265,                /* EXITCODE  */
    semicolon = 266,               /* semicolon  */
    opening_curve = 267,           /* opening_curve  */
    closing_curve = 268,           /* closing_curve  */
    stick_ampersand = 269,         /* stick_ampersand  */
    semicolon_ampersand = 270,     /* semicolon_ampersand  */
    _case = 271,                   /* _case  */
    _coproc = 272,                 /* _coproc  */
    _do = 273,                     /* _do  */
    _done = 274,                   /* _done  */
    _elif = 275,                   /* _elif  */
    _else = 276,                   /* _else  */
    _esac = 277,                   /* _esac  */
    _fi = 278,                     /* _fi  */
    _for = 279,                    /* _for  */
    _function = 280,               /* _function  */
    _if = 281,                     /* _if  */
    _in = 282,                     /* _in  */
    _select = 283,                 /* _select  */
    _then = 284,                   /* _then  */
    _until = 285,                  /* _until  */
    _while = 286,                  /* _while  */
    _time = 287,                   /* _time  */
    _exclamation_mark = 288,       /* _exclamation_mark  */
    _opening_brace = 289,          /* _opening_brace  */
    _closing_brace = 290,          /* _closing_brace  */
    _db_opening_square_bracket = 291, /* _db_opening_square_bracket  */
    _db_closing_square_bracket = 292, /* _db_closing_square_bracket  */
    more_ampersand = 293,          /* more_ampersand  */
    ampersand_more = 294,          /* ampersand_more  */
    dollar_db_opening_curve = 295, /* dollar_db_opening_curve  */
    dollar_opening_curve = 296,    /* dollar_opening_curve  */
    backtick = 297,                /* backtick  */
    less_more = 298,               /* less_more  */
    opening_square_bracket = 299,  /* opening_square_bracket  */
    closing_square_bracket = 300,  /* closing_square_bracket  */
    u_cond_op = 301,               /* u_cond_op  */
    bin_cond_op = 302,             /* bin_cond_op  */
    ERROR = 303,                   /* ERROR  */
    declaration_command = 304,     /* declaration_command  */
    echo = 305,                    /* echo  */
    eq_option = 306,               /* eq_option  */
    ne_option = 307,               /* ne_option  */
    lt_option = 308,               /* lt_option  */
    le_option = 309,               /* le_option  */
    gt_option = 310,               /* gt_option  */
    ge_option = 311,               /* ge_option  */
    comma = 312,                   /* comma  */
    eq = 313,                      /* eq  */
    mul_eq = 314,                  /* mul_eq  */
    div_eq = 315,                  /* div_eq  */
    mod_eq = 316,                  /* mod_eq  */
    plus_eq = 317,                 /* plus_eq  */
    minus_eq = 318,                /* minus_eq  */
    shl_eq = 319,                  /* shl_eq  */
    shr_eq = 320,                  /* shr_eq  */
    ampersand_eq = 321,            /* ampersand_eq  */
    xor_eq = 322,                  /* xor_eq  */
    stick_eq = 323,                /* stick_eq  */
    question = 324,                /* question  */
    colon = 325,                   /* colon  */
    db_stick = 326,                /* db_stick  */
    db_ampersand = 327,            /* db_ampersand  */
    stick = 328,                   /* stick  */
    xor = 329,                     /* xor  */
    ampersand = 330,               /* ampersand  */
    db_eq = 331,                   /* db_eq  */
    exclamation_eq = 332,          /* exclamation_eq  */
    less_eq = 333,                 /* less_eq  */
    more_eq = 334,                 /* more_eq  */
    more = 335,                    /* more  */
    less = 336,                    /* less  */
    shl = 337,                     /* shl  */
    shr = 338,                     /* shr  */
    plus = 339,                    /* plus  */
    minus = 340,                   /* minus  */
    mul = 341,                     /* mul  */
    division = 342,                /* division  */
    mod = 343,                     /* mod  */
    power = 344,                   /* power  */
    tilda = 345,                   /* tilda  */
    pre_inc = 346,                 /* pre_inc  */
    pre_dec = 347,                 /* pre_dec  */
    post_inc = 348,                /* post_inc  */
    post_dec = 349,                /* post_dec  */
    LIST_PRI_2 = 350,              /* LIST_PRI_2  */
    LIST_PRI_1 = 351,              /* LIST_PRI_1  */
    ASSIGNMENT_PRI = 352,          /* ASSIGNMENT_PRI  */
    TRIPLE_OP = 353,               /* TRIPLE_OP  */
    UNARY = 354,                   /* UNARY  */
    PAREN = 355                    /* PAREN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 66 "sh_parser.y"

    long long num;
    char* string;
    struct list_node *instr;

#line 170 "sh_parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SH_PARSER_TAB_H_INCLUDED  */
