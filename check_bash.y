%{


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef DEBUG
    #define DBG_MSG(...) printf(__VA_ARGS__);
#else
    #define DBG_MSG(...) ((void)0)
#endif

#if defined(COLORS)
    #define COLOR_GREEN "\033[1;32m"
    #define COLOR_RED   "\033[1;31m"
    #define COLOR_RESET "\033[0m"
#else
    #define COLOR_GREEN ""
    #define COLOR_RED   ""
    #define COLOR_RESET ""
#endif


typedef enum _error_t {
    NO_ERROR,
    ERROR_RESERVED_WORD_CIRCUMSTANCE,
    ERROR_GOT_UNEXPECTED_WORD,
    ERROR_DESCRIPTOR_RANGE
} _error_t;

_error_t caught_error = NO_ERROR;


char* error_string;
void yyerror(const char *s);
int  yylex(void);

extern int yylineno;
extern int eol_met;

extern FILE *yyin;   // Объявляем переменную Flex (определена в lex.yy.c)
extern int yyparse(); // Функция парсера Bison

%}

%union {
    struct _poly_t* poly;
    long long num;
    char* letters;
    char letter;
}

%token <letters> string pattern assignment
%token <letters> WORD
%token <letters> option
%token <num> number


%type <letters> word
%token <letters> name
%token COMMENT
%token stick ampersand semicolon opening_curve closing_curve more_sign less_sign
%token space tab NEWLINE
%token db_stick stick_ampersand db_ampersand db_semicolon semicolon_ampersand db_semicolon_ampersand

/*reserved words*/

/*
opening reserved words must end with BLANK or metacharacter.
closing reserved words must start with BLANK or metacharacter.
*/

%token  _case  _coproc  _do  _done  _elif  _else  _esac  _fi  _for  _function  _if  _in  _select  _then  _until  _while  _time
%token  _exclamation_mark  _opening_brace  _closing_brace  _opening_db_square_bracket _closing_db_square_bracket

/* _select (допустимо только  _in), либо третьим словом словом команды  _for (допустимы только  _in и  _do)*/

/* my tokens */
%token db_opening_curve db_closing_curve more_sign_ampersand ampersand_more_sign
%token dollar_db_opening_curve dollar_opening_curve backtick less_more
%token opening_square_bracket closing_square_bracket
%token u_cond_op bin_cond_op EQUAL
%token ERROR
%token declaration_command
%token builtin_command_name sudo op_eq

/* ЗАДАТЬ ПРИОРИТЕТ !!! */


%token colon question_sign comma
%token post_inc post_dec inc dec u_minus u_plus tilda
%token power mul division mod plus minus shift_sign l_shift leq_sign geq_sign eq_sign neq_sign
%token bit_and bit_xor bit_or logic_and logic_or b_op



%left ampersand
%left eq_sign neq_sign
%left leq_sign geq_sign more_sign less_sign
%left l_shift shift_sign
%left plus minus
%left mul division mod
%left power

%nonassoc _exclamation_mark tilda
%nonassoc u_plus u_minus
%nonassoc inc dec
%nonassoc post_inc post_dec

%start input

%%

input:
    empty_or_NEWLINE list empty_or_NEWLINE {DBG_MSG("rule:  input -> empty_or_NEWLINE list empty_or_NEWLINE\n"); printf(COLOR_GREEN "[+] i mind it a bash script\n" COLOR_RESET);}
    ;

errors:
    error {
        DBG_MSG("rule:  errors -> error\n"); yyerror("error somewhere");
        yyterminate();
        // yyclearin; yyerrok;
        }
    | ERROR
        {
            DBG_MSG("rule:  errors -> ERROR\n");
            switch (caught_error)
            {               
            case ERROR_RESERVED_WORD_CIRCUMSTANCE:
                yyerror("ERROR_RESERVED_WORD_CIRCUMSTANCE");
                yyterminate();
                break;
            case ERROR_GOT_UNEXPECTED_WORD:
                yyerror("ERROR_GOT_UNEXPECTED_WORD");
                yyterminate();
                break;
            case ERROR_DESCRIPTOR_RANGE:
                yyerror("ERROR_DESCRIPTOR_RANGE");
                yyterminate();
                break;
            }

        }
    ;

/*
между кавычек нет metachars
*/

