#include "processor.h"
#include "stdio.h"
Stack s;
ByteCode bc;

REG_T rega, regb, regc, regd, regconst;
byte_t* ip;
int zero_flag;

int bind_arg(REG_T** pp_arg, byte_t* bytes)
{
    int op = *bytes;
    switch (op)
    {
    case REGA_OPCODE:
        *pp_arg = &rega;
        break;
    case REGB_OPCODE:
        *pp_arg = &regb;
        break;
    case REGC_OPCODE:
        *pp_arg = &regc;
        break;
    case REGD_OPCODE:
        *pp_arg = &regd;
        break;
    default:
        return 0;
    }
    return 1;
}

int bind_arg_to_regconst(REG_T** pp_arg, byte_t* bytes)
{
    if (bytes + sizeof(REG_T) > bc.bytes + bc.size) {
        return 0;
    }
    *pp_arg = &regconst;
    regconst = *(int*)bytes;
    return 1;
}

int read_instruction(byte_t* ip, REG_T** pp_arg1, REG_T** pp_arg2, byte_t** new_ip)
{
    int status = 1;
    byte_t* bytes = ip;
    byte_t op = *bytes;
    //printf("op: %02X\n", op);

    if (UNARY(op)){
        bytes++;

        status = bind_arg(pp_arg1, bytes);
        if (!status) return 0;
        bytes++;
        //printf("unary\n");
    }
    else if (UNARY_WIDE(op)) {
        bytes++;

        status = bind_arg_to_regconst(pp_arg1, bytes);
        if (!status) return 0;
        bytes+=sizeof(REG_T);
        //printf("unary wide\n");
    }
    else if (BINARY(op)) {
        bytes++;

        status = bind_arg(pp_arg1, bytes);
        if (!status) return 0;
        bytes++;


        status = bind_arg(pp_arg2, bytes);
        if (!status) return 0;
        bytes++;
        //printf("binary\n");
    }
    else if (BINARY_WIDE(op)) {
        bytes++;

        status = bind_arg(pp_arg1, bytes);
        if (!status) return 0;
        bytes++;

        status = bind_arg_to_regconst(pp_arg2, bytes);
        if (!status) return 0;
        bytes+=sizeof(REG_T);

        //printf("binary wide\n");
    }
    else {
        printf("[-] read_instruction: wrong opcode\n");
        return 0;
    }

    *new_ip = bytes;

    return 1;
}



