%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#include "bytecode.h"
#include "map.h"

#ifdef DEBUG
    #define DBG_MSG(...) printf(__VA_ARGS__);
#else
    #define DBG_MSG(...) ((void)0)
#endif

void yyerror(const char *s);
int  yylex(void);

extern int yylineno;

extern FILE *yyin;   // Объявляем переменную Flex (определена в lex.yy.c)
extern int yyparse(); // Функция парсера Bison

FILE* p_output_file = NULL;
Map gap_map, label_map;

int gap_offs(void);
int label_offs(void);
int write_instruction_u(unsigned char op, unsigned char reg);
int write_instruction_u_w(unsigned char op, MAP_VALUE_T number);
int write_instruction_b(unsigned char op, unsigned char reg1, unsigned char reg2);
int write_instruction_b_w(unsigned char op, unsigned char reg1, MAP_VALUE_T number);

%}

%glr-parser

%union {
    char* string;
    int num;
    unsigned char opcode;
}

%type  <opcode> reg j_op u_op u_op_wide bin_op bin_op_wide
%token <string> label
%token <num> number
%token NEWLINE ERROR colon
%token rega regb regc regd rege regf regg regh
%token out push pop
%token jmp jz jnz
%token mov add sub mul pow _div mod shr shl or xor and not
%token test cmp
%token read_ write_




%start input

%%

input:
    { DBG_MSG("rule: input -> epsilon\n"); }
    | input NEWLINE { DBG_MSG("rule: input -> input NEWLINE\n"); }
    | input instruction NEWLINE { DBG_MSG("rule: input -> input instruction NEWLINE\n"); }
    ;

reg:
      rega { DBG_MSG("rule: reg -> rega\n"); $$ = REGA_OPCODE; }
    | regb { DBG_MSG("rule: reg -> regb\n"); $$ = REGB_OPCODE; }
    | regc { DBG_MSG("rule: reg -> regc\n"); $$ = REGC_OPCODE; }
    | regd { DBG_MSG("rule: reg -> regd\n"); $$ = REGD_OPCODE; }
    | rege { DBG_MSG("rule: reg -> rege\n"); $$ = REGE_OPCODE; }
    | regf { DBG_MSG("rule: reg -> regf\n"); $$ = REGF_OPCODE; }
    | regg { DBG_MSG("rule: reg -> regg\n"); $$ = REGG_OPCODE; }
    | regh { DBG_MSG("rule: reg -> regh\n"); $$ = REGH_OPCODE; }
    ;

u_op:
      out { DBG_MSG("rule: u_op -> out\n"); $$ = OUT_OPCODE; }
    | push { DBG_MSG("rule: u_op -> push\n"); $$ = PUSH_OPCODE; }
    | pop { DBG_MSG("rule: u_op -> pop\n"); $$ = POP_OPCODE; }
    ;

u_op_wide:
      out { DBG_MSG("rule: u_op -> out\n"); $$ = OUT_WIDE_OPCODE; }
    | push { DBG_MSG("rule: u_op -> push\n"); $$ = PUSH_WIDE_OPCODE; }
    ;
j_op:
      jmp { DBG_MSG("rule: u_op_wide -> jmp\n"); $$ = JMP_OPCODE; }
    | jz  { DBG_MSG("rule: u_op_wide -> jz\n");  $$ =  JZ_OPCODE; }
    | jnz { DBG_MSG("rule: u_op_wide -> jnz\n"); $$ = JNZ_OPCODE; }
    ;