metacharacter:
    stick {DBG_MSG("rule:  metacharacter -> stick\n");}
    | ampersand {DBG_MSG("rule:  metacharacter -> ampersand\n");}
    | semicolon {DBG_MSG("rule:  metacharacter -> semicolon\n");}
    | opening_curve {DBG_MSG("rule:  metacharacter -> opening_curve\n");}
    | closing_curve {DBG_MSG("rule:  metacharacter -> closing_curve\n");}
    | more_sign {DBG_MSG("rule:  metacharacter -> more_sign\n");}
    | less_sign {DBG_MSG("rule:  metacharacter -> less_sign\n");}
    | space {DBG_MSG("rule:  metacharacter -> space\n");}
    | tab {DBG_MSG("rule:  metacharacter -> tab\n");}
    | NEWLINE {DBG_MSG("rule:  metacharacter -> NEWLINE\n");}
    ;

ctrl_op:
    db_stick {DBG_MSG("rule:  ctrl_op -> db_stick\n");}
    | ampersand {DBG_MSG("rule:  ctrl_op -> ampersand\n");}
    | db_ampersand {DBG_MSG("rule:  ctrl_op -> db_ampersand\n");}
    | semicolon {DBG_MSG("rule:  ctrl_op -> semicolon\n");}
    | db_semicolon {DBG_MSG("rule:  ctrl_op -> db_semicolon\n");}
    | semicolon_ampersand {DBG_MSG("rule:  ctrl_op -> semicolon_ampersand\n");}
    | db_semicolon_ampersand {DBG_MSG("rule:  ctrl_op -> db_semicolon_ampersand\n");}
    | opening_curve {DBG_MSG("rule:  ctrl_op -> opening_curve\n");}
    | closing_curve {DBG_MSG("rule:  ctrl_op -> closing_curve\n");}
    | stick {DBG_MSG("rule:  ctrl_op -> stick\n");}
    | stick_ampersand {DBG_MSG("rule:  ctrl_op -> stick_ampersand\n");}
    | NEWLINE {DBG_MSG("rule:  ctrl_op -> NEWLINE\n");}
    ;

/* delimiting */


/* word */

word: //  word means a unit.
    WORD {DBG_MSG("rule:  word -> WORD\n");}
    | EQUAL {};
    | name {DBG_MSG("rule:  word -> name\n");}
    | pattern {DBG_MSG("rule:  word -> pattern\n");}
    | number {DBG_MSG("rule:  word -> number\n");}
    | option {DBG_MSG("rule:  word -> option\n");}
    | dollar_opening_curve list closing_curve {DBG_MSG("rule:  word -> dollar_opening_curve list closing_curve\n");}
    // | backtick simple_command_body backtick {DBG_MSG("rule:  word -> backtick simple_command_body backtick\n");}
    | backtick list backtick {DBG_MSG("rule:  word -> backtick list backtick\n");}
    | dollar_db_opening_curve expr db_closing_curve {DBG_MSG("rule:  word -> dollar_opening_db_curve expr db_closing_curve\n");}
    ;


words:
    word {DBG_MSG("rule:  words -> word\n");}
    | words word {DBG_MSG("rule:  words -> words word\n");}
    ;

/* variables */

value:
    word { DBG_MSG("rule: value -> word\n");}
    | backtick simple_command_body backtick {DBG_MSG("rule:  word -> backtick simple_command_body backtick\n");}

    ;

values:
    value {DBG_MSG("rule: values -> value\n");}
    | values empty_or_NEWLINE value {
        DBG_MSG("rule: values -> values empty_or_NEWLINE value\n");}
    ;

assignment_structure:
    assignment                    { DBG_MSG("rule: assignment_structure -> assignment\n"); }
    | declaration_command assignment value {DBG_MSG("rule: assignment_structure -> declaration_command assignment value\n");}  
    | declaration_command option name {DBG_MSG("rule: assignment_structure -> declaration_command option name\n");}  
    | assignment value             { DBG_MSG("rule: assignment_structure -> assignment value\n"); }
    | assignment opening_curve empty_or_NEWLINE values empty_or_NEWLINE closing_curve { 
        DBG_MSG("rule: assignment_structure -> assignment opening_curve empty_or_NEWLINE values empty_or_NEWLINE closing_curve\n"); }

    ;

var:
    name {DBG_MSG("rule:  var -> name\n");} // just that  _for a  _while. not sure it is so according to docs
    ;

