#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "stack.h"
#include "bytecode.h"

typedef long long REG_T;

extern Stack s;
extern ByteCode bc;

extern REG_T rega, regb, regc, regd, regconst;
extern byte_t* ip;
extern int zero_flag;

int read_instruction(byte_t* ip, REG_T** pp_arg1, REG_T** pp_arg2, byte_t** new_ip);

#endif
