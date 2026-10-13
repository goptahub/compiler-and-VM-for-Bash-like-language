#ifndef BASM_WIZARD_H
#define BASM_WIZARD_H

#include <stdio.h>

extern char* commands[];
extern char* regs[];

#define REGA regs[0]
#define REGB regs[1]
#define REGC regs[2]
#define REGD regs[3]

#define OUT  commands[0]
#define PUSH commands[1]
#define POP  commands[2]
#define JMP  commands[3]
#define JZ   commands[4]
#define JNZ  commands[5]
#define READ commands[6]
#define WRITE commands[7]
#define MOV  commands[8]
#define ADD  commands[9]
#define SUB  commands[10]
#define MUL  commands[11]
#define POW  commands[12]
#define DIV  commands[13]
#define MOD  commands[14]
#define SHR  commands[15]
#define SHL  commands[16]
#define OR   commands[17]
#define XOR  commands[18]
#define AND  commands[19]
#define NOT  commands[20]
#define CMP  commands[21]
#define TEST commands[22]


typedef struct Instruction Instruction;

struct Instruction{
    Instruction* next;
    char* command;
    char* arg1;
    char* arg2;
};

Instruction* instr_create(char* command, char* arg1, char* arg2);
void instr_free(Instruction* instr);
void instr_print(Instruction* instr, FILE* file);

#define instr_create_com(command, arg1, arg2)   instr_create(command, arg1, arg2)
#define instr_create_label(label)               instr_create(label, NULL, NULL)


#endif