vars:
    var {DBG_MSG("rule:  vars -> var\n");}
    | vars var {DBG_MSG("rule:  vars -> vars var\n");}
    ;

/* redirection */

desciptor:
    // word {DBG_MSG("rule:  descriptor -> word\n"); 
    //     if (strcmp($1, "1")!=0 && strcmp($1, "2")!=0 && strcmp($1, "3")!=0 &&
    //     strcmp($1, "4")!=0 && strcmp($1, "5")!=0 && strcmp($1, "6")!=0 &&
    //     strcmp($1, "7")!=0 && strcmp($1, "8")!=0 && strcmp($1, "9")!=0
    //     ) {printf("qwe\n"); caught_error = ERROR_DESCRIPTOR_RANGE; YYERROR;}
    //     }
    number {DBG_MSG("token: desciptor -> number\n"); 
            if ($1 < 0 || $1 > 9) {
                yyerror("ERROR_DESCRIPTOR_RANGE"); 
                YYACCEPT;
            }}
    ;

redir_dst:
    word {}
    | opening_curve list closing_curve {}
    ;


redir:
      desciptor  more_sign           word {DBG_MSG("rule:  redir -> descriptor more_sign word\n");}
    | desciptor  less_sign           word {DBG_MSG("rule:  redir -> descriptor less_sign word\n");}
    | desciptor  less_more           word {DBG_MSG("rule:  redir -> desciptor less_more word\n");}
    | desciptor  shift_sign          word {DBG_MSG("rule:  redir -> descriptor shift_sign word\n");}
    | desciptor  more_sign_ampersand desciptor {DBG_MSG("rule:  redir -> descriptor more_sign_ampersand descriptor\n");}
    |            more_sign           redir_dst {DBG_MSG("rule:  redir -> more_sign redir_dst\n");}
    |            less_sign           redir_dst {DBG_MSG("rule:  redir -> less_sign redir_dst\n");}
    |            shift_sign          word {DBG_MSG("rule:  redir -> shift_sign word\n");}
    |            ampersand_more_sign word {DBG_MSG("rule:  redir -> ampersand_more_sign word\n");}
    |            less_more           word {DBG_MSG("rule:  redir -> desciptor less_more word\n");}
    ;

/* command */
command:
    simple_command {}
    | compound_command {}
    | assignment_structure {}
    | builtin_command { DBG_MSG("rule:  command -> builtin_command\n"); }
    | sudo builtin_command { DBG_MSG("rule:  command -> sudo builtin_command\n"); }
    ;


/* simple_command */

simple_command_body:
    word {DBG_MSG("rule:  simple_command_body -> word\n");}
    | redir {DBG_MSG("rule:  simple_command_body -> redir\n");}
    | simple_command_body word {DBG_MSG("rule:  simple_command_body -> simple_command_body word\n");}
    | simple_command_body redir {DBG_MSG("rule:  simple_command_body -> simple_command_body redir\n");}
    | function {DBG_MSG("rule:  simple_command_body -> function\n");}
    ;

simple_command:
    simple_command_body {DBG_MSG("rule:  simple_command -> simple_command_body\n");}
    | sudo simple_command_body {DBG_MSG("rule:  simple_command -> sudo simple_command_body\n");}
/*
i see "name=[value]" considered
*/
    // | vars simple_command_body {DBG_MSG("rule:  simple_command -> vars simple_command_body\n");}
    ;

/* pipeline */

pipeline_head:
       _time {DBG_MSG("rule:  pipeline_head -> _time\n");}
    |  _time option {DBG_MSG("rule:  pipeline_head -> _time -p\n");
            if (strcmp($2, "-p")!=0) {
                yyerror("pipeline: [time [-p]] [!] cmd [[| or |&] cmd ...]");
                YYACCEPT;
            }}
    |  _exclamation_mark {DBG_MSG("rule:  pipeline_head -> _exclamation_mark\n");}
    |  _time _exclamation_mark {DBG_MSG("rule:  pipeline_head -> _time _exclamation_mark\n");}
    |  _time option _exclamation_mark {DBG_MSG("rule:  pipeline_head -> _time -p _exclamation_mark\n");
            if (strcmp($2, "-p")!=0) {
                yyerror("pipeline: [time [-p]] [!] cmd [ [| or |&] cmd ...]");
                YYACCEPT;
            }}
    ;