bin_op:
      read_  { DBG_MSG("rule: bin_op_wide -> read\n");  $$ = READ_OPCODE; }
    | write_ { DBG_MSG("rule: bin_op_wide -> write\n"); $$ = WRITE_OPCODE; }
    | mov { DBG_MSG("rule: bin_op -> mov\n"); $$ = MOV_OPCODE; }
    | add { DBG_MSG("rule: bin_op -> add\n"); $$ = ADD_OPCODE; }
    | sub { DBG_MSG("rule: bin_op -> sub\n"); $$ = SUB_OPCODE; }
    | mul { DBG_MSG("rule: bin_op -> mul\n"); $$ = MUL_OPCODE; }
    | pow { DBG_MSG("rule: bin_op -> pow\n"); $$ = POW_OPCODE; }
    | _div { DBG_MSG("rule: bin_op -> div\n"); $$ = DIV_OPCODE; }
    | mod { DBG_MSG("rule: bin_op -> mod\n"); $$ = MOD_OPCODE; }
    | shr { DBG_MSG("rule: bin_op -> shr\n"); $$ = SHR_OPCODE; }
    | shl { DBG_MSG("rule: bin_op -> shl\n"); $$ = SHL_OPCODE; }
    | or  { DBG_MSG("rule: bin_op -> or\n");  $$ =  OR_OPCODE; }
    | xor { DBG_MSG("rule: bin_op -> xor\n"); $$ = XOR_OPCODE; }
    | and { DBG_MSG("rule: bin_op -> and\n"); $$ = AND_OPCODE; }
    | not { DBG_MSG("rule: bin_op -> not\n"); $$ = NOT_OPCODE; }
    | test { DBG_MSG("rule: bin_op -> test\n"); $$ = TEST_OPCODE; }
    | cmp { DBG_MSG("rule: bin_op -> cmp\n"); $$ = CMP_OPCODE; }
    ;
 
bin_op_wide:
      read_  { DBG_MSG("rule: bin_op_wide -> read\n");  $$ = READ_WIDE_OPCODE; }
    | write_ { DBG_MSG("rule: bin_op_wide -> write\n"); $$ = WRITE_WIDE_OPCODE; }
    | mov { DBG_MSG("rule: bin_op -> mov\n"); $$ = MOV_WIDE_OPCODE; }
    | add { DBG_MSG("rule: bin_op -> add\n"); $$ = ADD_WIDE_OPCODE; }
    | sub { DBG_MSG("rule: bin_op -> sub\n"); $$ = SUB_WIDE_OPCODE; }
    | mul { DBG_MSG("rule: bin_op -> mul\n"); $$ = MUL_WIDE_OPCODE; }
    | pow { DBG_MSG("rule: bin_op -> pow\n"); $$ = POW_WIDE_OPCODE; }
    | _div { DBG_MSG("rule: bin_op -> div\n"); $$ = DIV_WIDE_OPCODE; }
    | mod { DBG_MSG("rule: bin_op -> mod\n"); $$ = MOD_WIDE_OPCODE; }
    | shr { DBG_MSG("rule: bin_op -> shr\n"); $$ = SHR_WIDE_OPCODE; }
    | shl { DBG_MSG("rule: bin_op -> shl\n"); $$ = SHL_WIDE_OPCODE; }
    | or  { DBG_MSG("rule: bin_op -> or\n");  $$ =  OR_WIDE_OPCODE; }
    | xor { DBG_MSG("rule: bin_op -> xor\n"); $$ = XOR_WIDE_OPCODE; }
    | and { DBG_MSG("rule: bin_op -> and\n"); $$ = AND_WIDE_OPCODE; }
    | not { DBG_MSG("rule: bin_op -> not\n"); $$ = NOT_WIDE_OPCODE; }
    | test { DBG_MSG("rule: bin_op -> test\n"); $$ = TEST_WIDE_OPCODE; }
    | cmp { DBG_MSG("rule: bin_op -> cmp\n"); $$ = CMP_WIDE_OPCODE; }
    ;

