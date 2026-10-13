/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

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

#ifndef YY_YY_BASM_PARSER_TAB_H_INCLUDED
# define YY_YY_BASM_PARSER_TAB_H_INCLUDED
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
    label = 258,                   /* label  */
    number = 259,                  /* number  */
    NEWLINE = 260,                 /* NEWLINE  */
    ERROR = 261,                   /* ERROR  */
    colon = 262,                   /* colon  */
    rega = 263,                    /* rega  */
    regb = 264,                    /* regb  */
    regc = 265,                    /* regc  */
    regd = 266,                    /* regd  */
    rege = 267,                    /* rege  */
    regf = 268,                    /* regf  */
    regg = 269,                    /* regg  */
    regh = 270,                    /* regh  */
    out = 271,                     /* out  */
    push = 272,                    /* push  */
    pop = 273,                     /* pop  */
    jmp = 274,                     /* jmp  */
    jz = 275,                      /* jz  */
    jnz = 276,                     /* jnz  */
    mov = 277,                     /* mov  */
    add = 278,                     /* add  */
    sub = 279,                     /* sub  */
    mul = 280,                     /* mul  */
    pow = 281,                     /* pow  */
    _div = 282,                    /* _div  */
    mod = 283,                     /* mod  */
    shr = 284,                     /* shr  */
    shl = 285,                     /* shl  */
    or = 286,                      /* or  */
    xor = 287,                     /* xor  */
    and = 288,                     /* and  */
    not = 289,                     /* not  */
    test = 290,                    /* test  */
    cmp = 291,                     /* cmp  */
    read_ = 292,                   /* read_  */
    write_ = 293                   /* write_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 40 "basm_parser.y"

    char* string;
    int num;
    unsigned char opcode;

#line 103 "basm_parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BASM_PARSER_TAB_H_INCLUDED  */