pipeline_members_connector:
    stick                         { DBG_MSG("rule: pipeline_members_connector -> stick\n"); }
    | stick_ampersand             { DBG_MSG("rule: pipeline_members_connector -> stick_ampersand\n"); }
    | stick NEWLINE              { DBG_MSG("rule: pipeline_members_connector -> stick NEWLINE\n"); }
    | stick_ampersand NEWLINE    { DBG_MSG("rule: pipeline_members_connector -> stick_ampersand NEWLINE\n"); }
    /*
    |& is 2>&1 |
    */
    ;
 
pipeline_body:
    command {DBG_MSG("rule:  pipeline_body -> command\n");}
    | pipeline_body pipeline_members_connector command {DBG_MSG("rule:  pipeline_body -> pipeline_body pipeline_members_connector command\n");}
    ;

pipeline:
    pipeline_body {DBG_MSG("rule:  pipeline -> pipeline_body\n");}
    | pipeline_head pipeline_body {DBG_MSG("rule:  pipeline -> pipeline_head pipeline_body\n");}
    ;

/* list */

/*
РАССТАВЬ ПРИОРИТЕТЫ !!!!!!
В этом списке операторы && и || имеют одинаковый приоритет, а за ними следуют операторы ; и &, которые также имеют одинаковый приоритет.
*/
/*
ВАЖНО для конченных тестов
Если команда завершается управляющим оператором &, то оболочка выполняет команду в фоновом режиме background в подоболочке. Оболочка не ожидает завершения команды и возвращаемый статус равен 0.
*/
/*
шо они имеют в виду
В этом списке операторы && и || имеют одинаковый приоритет, а за ними следуют операторы ; и &, которые также имеют одинаковый приоритет.
Вместо точки с запятой для разделения команд в списке list может присутствовать последовательность из одной или нескольких новых строк.
*/

list_tail:
      semicolon             {DBG_MSG("rule:  list_tail -> semicolon\n");}
    | ampersand             {DBG_MSG("rule:  list_tail -> ampersand\n");}
    | NEWLINE              {DBG_MSG("rule:  list_tail -> NEWLINE\n");}
    | semicolon NEWLINE    {DBG_MSG("rule:  list_tail -> semicolon NEWLINE\n");}
    | ampersand NEWLINE    {DBG_MSG("rule:  list_tail -> ampersand NEWLINE\n");}
    ;

list_members_connector:
    semicolon                     { DBG_MSG("rule: list_members_connector -> semicolon\n"); }
    | ampersand                   { DBG_MSG("rule: list_members_connector -> ampersand\n"); }
    | db_ampersand                { DBG_MSG("rule: list_members_connector -> db_ampersand\n"); }
    | db_stick                    { DBG_MSG("rule: list_members_connector -> db_stick\n"); }
    | NEWLINE                    { DBG_MSG("rule: list_members_connector -> NEWLINE\n"); }
    | semicolon NEWLINE          { DBG_MSG("rule: list_members_connector -> semicolon NEWLINE\n"); }
    | ampersand NEWLINE          { DBG_MSG("rule: list_members_connector -> ampersand NEWLINE\n"); }
    | db_ampersand NEWLINE       { DBG_MSG("rule: list_members_connector -> db_ampersand NEWLINE\n"); }
    | db_stick NEWLINE           { DBG_MSG("rule: list_members_connector -> db_stick NEWLINE\n"); }
    ;

list_body:
      pipeline {DBG_MSG("rule:  list_body -> pipeline\n");}
    | list_body list_members_connector pipeline {DBG_MSG("rule:  list_body -> list_body list_members_connector pipeline\n");}
    ;

list:
/*
i mind it safe if lists are to be delimitted with nothing but list_tail nonterminals
*/
    list_body {DBG_MSG("rule:  list -> list_body\n");}
    | list_body list_tail {DBG_MSG("rule:  list -> list_body list_tail\n");} // it is obvious that list_tail is on the same line as list_body
    ;

/* compound command */

compound_command:
        opening_curve empty_or_NEWLINE list closing_curve {DBG_MSG("rule:  compound_command -> opening_curve empty_or_NEWLINE list closing_curve\n");}
/*
ommitting semicolon in "_opening_brace list semicolon  _closing_brace".
reason:
braces are reserved symbols. thus they are allowed to be near metacharecters.
{ echo 1 & } this is { list & } is VALID
as list ends only on semicolon, ampersand, NEWLINE and empty.
semicolon, ampersand, NEWLINE are metachars
so I m in right to write rule "compound_command: _opening_brace list_body list_tail _closing_brace"
*/

    |  _opening_brace empty_or_NEWLINE list_body list_tail _closing_brace {DBG_MSG("rule:  compound_command -> _opening_brace empty_or_NEWLINE list_body list_tail _closing_brace\n");}


    
