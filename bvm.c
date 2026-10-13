#include "bvm.h"
#include "processor.h"
#include <stdio.h>
//            printf("*p_arg2: %d\n", *p_arg2);

REG_T *p_arg1, *p_arg2;

void dbg(REG_T* reg1, REG_T* reg2);
int interpreter(void);

#ifdef ITSELF

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Usage: bvm <.bvm>");
        return BAD_EXIT_CODE;
    }
    char* bvm_bytecode_file = argv[1];
    int status = 1;
    int exit_code = GOOD_EXIT_CODE;
    bc_init(&bc);
    status = bc_create(&bc, bvm_bytecode_file);
    if (!status) {
        printf("Failed to load file\n");
        return 1;
    }
    stack_init(&s);

    exit_code = interpreter();

    stack_free(&s);
    bc_delete(&bc);

    if (exit_code == BAD_EXIT_CODE)
        printf("BAD_EXIT_CODE\n");

    return exit_code;
}

#else

int execute_bvm(char* bvm_bytecode_file)
{
    int status = 1;
    int exit_code = GOOD_EXIT_CODE;
    bc_init(&bc);
    status = bc_create(&bc, bvm_bytecode_file);
    if (!status) {
        printf("Failed to load file\n");
        return 1;
    }
    stack_init(&s);

    exit_code = interpreter();

    stack_free(&s);
    bc_delete(&bc);

    if (exit_code == BAD_EXIT_CODE)
        printf("BAD_EXIT_CODE\n");

    return exit_code;
}

#endif

void set_zero_flag(REG_T value)
{
    if (value) zero_flag = 0;
    else zero_flag = 1;
}

int interpreter(void)
{
    int status = 1;
    zero_flag = 0;
    byte_t* new_ip;
    ip = bc.bytes;
    byte_t* start_addr = bc.bytes;
    byte_t* finish_addr = bc.bytes + bc.size;
    while (ip >= start_addr && ip < finish_addr) {
        status = read_instruction(ip, &p_arg1, &p_arg2, &new_ip);
        if (!status) {
            printf("[-] read_instruction failed\n");
            return BAD_EXIT_CODE;
        }
        byte_t op = *ip;
        switch (op)
        {
        case MOV_OPCODE:
            *p_arg1 = *p_arg2;
            ip = new_ip;
			break;
        case ADD_OPCODE:
            *p_arg1 += *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case SUB_OPCODE:
            *p_arg1 -= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case MUL_OPCODE:
            *p_arg1 *= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case POW_OPCODE:
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case DIV_OPCODE:
            *p_arg1 /= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case MOD_OPCODE:
            *p_arg1 %= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case SHR_OPCODE:
            *p_arg1 >>= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case SHL_OPCODE:
            *p_arg1 <<= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case OR_OPCODE:
            *p_arg1 |= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case XOR_OPCODE:
            *p_arg1 ^= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case AND_OPCODE:
            *p_arg1 = (*p_arg1) & (*p_arg2);
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case NOT_OPCODE:
            *p_arg1 = ~(*p_arg2);
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;

        case MOV_WIDE_OPCODE:
            *p_arg1 = *p_arg2;
            ip = new_ip;
			break;
        case ADD_WIDE_OPCODE:
            *p_arg1 += *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case SUB_WIDE_OPCODE:
            *p_arg1 -= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case MUL_WIDE_OPCODE:
            *p_arg1 *= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case POW_WIDE_OPCODE:
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case DIV_WIDE_OPCODE:
            *p_arg1 /= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case MOD_WIDE_OPCODE:
            *p_arg1 %= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case SHR_WIDE_OPCODE:
            *p_arg1 >>= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case SHL_WIDE_OPCODE:
            *p_arg1 <<= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case OR_WIDE_OPCODE:
            *p_arg1 |= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case XOR_WIDE_OPCODE:
            *p_arg1 ^= *p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case AND_WIDE_OPCODE:
            *p_arg1 = (*p_arg1) & (*p_arg2);
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;
        case NOT_WIDE_OPCODE:
            *p_arg1 = ~*p_arg2;
            ip = new_ip;
			set_zero_flag(*p_arg1);
			break;

        case READ_OPCODE:
            *p_arg1 = stack_get_from_bottom(&s, *p_arg2);
            ip = new_ip;
			break;
        case WRITE_OPCODE:
            stack_set_from_bottom(&s, *p_arg2, *p_arg1);
            ip = new_ip;
			break;

        case READ_WIDE_OPCODE:
            *p_arg1 = stack_get_from_bottom(&s, *p_arg2);
            ip = new_ip;
			break;
        case WRITE_WIDE_OPCODE:
            stack_set_from_bottom(&s, *p_arg2, *p_arg1);
            ip = new_ip;
			break;

        case OUT_OPCODE:
            // printf("%04X\n", *p_arg1);
            printf("%ld\n", *p_arg1);
            ip = new_ip;
			break;
        case OUT_WIDE_OPCODE:
            // printf("%04X\n", *p_arg1);
            printf("%ld\n", *p_arg1);
            ip = new_ip;
			break;
            
        case PUSH_OPCODE:
            stack_push(&s, *p_arg1);
            ip = new_ip;
			break;
        case PUSH_WIDE_OPCODE:
            stack_push(&s, *p_arg1);
            ip = new_ip;
			break;
            
        case POP_OPCODE:
            *p_arg1 = stack_pop(&s);
            ip = new_ip;
			break;


        case JMP_OPCODE:
            ip = bc.bytes + *p_arg1;
			break;
        case JZ_OPCODE:
            if (zero_flag) ip = bc.bytes + *p_arg1;
            else ip = new_ip;
			break;
        case JNZ_OPCODE:
            if (!zero_flag) ip = bc.bytes + *p_arg1;
            else ip = new_ip;
			break;

        case CMP_OPCODE:
            regconst = *p_arg1 - *p_arg2;
            ip = new_ip;
			set_zero_flag(regconst);
            break;
        case CMP_WIDE_OPCODE:
            regconst = *p_arg1 - *p_arg2;
            ip = new_ip;
			set_zero_flag(regconst);
            break;

        case TEST_OPCODE:
            regconst = (*p_arg1) * (*p_arg2);
            ip = new_ip;
			set_zero_flag(regconst);
            break;
        case TEST_WIDE_OPCODE:
            regconst = (*p_arg1) * (*p_arg2);
            ip = new_ip;
			set_zero_flag(regconst);
            break;

        default:
            printf("[-] unknown opcode\n");
            return BAD_EXIT_CODE;
        }

    }
    return GOOD_EXIT_CODE;
}

void dbg(REG_T* reg1, REG_T* reg2)
{
    printf("p_arg1: %p\n", p_arg1);
    printf("reg1:   %p\n", reg1);
    printf("p_arg2: %p\n", p_arg2);
    printf("reg2:   %p\n", reg2);
}



