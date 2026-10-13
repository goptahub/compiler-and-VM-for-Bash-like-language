%{

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

%}

%union {
    long long num;
    char* string;
    struct list_node *instr;
}

%token <string> NUM WORD VAR VAR_VALUE assignment

%token COMMENT NEWLINE EXITCODE
%token semicolon opening_curve closing_curve stick_ampersand semicolon_ampersand

%type <instr> expr cmp_expr_squared cmp_expr_curved word words 
%type <instr> assignment_structure
%type <instr> pipeline_body pipeline 
%type <instr> list list_body
%type <instr> command compound_command while_cycle
%type <instr> if_structure elif_structures elif_structure else_structure

%type <string> bin_op pre_c_op post_c_op op_eq list_members_connector_pri_1


/*reserved words*/

/*
opening reserved words must end with BLANK or metacharacter.
closing reserved words must start with BLANK or metacharacter.
*/

%token  _case  _coproc  _do  _done  _elif  _else  _esac  _fi  _for  _function  _if  _in  _select  _then  _until  _while  _time
%token  _exclamation_mark  _opening_brace  _closing_brace  _db_opening_square_bracket _db_closing_square_bracket


/* my tokens */
%token more_ampersand ampersand_more
%token dollar_db_opening_curve dollar_opening_curve backtick less_more
%token opening_square_bracket closing_square_bracket
%token u_cond_op bin_cond_op
%token ERROR
%token declaration_command echo

%token eq_option ne_option lt_option le_option gt_option ge_option
%token comma
%token eq mul_eq div_eq mod_eq plus_eq minus_eq shl_eq shr_eq ampersand_eq xor_eq stick_eq
%token question colon
%token db_stick
%token db_ampersand
%token stick
%token xor
%token ampersand
%token db_eq exclamation_eq
%token less_eq more_eq more less
%token shl shr
%token plus minus
%token mul division mod
%token power
%token tilda
%token pre_inc pre_dec
%token post_inc post_dec

%nonassoc LIST_PRI_2
%nonassoc LIST_PRI_1 

%left eq_option ne_option lt_option le_option gt_option ge_option
%left comma
%right ASSIGNMENT_PRI eq mul_eq div_eq mod_eq plus_eq minus_eq shl_eq shr_eq ampersand_eq xor_eq stick_eq
%right TRIPLE_OP
%left db_stick
%left db_ampersand
%left stick
%left xor
%left ampersand
%left db_eq exclamation_eq
%left less_eq more_eq more less
%left shl shr
%left plus minus
%left mul division mod
%right power

%nonassoc _exclamation_mark tilda
%nonassoc pre_inc pre_dec
%nonassoc post_inc post_dec


%nonassoc UNARY
%nonassoc PAREN



%start input



%%

db_opening_curve:
    opening_curve opening_curve {}
    ;

db_closing_curve:
    closing_curve closing_curve {}
    ;


input:
    empty_or_NEWLINE list empty_or_NEWLINE {DBG_MSG("rule:  input -> empty_or_NEWLINE list empty_or_NEWLINE\n"); 
        final_code = $2;
        printf("[+] I mind it a bash script\n");}
    ;


/* word */