/*
хз
Выражение expression расширяется так же, как если бы оно было заключено в двойные кавычки, но неэкранированные символы двойных кавычек в expression не обрабатываются специальным образом и удаляются.
*/
    | db_opening_curve expr db_closing_curve {DBG_MSG("rule:  compound_command -> db_opening_curve expr db_closing_curve\n");}
/*
хз
Слова между [[ и ]] не разделяются на слова и не расширяются названием пути. Оболочка выполняет расширение тильдой, расширение параметров и переменных, арифметическое расширение, замену команд, замену процессов и удаление кавычек в этих словах. Условные операторы, такие как -f, должны быть без кавычек, чтобы их можно было распознать как основные.
При использовании совместно с [[ операторы < и > выполняют лексикографическую сортировку с использованием текущей локали.
Смотрите описание встроенной команды test (в разделе ВСТРОЕННЫЕ КОМАНДЫ ОБОЛОЧКИ) при обработке параметров (т.е. отсутствующих параметров).
*/
/*
ПРОЧИТАТЬ
абзац "Когда используются операторы == и != ..."
*/

/*
что делать с -f
*/
    | _opening_db_square_bracket expr _closing_db_square_bracket {DBG_MSG("rule:  compound_command -> _opening_db_square_bracket expr _closing_db_square_bracket\n");}
    | opening_square_bracket expr closing_square_bracket {DBG_MSG("rule:  compound_command -> opening_square_bracket expr closing_square_bracket\n");}
    | for_cycle_1 {DBG_MSG("rule:  compound_command -> for_cycle_1\n");}
    | for_cycle_2 {DBG_MSG("rule:  compound_command -> for_cycle_2\n");}
    | select_structure { DBG_MSG("rule: command -> select_structure\n"); }
    | case_structure { DBG_MSG("rule: command -> case_structure\n"); }
    | if_structure {DBG_MSG("rule:  compound_command -> if_structure\n");}
    | while_cycle { DBG_MSG("rule:  compound_command -> while_cycle\n"); }
    | until_cycle { DBG_MSG("rule:  compound_command -> until_cycle\n"); }
    ;

/*  _for */

semicolon_or_and_NEWLINE:
    semicolon                     { DBG_MSG("rule: semicolon_or_and_NEWLINE -> semicolon\n"); }
    | NEWLINE                    { DBG_MSG("rule: semicolon_or_and_NEWLINE -> NEWLINE\n"); }
    | semicolon NEWLINE          { DBG_MSG("rule: semicolon_or_and_NEWLINE -> semicolon NEWLINE\n"); }
    ;

empty_or_NEWLINE:
                                  { DBG_MSG("rule: empty_or_NEWLINE -> /* empty */\n"); }
    | NEWLINE                    { DBG_MSG("rule: empty_or_NEWLINE -> NEWLINE\n"); }
    ;

for_cycle_1:
       _for name                                     _do empty_or_NEWLINE list _done {DBG_MSG("rule:  _for name                                 _do empty_or_NEWLINE list _done\n");}
    |  _for name           semicolon_or_and_NEWLINE _do empty_or_NEWLINE list _done {DBG_MSG("rule:  _for name           semicolon_or_and_NEWLINE _do empty_or_NEWLINE list _done\n");}
    |  _for name _in words semicolon_or_and_NEWLINE _do empty_or_NEWLINE list _done {DBG_MSG("rule:  _for name _in words semicolon_or_and_NEWLINE _do empty_or_NEWLINE list _done\n");} 
    ;