instruction:
      u_op reg               { DBG_MSG("rule: instruction -> u_op reg\n");              write_instruction_u  ($1, $2);    }
    | u_op_wide number       { DBG_MSG("rule: instruction -> u_op_wide number\n");      write_instruction_u_w($1, $2);    }
    | j_op label             { DBG_MSG("rule: instruction -> j_op label\n");    
        //printf("add gap: %s, %08X\n", $2, gap_offs());
        map_add(&gap_map, $2, gap_offs());
        write_instruction_u_w($1, 0xFFFFFFFFFFFFFFFF);
        }
    | bin_op reg reg         { DBG_MSG("rule: instruction -> bin_op reg reg\n");        write_instruction_b  ($1, $2, $3);}
    | bin_op_wide reg number { DBG_MSG("rule: instruction -> bin_op_wide reg number\n");write_instruction_b_w($1, $2, $3);}
    | label colon                  { DBG_MSG("rule: instruction -> label colon\n");
        //printf("\tadd label: %s, %08X\n", $1, label_offs());
        map_add(&label_map, $1, label_offs());
        }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "[-] %s [line: %d]\n", s, yylineno);
}

int gap_offs(void)
{
    return ftell(p_output_file) + 1;
}

int label_offs(void)
{
    return ftell(p_output_file);
}

int fill_gaps(void)
{
    char* key;
    MAP_VALUE_T gap_offs, label_offs;
    int found = 1;
    for (size_t i = 0; i < gap_map.size; ++i) {
        key = gap_map.items[i].key;
        gap_offs = gap_map.items[i].value;
        found = map_get(&label_map, key, &label_offs);
        if (!found) return 1;

        fseek(p_output_file, gap_offs, SEEK_SET);
        fwrite(&label_offs, sizeof(MAP_VALUE_T), 1, p_output_file);

        //printf("\nlabel:      %s\n", key);
        //printf("gap_offs:   %08X\n", gap_offs);
        //printf("label_offs: %08X\n", label_offs);
    }
    return 0;
}

int write_instruction_u(unsigned char op, unsigned char reg)
{
    fwrite(&op,  1, 1, p_output_file);
    fwrite(&reg, 1, 1, p_output_file);
    return 1;
}

int write_instruction_u_w(unsigned char op, MAP_VALUE_T number)
{
    fwrite(&op,     1, 1, p_output_file);
    fwrite(&number, sizeof(MAP_VALUE_T), 1, p_output_file);
    return 1;
}

int write_instruction_b(unsigned char op, unsigned char reg1, unsigned char reg2)
{
    fwrite(&op,   1, 1, p_output_file);
    fwrite(&reg1, 1, 1, p_output_file);
    fwrite(&reg2, 1, 1, p_output_file);
    return 1;
}

int write_instruction_b_w(unsigned char op, unsigned char reg1, MAP_VALUE_T number)
{
    fwrite(&op,     1, 1, p_output_file);
    fwrite(&reg1,   1, 1, p_output_file);
    fwrite(&number, sizeof(MAP_VALUE_T), 1, p_output_file);
    return 1;
}


#ifdef ITSELF 

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: basm_parser <.basm> <.bvm>\n");
        return 0;
    }

    p_output_file = fopen(argv[2], "wb");
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

    map_init(&gap_map, JUST_ADD);
    map_init(&label_map, JUST_ADD);

    yylineno = 0;
    int exit_code = yyparse();

    if (exit_code == 0) {
        exit_code = fill_gaps();
    }

    map_free(&gap_map, 0);
    map_free(&label_map, 0);

    fclose(yyin);
    fclose(p_output_file);

    return exit_code;
}

#else

int assemble_basm_to_bvm(char* input_file, char* output_file)
{
    p_output_file = fopen(output_file, "wb");
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

    map_init(&gap_map, JUST_ADD);
    map_init(&label_map, JUST_ADD);

    int exit_code = yyparse();

    if (exit_code == 0) {
        exit_code = fill_gaps();
    }

    map_free(&gap_map, 0);
    map_free(&label_map, 0);

    fclose(yyin);
    fclose(p_output_file);

    //printf("assemble_basm_to_bvm returned %d\n", exit_code);

    return exit_code;
}

#endif