word: //  word means a unit.
      NUM {DBG_MSG("rule:  word -> NUM\n");
        list_init(&code_block);
        _list_insert_tail(&code_block, instr_create(MOV,  REGD, $1));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        $$=code_block;
        // dbg_list("word->NUM", $$);
    }
    | EXITCODE {DBG_MSG("rule:  word -> EXITCODE\n");$$=NULL;}
    | dollar_opening_curve list closing_curve {DBG_MSG("rule:  word -> dollar_opening_curve list closing_curve\n");
    }
    // | backtick simple_command_body backtick {DBG_MSG("rule:  word -> backtick simple_command_body backtick\n");}
    | backtick list backtick {DBG_MSG("rule:  word -> backtick list backtick\n");
    
    }
    | dollar_db_opening_curve expr db_closing_curve {DBG_MSG("rule:  word -> dollar_opening_db_curve expr db_closing_curve\n");
        $$=$2;
    }
    | VAR { DBG_MSG("rule:  word -> VAR\n"); 
        list_init(&code_block);
        char* stack_slot_str;
        if (!map_get(&global_vars_map, $1, &stack_slot_str)) {
            yyerror("var -> VAR: undeclared variable");
            YYABORT;
        }
        _list_insert_tail(&code_block, instr_create(READ, REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        $$=code_block;
    }
    | VAR_VALUE { DBG_MSG("rule: word -> VAR_VALUE\n"); 
        list_init(&code_block);
        char* stack_slot_str;
        if (!map_get(&global_vars_map, $1, &stack_slot_str)) {
            yyerror("var_value -> VAR_VALUE: undeclared variable");
            YYABORT;
        }
        _list_insert_tail(&code_block, instr_create(READ, REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        $$=code_block;
    }
    | dollar_db_opening_curve expr db_closing_curve {
        DBG_MSG("rule: word -> dollar_db_opening_curve expr db_closing_curve\n");
        $$=$2;
    }
    ;


words:
    word {DBG_MSG("rule:  words -> word\n");
        $$=$1;
        word_cnt=1;
    }
    | words word {DBG_MSG("rule:  words -> words word\n");
        list_splice_tail(&$1, &$2);
        $$=$1;
        word_cnt++;
    }
    ;

/* variables */

assignment_structure:
      assignment word            { DBG_MSG("rule: assignment_structure -> assignment word\n"); 
        list_init(&code_block);
        list_splice_tail(&code_block, &$2);
        char* stack_slot_str = alloc_global_var($1);
        _list_insert_tail(&code_block, instr_create(POP, REGD, NULL));
        _list_insert_tail(&code_block, instr_create(WRITE, REGD, stack_slot_str));     
        $$=code_block; 
    }
    | assignment opening_curve empty_or_NEWLINE words empty_or_NEWLINE closing_curve { 
        DBG_MSG("rule:  assignment_structure -> assignment opening_curve empty_or_NEWLINE arithmetic_exts empty_or_NEWLINE closing_curve\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$4);

        for (int i=word_cnt-1; i>=0; i--) {
            char* elem_name = create_string($1, i);
            char* stack_slot_str = alloc_global_var(elem_name);
            free(elem_name);
            _list_insert_tail(&code_block, instr_create(POP, REGD, NULL));
            _list_insert_tail(&code_block, instr_create(WRITE, REGD, stack_slot_str));
        }

        $$=code_block;
        word_cnt = 0;
    }
    ;

    /* command */
command:
      compound_command      { DBG_MSG("rule:  command -> compound_command\n"); 
        $$=$1; // command and compound_command are in charge for converting return value into exit code
    }
    | assignment_structure  { DBG_MSG("rule:  command -> assignment_structure\n"); 
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        _list_insert_tail(&code_block, instr_create(PUSH,zero_str, NULL));
        $$=code_block;
    }
    | echo word             { DBG_MSG("rule:  command -> echo word\n"); 
        list_init(&code_block);
        list_splice_tail(&code_block, &$2);
        _list_insert_tail(&code_block, instr_create(POP, REGD, NULL));
        _list_insert_tail(&code_block, instr_create(OUT, REGD, NULL));
        _list_insert_tail(&code_block, instr_create(PUSH,zero_str, NULL));
        $$=code_block;  
    }
    ;


/* pipeline */

pipeline_members_connector:
      stick                       { DBG_MSG("rule: pipeline_members_connector -> stick\n"); }
    | stick_ampersand             { DBG_MSG("rule: pipeline_members_connector -> stick_ampersand\n"); }
    | stick NEWLINE               { DBG_MSG("rule: pipeline_members_connector -> stick NEWLINE\n"); }
    | stick_ampersand NEWLINE     { DBG_MSG("rule: pipeline_members_connector -> stick_ampersand NEWLINE\n"); }
    ;

pipeline_body:
    command {DBG_MSG("rule:  pipeline_body -> command\n");
        $$=$1;
    }
    | pipeline_body pipeline_members_connector command {DBG_MSG("rule:  pipeline_body -> pipeline_body pipeline_members_connector command\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        // pop out an exit code of previous pipeline
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        list_splice_tail(&code_block, &$3);
        $$=code_block;
    }
    ;

pipeline:
    pipeline_body {DBG_MSG("rule:  pipeline -> pipeline_body\n");
        $$=$1;
    }
    | _exclamation_mark pipeline_body {DBG_MSG("rule:  pipeline -> _exclamation_mark pipeline_body\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$2);
        // pop out an exit code of previous pipeline
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        _list_insert_tail(&code_block, instr_create(MOV,  REGA,  one_str));
        // command is highly expected to return exit code, not a return value
        _list_insert_tail(&code_block, instr_create(SUB,  REGA,  REGD));
        _list_insert_tail(&code_block, instr_create(PUSH, REGA,  NULL));
        $$=code_block;
    }
    ;

/* list */

list_tail:
      semicolon             {DBG_MSG("rule:  list_tail -> semicolon\n");}
    | NEWLINE               {DBG_MSG("rule:  list_tail -> NEWLINE\n");}
    | semicolon NEWLINE     {DBG_MSG("rule:  list_tail -> semicolon NEWLINE\n");}
    ;
list_members_connector_pri_2:
      semicolon             { DBG_MSG("rule:  list_members_connector_pri_2 -> semicolon\n"); }
    | NEWLINE               { DBG_MSG("rule:  list_members_connector_pri_2 -> NEWLINE\n"); }
    | semicolon NEWLINE     { DBG_MSG("rule:  list_members_connector_pri_2 -> semicolon NEWLINE\n"); }
    ;
list_members_connector_pri_1:   
      db_ampersand          { DBG_MSG("rule:  list_members_connector_pri_1 -> db_ampersand\n"); $$=JZ;}
    | db_stick              { DBG_MSG("rule:  list_members_connector_pri_1 -> db_stick\n"); $$=JNZ;}
    | db_ampersand NEWLINE  { DBG_MSG("rule:  list_members_connector_pri_1 -> db_ampersand NEWLINE\n"); $$=JZ;}
    | db_stick NEWLINE      { DBG_MSG("rule:  list_members_connector_pri_1 -> db_stick NEWLINE\n"); $$=JNZ;}
    ;

list_body:
      pipeline {DBG_MSG("rule:  list_body -> pipeline\n");
        $$=$1;
    }
    | list_body list_members_connector_pri_1 pipeline %prec LIST_PRI_1 {DBG_MSG("rule:  list_body -> list_body list_members_connector_pri_1 pipeline\n");
        if (!list_end_label) {
            list_end_label = create_named_string("__list_end");
        }
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);      
        _list_insert_tail(&code_block, instr_create(POP, REGD,           NULL));
        _list_insert_tail(&code_block, instr_create(CMP, REGD,           one_str));
        _list_insert_tail(&code_block, instr_create($2,  list_end_label, NULL));
        list_splice_tail(&code_block, &$3);
        $$=code_block;
    }
    | list_body list_members_connector_pri_2 pipeline %prec LIST_PRI_2 {DBG_MSG("rule:  list_body -> list_body list_members_connector_pri_2 pipeline\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        // pop out an exit code of previous list
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        list_splice_tail(&code_block, &$3);
        $$=code_block;
    }
    ;

list:
/*
i mind it safe if lists are to be delimitted with nothing but list_tail nonterminals
*/
    list_body {DBG_MSG("rule:  list -> list_body\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        if (list_end_label) {
            _list_insert_tail(&code_block, instr_create(list_end_label, NULL, NULL));
            list_end_label = NULL;
        }
            
        $$=code_block;
            
    }
    | list_body list_tail {DBG_MSG("rule:  list -> list_body list_tail\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        if (list_end_label) {
            _list_insert_tail(&code_block, instr_create(list_end_label, NULL, NULL));
            list_end_label = NULL;
        }
        $$=code_block;
    }
    ;


// command and compound_command are in charge for converting return values into exit codes
compound_command:
          opening_curve empty_or_NEWLINE list                    closing_curve {DBG_MSG("rule:  compound_command -> opening_curve empty_or_NEWLINE list closing_curve\n");
        $$=$3;
    }
    |    _opening_brace empty_or_NEWLINE list_body list_tail    _closing_brace {DBG_MSG("rule:  compound_command -> _opening_brace empty_or_NEWLINE list_body list_tail _closing_brace\n");
        $$=$3;
    }
    |  db_opening_curve                  expr                 db_closing_curve {DBG_MSG("rule:  compound_command -> db_opening_curve expr db_closing_curve\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$2);
        convert_to_exitcode(&code_block);
        $$=code_block;  
    }
    | _db_opening_square_bracket         cmp_expr_squared    _db_closing_square_bracket {DBG_MSG("rule:  compound_command -> _db_opening_square_bracket cmp_expr_squared _db_closing_square_bracket\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$2);
        convert_to_exitcode(&code_block);
        $$=code_block;
    }
    |     opening_square_bracket         cmp_expr_squared        closing_square_bracket {DBG_MSG("rule:  compound_command -> opening_square_bracket cmp_expr_squared closing_square_bracket\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$2);
        convert_to_exitcode(&code_block);
        $$=code_block;
    }
    | if_structure {DBG_MSG("rule:  compound_command -> if_structure\n");
    
    }
    | while_cycle { DBG_MSG("rule:  compound_command -> while_cycle\n"); 
        $$=$1;
    }
    ;

/*  _for */

semicolon_or_and_NEWLINE:
    semicolon                   { DBG_MSG("rule:  semicolon_or_and_NEWLINE -> semicolon\n"); }
    | NEWLINE                   { DBG_MSG("rule:  semicolon_or_and_NEWLINE -> NEWLINE\n"); }
    | semicolon NEWLINE         { DBG_MSG("rule:  semicolon_or_and_NEWLINE -> semicolon NEWLINE\n"); }
    ;

empty_or_NEWLINE:
                                { DBG_MSG("rule:  empty_or_NEWLINE -> /* empty */\n"); }
    | NEWLINE                   { DBG_MSG("rule:  empty_or_NEWLINE -> NEWLINE\n"); }
    ;


/*  _while */

while_cycle:
    _while list _do empty_or_NEWLINE list _done { DBG_MSG("rule:  while_cycle -> _while list _do empty_or_NEWLINE list _done\n"); 
        char* check = create_named_string("__chk_while_cond");
        char* end = create_named_string("__while_end");
        char* start = create_named_string("__while_start");
        char* action = create_named_string("__while_action");
        list_init(&code_block);
        _list_insert_tail(&code_block, instr_create(start,NULL,  NULL));
        // adding one push is cheeper than adding the double block
        _list_insert_tail(&code_block, instr_create(PUSH, one_str, NULL));
        _list_insert_tail(&code_block, instr_create(check,NULL,  NULL));
        list_splice_tail(&code_block, &$2);
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        _list_insert_tail(&code_block, instr_create(CMP,  REGD,  one_str));
        _list_insert_tail(&code_block, instr_create(JZ,   end,   NULL));
        /* pop regd aligns stack clearing stack of the exit code of the PREVIOUS list2*/
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        _list_insert_tail(&code_block, instr_create(action,NULL,  NULL));
        list_splice_tail(&code_block, &$5);
        _list_insert_tail(&code_block, instr_create(JMP,  check, NULL));
        _list_insert_tail(&code_block, instr_create(end,  NULL,  NULL));
        //convert_to_exitcode(&code_block);
        $$=code_block;
    }
    ;


/*  _if */

elif_structure:
     _elif empty_or_NEWLINE list  _then empty_or_NEWLINE list {DBG_MSG("rule:  elif_structure -> _elif empty_or_NEWLINE list _then empty_or_NEWLINE list\n");
        if (!if_end_label) {
            if_end_label = create_named_string("__if_end");
        }
        char* next = create_named_string("__elif_next");
        char* end = create_named_string("__elif_end");
        char* start = create_named_string("__elif_start");

        list_init(&code_block);
        _list_insert_tail(&code_block, instr_create(start,NULL,  NULL));
        
        list_splice_tail(&code_block, &$3);
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        _list_insert_tail(&code_block, instr_create(CMP,  REGD,  one_str));
        _list_insert_tail(&code_block, instr_create(JZ,   next,   NULL));
        list_splice_tail(&code_block, &$6);
        _list_insert_tail(&code_block, instr_create(JMP,  if_end_label, NULL));
        
        _list_insert_tail(&code_block, instr_create(next,  NULL,  NULL));
        
        _list_insert_tail(&code_block, instr_create(end,NULL,  NULL));
        $$=code_block;
    }
    ;

elif_structures:
    {DBG_MSG("rule:  elif_structures -> empty\n");
        $$=NULL;
    }
    | elif_structure {DBG_MSG("rule:  elif_structures -> elif_structure\n");
        $$=$1;
    }
    | elif_structures elif_structure {DBG_MSG("rule:  elif_structures -> elif_structures elif_structure\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$2);
        $$=code_block;
    }
    ;

else_structure:
    {DBG_MSG("rule:  else_structure -> empty\n");
        $$=NULL;
    }
    | _else empty_or_NEWLINE list {DBG_MSG("rule:  else_structure -> _else empty_or_NEWLINE list\n");
        if (!if_end_label) {
            if_end_label = create_named_string("__if_end");
        }
        char* end = create_named_string("__else_end");
        char* start = create_named_string("__else_start");

        list_init(&code_block);
        _list_insert_tail(&code_block, instr_create(start,NULL,  NULL));
        list_splice_tail(&code_block, &$3);
        _list_insert_tail(&code_block, instr_create(end,NULL,  NULL));
        $$=code_block;
    }
    ;


    //  | _if _db_opening_square_bracket expr _db_closing_square_bracket semicolon_or_and_NEWLINE _then empty_or_NEWLINE list elif_structures else_structure _fi {DBG_MSG("rule:  if_structure -> _if _db_opening_square_bracket expr _db_closing_square_bracket semicolon_or_and_NEWLINE _then list elif_structures else_structure _fi\n");}

if_structure:
     _if list _then empty_or_NEWLINE list elif_structures else_structure _fi {DBG_MSG("rule:  if_structure -> _if list _then list elif_structures else_structure _fi\n");
        char* end =  create_named_string("__if_end_qwe");
        char* start = create_named_string("__if_start");
        char* next = create_named_string("__if_next");

        list_init(&code_block);
        _list_insert_tail(&code_block, instr_create(start,NULL,  NULL));
        
        list_splice_tail(&code_block, &$2);
        _list_insert_tail(&code_block, instr_create(POP,  REGD,  NULL));
        _list_insert_tail(&code_block, instr_create(CMP,  REGD,  one_str));

        if (if_end_label) {
            _list_insert_tail(&code_block, instr_create(JZ,   next,   NULL));
            list_splice_tail(&code_block, &$5);
            _list_insert_tail(&code_block, instr_create(JMP,  if_end_label, NULL));
            _list_insert_tail(&code_block, instr_create(next,  NULL,  NULL));
            list_splice_tail(&code_block, &$6);
            if ($7) {
                list_splice_tail(&code_block, &$7);
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
            list_splice_tail(&code_block, &$5);
            _list_insert_tail(&code_block, instr_create(JMP,  if_end_label, NULL));
            _list_insert_tail(&code_block, instr_create(next,  NULL,  NULL));
            _list_insert_tail(&code_block, instr_create(PUSH,  zero_str, NULL));
            _list_insert_tail(&code_block, instr_create(if_end_label,  NULL,  NULL));
            if_end_label = NULL;
        }
        

        _list_insert_tail(&code_block, instr_create(end, NULL,  NULL));
        $$=code_block;
    }
    ;


/* expression */

op_eq:
      mul_eq        { DBG_MSG("rule:  op_eq -> mul_eq\n"); $$=MUL;}
    | div_eq        { DBG_MSG("rule:  op_eq -> div_eq\n"); $$=DIV;}
    | mod_eq        { DBG_MSG("rule:  op_eq -> mod_eq\n"); $$=MOD;}
    | plus_eq       { DBG_MSG("rule:  op_eq -> plus_eq\n"); $$=ADD;}
    | minus_eq      { DBG_MSG("rule:  op_eq -> minus_eq\n"); $$=SUB;}
    | shl_eq        { DBG_MSG("rule:  op_eq -> shl_eq\n"); $$=SHL;}
    | shr_eq        { DBG_MSG("rule:  op_eq -> shr_eq\n"); $$=SHR;}
    | ampersand_eq  { DBG_MSG("rule:  op_eq -> ampersand_eq\n"); $$=AND;}
    | xor_eq        { DBG_MSG("rule:  op_eq -> xor_eq\n"); $$=XOR;}
    | stick_eq      { DBG_MSG("rule:  op_eq -> stick_eq\n"); $$=OR;}
    ;

post_c_op:
      post_inc {DBG_MSG("rule:  post_c_op -> post_inc\n"); $$=ADD;}
    | post_dec {DBG_MSG("rule:  post_c_op -> post_dec\n"); $$=SUB;}
    ;

pre_c_op:
      pre_inc {DBG_MSG("rule:  pre_c_op -> pre_inc\n"); $$=ADD;}
    | pre_dec {DBG_MSG("rule:  pre_c_op -> pre_dec\n"); $$=SUB;}
    ;

bin_op:
    | db_stick {DBG_MSG("rule:  bin_op -> logic_or\n"); $$=OR;}
    | power {DBG_MSG("rule:  bin_op -> mul\n"); $$=POW;}
    ;

expr:
      word {DBG_MSG("rule:  expr -> word\n");
        $$=$1;
    }
    | assignment expr %prec ASSIGNMENT_PRI { DBG_MSG("rule: expr -> assignment word\n"); 
        list_init(&code_block);
        list_splice_tail(&code_block, &$2);
        char* stack_slot_str = alloc_global_var($1);
        _list_insert_tail(&code_block, instr_create(POP, REGD, NULL));
        _list_insert_tail(&code_block, instr_create(WRITE, REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));    
        $$=code_block; 
    }
    | VAR eq expr %prec ASSIGNMENT_PRI {DBG_MSG("rule:  expr -> expr eq expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$3);
        char* stack_slot_str = alloc_global_var($1);
        _list_insert_tail(&code_block, instr_create(POP,  REGD, NULL));
        _list_insert_tail(&code_block, instr_create(WRITE,REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        $$=code_block;
    }
    | VAR op_eq expr {DBG_MSG("rule:  expr -> expr op_eq expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$3);
        char* stack_slot_str;
        if (!map_get(&global_vars_map, $1, &stack_slot_str)) {
            yyerror("expr -> VAR post_c_op: undeclared variable");
            YYABORT;
        }
        _list_insert_tail(&code_block, instr_create(POP,  REGD, NULL));
        _list_insert_tail(&code_block, instr_create(READ, REGA, stack_slot_str));
        _list_insert_tail(&code_block, instr_create($2,   REGA, REGD));
        _list_insert_tail(&code_block, instr_create(WRITE,REGA, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGA, NULL));
        $$=code_block;
    }
    | VAR post_c_op {DBG_MSG("rule:  expr -> VAR post_c_op\n");
        list_init(&code_block);
        char* stack_slot_str;
        if (!map_get(&global_vars_map, $1, &stack_slot_str)) {
            yyerror("expr -> VAR post_c_op: undeclared variable");
            YYABORT;
        }
        _list_insert_tail(&code_block, instr_create(READ, REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        _list_insert_tail(&code_block, instr_create($2,   REGD, one_str));
        _list_insert_tail(&code_block, instr_create(WRITE,REGD, stack_slot_str));
        $$=code_block;
    }
    | pre_c_op VAR {DBG_MSG("rule:  expr -> pre_c_op VAR\n");
        list_init(&code_block);
        char* stack_slot_str;
        if (!map_get(&global_vars_map, $2, &stack_slot_str)) {
            yyerror("expr -> pre_c_op VAR: undeclared variable");
            YYABORT;
        }
        _list_insert_tail(&code_block, instr_create(READ, REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create($1,   REGD, one_str));
        _list_insert_tail(&code_block, instr_create(WRITE,REGD, stack_slot_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        $$=code_block;
    }
    | minus expr %prec UNARY { DBG_MSG("rule:  expr -> minus expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$2);
        _list_insert_tail(&code_block, instr_create(POP,  REGD, NULL));
        _list_insert_tail(&code_block, instr_create(MUL,  REGD, minus_one_str));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        $$=code_block;        
    }
    | plus expr %prec UNARY { DBG_MSG("rule:  expr -> plus expr\n");
        $$=$2;        
    }
    | _exclamation_mark expr { DBG_MSG("rule:  expr -> _exclamation_mark expr\n");
        char* label_1 = create_named_string("__expr_eq_0_");
        char* label_2 = create_named_string("__exclamation_end");
        list_init(&code_block);
        list_splice_tail(&code_block, &$2);
        _list_insert_tail(&code_block, instr_create(POP,  REGD,     NULL));
        _list_insert_tail(&code_block, instr_create(TEST, REGD,     one_str));
        _list_insert_tail(&code_block, instr_create(JZ,   label_1,  NULL));
        _list_insert_tail(&code_block, instr_create(PUSH, one_str,  NULL));
        _list_insert_tail(&code_block, instr_create(JMP,  label_2,  NULL));
        _list_insert_tail(&code_block, instr_create(label_1, NULL,  NULL));
        _list_insert_tail(&code_block, instr_create(PUSH, zero_str, NULL));
        _list_insert_tail(&code_block, instr_create(label_2, NULL,  NULL));
        $$=code_block;         
    }
    | tilda expr { DBG_MSG("rule:  expr -> tilda expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$2);
        _list_insert_tail(&code_block, instr_create(POP,  REGD, NULL));
        _list_insert_tail(&code_block, instr_create(NOT,  REGD, REGD));
        _list_insert_tail(&code_block, instr_create(PUSH, REGD, NULL));
        $$=code_block;  
    }
    | expr minus expr {DBG_MSG("rule:  expr -> expr minus expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block, SUB);
        $$=code_block;
    }
    | expr plus expr {DBG_MSG("rule:  expr -> expr minus expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block, ADD);
        $$=code_block;
    }
    | expr mul expr {DBG_MSG("rule:  expr -> expr mul expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block, MUL);
        $$=code_block;
    }
    | expr division expr {DBG_MSG("rule:  expr -> expr division expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block, DIV);
        $$=code_block;
    }
    | expr mod expr {DBG_MSG("rule:  expr -> expr mod expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block,  MOD);
        $$=code_block;
    }
    | expr shr expr {DBG_MSG("rule:  expr -> expr shr expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block,  SHR);
        $$=code_block;
    }
    | expr shl expr {DBG_MSG("rule:  expr -> expr shl expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block,  SHL);
        $$=code_block;
    }
    | expr ampersand expr {DBG_MSG("rule:  expr -> expr ampersand expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block,  AND);
        $$=code_block;
    }
    | expr stick expr {DBG_MSG("rule:  expr -> expr stick expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block, OR );
        $$=code_block;
    }
    | expr xor expr {DBG_MSG("rule:  expr -> expr xor expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block,  XOR);
        $$=code_block;
    }
    | expr db_ampersand expr {DBG_MSG("rule:  expr -> expr db_ampersand expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block,  AND);
        $$=code_block;
    }
    | expr db_stick expr {DBG_MSG("rule:  expr -> expr db_stick expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block,  OR);
        $$=code_block;
    }
    | expr power expr {DBG_MSG("rule:  expr -> expr power expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_bin_op(&code_block,  POW);
        $$=code_block;
    }
    | cmp_expr_curved {DBG_MSG("rule:  expr -> cmp_expr_curved\n");
        $$=$1;
    }
    | expr question expr colon expr %prec TRIPLE_OP {DBG_MSG("rule:  expr -> expr question expr colon expr\n");
        char* label_1 = create_named_string("__triple_op_cond_eq_0_");
        char* label_2 = create_named_string("__triple_op_end");
        list_init(&code_block);
        list_splice_tail(&code_block, &$3);
        list_splice_tail(&code_block, &$5);
        list_splice_tail(&code_block, &$1);
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
        $$=code_block;
    }
    | expr comma expr {DBG_MSG("rule:  expr -> expr comma expr\n");
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        _list_insert_tail(&code_block, instr_create(POP,     REGD,    NULL));
        _list_insert_tail(&code_block, instr_create(POP,     REGA,    NULL)); 
        _list_insert_tail(&code_block, instr_create(PUSH,    REGD,    NULL));
        // only expr2 result matters
        $$=code_block; 
    }
    | opening_curve expr closing_curve {DBG_MSG("rule:  expr -> opening_curve expr closing_curve\n");
        $$=$2;
    }

    ;

cmp_expr_squared:
      expr eq_option expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_eq(&code_block);
        $$=code_block;
    }
    | expr ne_option expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_ne(&code_block);        
        $$=code_block;
    }
    | expr lt_option expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_lt(&code_block);
        $$=code_block;
    }
    | expr le_option expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_le(&code_block);
        $$=code_block;
    }
    | expr gt_option expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_gt(&code_block);
        $$=code_block;
    }
    | expr ge_option expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_ge(&code_block);
        $$=code_block;
    }
    ;

cmp_expr_curved:
      expr db_eq expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_eq(&code_block);
        $$=code_block;
    }
    | expr exclamation_eq expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_ne(&code_block);        
        $$=code_block;
    }
    | expr less expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_lt(&code_block);
        $$=code_block;
    }
    | expr less_eq expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_le(&code_block);
        $$=code_block;
    }
    | expr more expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_gt(&code_block);
        $$=code_block;
    }
    | expr more_eq expr {
        list_init(&code_block);
        list_splice_tail(&code_block, &$1);
        list_splice_tail(&code_block, &$3);
        gen_ge(&code_block);
        $$=code_block;
    }
    ;

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



%%

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