for_cycle_2:
       _for db_opening_curve empty_or_NEWLINE expr empty_or_NEWLINE semicolon empty_or_NEWLINE expr empty_or_NEWLINE semicolon empty_or_NEWLINE expr empty_or_NEWLINE db_closing_curve empty_or_NEWLINE _do empty_or_NEWLINE list _done {DBG_MSG("rule:  for_cycle_2 -> _for db_opening_curve empty_or_NEWLINE expr empty_or_NEWLINE semicolon empty_or_NEWLINE expr empty_or_NEWLINE semicolon empty_or_NEWLINE expr empty_or_NEWLINE db_closing_curve empty_or_NEWLINE _do empty_or_NEWLINE list _done\n");}
    |  _for db_opening_curve empty_or_NEWLINE expr empty_or_NEWLINE semicolon empty_or_NEWLINE expr empty_or_NEWLINE semicolon empty_or_NEWLINE expr empty_or_NEWLINE db_closing_curve empty_or_NEWLINE semicolon empty_or_NEWLINE _do empty_or_NEWLINE list _done {DBG_MSG("rule:  for_cycle_2 -> _for db_opening_curve empty_or_NEWLINE expr empty_or_NEWLINE semicolon empty_or_NEWLINE expr empty_or_NEWLINE semicolon empty_or_NEWLINE expr empty_or_NEWLINE db_closing_curve empty_or_NEWLINE semicolon empty_or_NEWLINE  _do empty_or_NEWLINE list _done\n");}
    ;

/*  _select */

select_structure:
    _select name semicolon_or_and_NEWLINE _do empty_or_NEWLINE list _done
        { DBG_MSG("rule: select_structure -> _select name semicolon_or_and_NEWLINE _do empty_or_NEWLINE list _done\n"); }
    | _select name _in words semicolon_or_and_NEWLINE _do empty_or_NEWLINE list _done
        { DBG_MSG("rule: select_structure -> _select name _in words semicolon_or_and_NEWLINE _do empty_or_NEWLINE list _done\n"); }
    ;

/* _case */

patterns:
      word { DBG_MSG("rule: patterns -> word\n"); }
    | patterns stick pattern { DBG_MSG("rule: patterns -> patterns stick pattern\n"); }
    | patterns stick name { DBG_MSG("rule: patterns -> patterns stick name\n"); }
    | mul { DBG_MSG("rule: patterns -> mul\n"); }
    ;

case_branch:
    patterns closing_curve empty_or_NEWLINE list db_semicolon empty_or_NEWLINE
        { DBG_MSG("rule: case_branch -> patterns closing_curve empty_or_NEWLINE list db_semicolon empty_or_NEWLINE\n"); }
    | opening_curve patterns closing_curve empty_or_NEWLINE list db_semicolon empty_or_NEWLINE
        { DBG_MSG("rule: case_branch -> opening_curve patterns closing_curve empty_or_NEWLINE list db_semicolon empty_or_NEWLINE\n"); }
    ;

case_branches:
     case_branch
        { DBG_MSG("rule: case_branches -> case_branch\n"); }
    | case_branches case_branch
        { DBG_MSG("rule: case_branches -> case_branches case_branch\n"); }
    ;

case_structure:
    _case word _in empty_or_NEWLINE _esac
        { DBG_MSG("rule: case_structure -> _case word _in empty_or_NEWLINE _esac\n"); }
    | _case word _in empty_or_NEWLINE case_branches _esac
        { DBG_MSG("rule: case_structure -> _case word _in empty_or_NEWLINE case_branches empty_or_NEWLINE _esac\n"); }
    ;


/*  _while */

while_cycle:
    _while list _do empty_or_NEWLINE list _done
        { DBG_MSG("rule: while_cycle -> _while list _do empty_or_NEWLINE list _done\n"); }
    ;

/* _until */

until_cycle:
    _until list _do empty_or_NEWLINE list _done
        { DBG_MSG("rule: until_cycle -> _until list _do empty_or_NEWLINE list _done\n"); }
    ;

/*  _if */

elif_structure:
     _elif empty_or_NEWLINE list  _then empty_or_NEWLINE list {DBG_MSG("rule:  elif_structure -> _elif empty_or_NEWLINE list _then empty_or_NEWLINE list\n");}
    ;

elif_structures:
    {DBG_MSG("rule:  elif_structures -> empty\n");}
    | elif_structure {DBG_MSG("rule:  elif_structures -> elif_structure\n");}
    | elif_structures elif_structure {DBG_MSG("rule:  elif_structures -> elif_structures elif_structure\n");}
    ;

else_structure:
    {DBG_MSG("rule:  else_structure -> empty");}
    | _else empty_or_NEWLINE list {DBG_MSG("rule:  else_structure -> _else empty_or_NEWLINE list\n");}
    ;

