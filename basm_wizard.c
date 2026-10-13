#include "basm_wizard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* commands[] = {
    "out", "push", "pop",
    "jmp", "jz", "jnz",
    "read", "write",
    "mov",
    "add", "sub", "mul", "pow", "div", "mod",
    "shr", "shl", "or", "xor", "and", "not",
    "cmp", "test"
};

char* regs[] = {"rega", "regb", "regc", "regd"};


Instruction* instr_create(char* command, char* arg1, char* arg2)
{
    Instruction* instr;
    instr = (Instruction*)malloc(sizeof(Instruction));
    if (!instr) {
        fprintf(stderr, "Memory allocation failed in instr_create()\n");
        exit(EXIT_FAILURE);
    }
    instr->next = NULL;
    instr->command = command;
    instr->arg1 = arg1;
    instr->arg2 = arg2;
    return instr;
}

void instr_free(Instruction* instr)
{
    free(instr);
}

void instr_print(Instruction* instr, FILE* file)
{
    if (instr->command) {
        if (instr->arg1) {
            if (instr->arg2) {
                fprintf(file, "%s %s %s\n", instr->command, instr->arg1, instr->arg2);
            }
            else {
                fprintf(file, "%s %s\n", instr->command, instr->arg1);
            }
        }
        else {
            fprintf(file, "\n%s:\n", instr->command);
        }
    }
    else {
        fprintf(stderr, "Trys to print empty instruction\n");
        exit(EXIT_FAILURE);
    }
}