if_structure:
     _if list _then empty_or_NEWLINE list elif_structures else_structure _fi {DBG_MSG("rule:  if_structure -> _if list _then list elif_structures else_structure _fi\n");}
    //  | _if _opening_db_square_bracket expr _closing_db_square_bracket semicolon_or_and_NEWLINE _then empty_or_NEWLINE list elif_structures else_structure _fi {DBG_MSG("rule:  if_structure -> _if _opening_db_square_bracket expr _closing_db_square_bracket semicolon_or_and_NEWLINE _then list elif_structures else_structure _fi\n");}
    ;


/* expression */
post_u_op:
    inc {DBG_MSG("rule:  post_u_op -> inc\n");}
    | dec {DBG_MSG("rule:  post_u_op -> dec\n");}
    ;

pre_u_op:
    inc {DBG_MSG("rule:  pre_u_op -> inc\n");}
    | dec {DBG_MSG("rule:  pre_u_op -> dec\n");}
    | minus {DBG_MSG("rule:  pre_u_op -> minus\n");}
    | plus {DBG_MSG("rule:  pre_u_op -> plus\n");}
    | _exclamation_mark {DBG_MSG("rule:  pre_u_op -> _exclamation_mark\n");}
    | tilda {DBG_MSG("rule:  pre_u_op -> tilda\n");}
    ;

bin_op:
    b_op {DBG_MSG("rule:  bin_op -> b_op\n");}
    | plus {DBG_MSG("rule:  bin_op -> plus\n");}
    | minus {DBG_MSG("rule:  bin_op -> minus\n");}
    | shift_sign {DBG_MSG("rule:  bin_op -> shift_sign\n");}
    | more_sign {DBG_MSG("rule:  bin_op -> more_sign\n");}
    | less_sign {DBG_MSG("rule:  bin_op -> less_sign\n");}
    | ampersand {DBG_MSG("rule:  bin_op -> ampersand\n");}
    | stick {DBG_MSG("rule:  bin_op -> stick\n");}
    | db_ampersand {DBG_MSG("rule:  bin_op -> logic_and\n");}
    | db_stick {DBG_MSG("rule:  bin_op -> logic_or\n");}
    | EQUAL {DBG_MSG("rule: bin_op -> EQUAL\n");}
    ;

expr:
    // var {DBG_MSG("rule:  expr -> var\n");}
      word {DBG_MSG("rule:  expr -> word\n");}
    | expr post_u_op {DBG_MSG("rule:  expr -> expr post_u_op\n");}
    | pre_u_op expr {DBG_MSG("rule:  expr -> pre_u_op expr\n");}
    | expr bin_op expr {DBG_MSG("rule:  expr -> expr bin_op expr\n");}
    | expr op_eq expr {DBG_MSG("rule:  expr -> expr op_eq expr\n");}
    | expr question_sign expr colon expr {DBG_MSG("rule:  expr -> expr question_sign expr colon expr\n");}
/*
оператор ветвления (условие)
= *= /= %= += -= <<= >>= &= ^= |=
назначение, распределение
expr1 , expr2
запятая
*/
/*
перечитать параграф "Когда используются операторы == и != ..."
*/
    | expr comma expr {DBG_MSG("rule:  expr -> expr comma expr\n");}
    | word option word {DBG_MSG("rule:  expr -> word option word\n");}
    | option word {DBG_MSG("rule:  expr -> option word\n");}
    | opening_curve expr closing_curve {DBG_MSG("rule:  expr -> opening_curve expr closing_curve\n");}
    ;

function:
    _function name opening_curve closing_curve empty_or_NEWLINE compound_command {
        DBG_MSG("rule:  function -> _function name opening_curve closing_curve empty_or_NEWLINE compound_command\n");
    }
    | _function name empty_or_NEWLINE compound_command {
        DBG_MSG("rule:  function -> _function name empty_or_NEWLINE compound_command\n");
    }
    | name opening_curve closing_curve empty_or_NEWLINE compound_command {
        DBG_MSG("rule:  function -> name opening_curve closing_curve empty_or_NEWLINE compound_command\n");
    }
    ;

builtin_command:
    builtin_command_name words {DBG_MSG("rule:  builtin_command -> builtin_command_name words\n");}
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, COLOR_RED "[-] %s [line: %d]\n" COLOR_RESET, s, yylineno);
}



int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage:\n\tcheck_bash <file with a bash script>\n");
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror(argv[1]);
        return 1;
    }

    error_string = NULL;
    // yylineno = 0;

    int result = yyparse();

    return result;
}