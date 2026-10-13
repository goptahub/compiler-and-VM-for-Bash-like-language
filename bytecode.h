// registers

#define REGISTER(opcode) (opcode >= 0xF8 && opcode <= 0xFD)

#define  REGA_OPCODE 0xFA
#define  REGB_OPCODE 0xFB
#define  REGC_OPCODE 0xFC
#define  REGD_OPCODE 0xFD 
#define  REGE_OPCODE 0xFE
#define  REGF_OPCODE 0xFF
#define  REGG_OPCODE 0xF8
#define  REGH_OPCODE 0xF9 

// unary instruction (arg1 of fixed type)

// arg1 - 1 byte (register)

#define UNARY(opcode) (opcode >= 0xA0 && opcode <= 0xA2)

#define  OUT_OPCODE 0xA0 //arg1 - 1
#define PUSH_OPCODE 0xA1 //arg1 - 1
#define  POP_OPCODE 0xA2 //arg1 - 1

// wide unary instruction

// arg1 - 4 byte (constant)

#define UNARY_WIDE(opcode) (opcode >= 0xD0 && opcode <= 0xDF)


#define  OUT_WIDE_OPCODE 0xD0 //arg1 - 4
#define PUSH_WIDE_OPCODE 0xD1 //arg1 - 4
//#define  POP_WIDE_OPCODE 0xD2 //arg1 - 4
#define  JMP_OPCODE 0xD3 //arg1 - 4
#define   JZ_OPCODE 0xD4 //arg1 - 4
#define  JNZ_OPCODE 0xD5 //arg1 - 4


// binary instruction

// arg1 - 1 byte (register)
// arg2 - 1 byte (register)

#define BINARY(opcode) (opcode >= 0xAE && opcode <= 0xBF)

#define  READ_OPCODE 0xAE
#define WRITE_OPCODE 0xAF

#define MOV_OPCODE 0xB0

#define ADD_OPCODE 0xB1
#define SUB_OPCODE 0xB2
#define MUL_OPCODE 0xB3
#define POW_OPCODE 0xB4
#define DIV_OPCODE 0xB5
#define MOD_OPCODE 0xB6

#define SHR_OPCODE 0xB7
#define SHL_OPCODE 0xB8
#define  OR_OPCODE 0xB9
#define XOR_OPCODE 0xBA
#define AND_OPCODE 0xBB
#define NOT_OPCODE 0xBC

#define  CMP_OPCODE 0xBD
#define TEST_OPCODE 0xBE


// extended binary instruction

// arg1 - 1 byte (register)
// arg2 - 4 bytes (constant)

#define BINARY_WIDE(opcode) (opcode >= 0xE0 && opcode <= 0xF1)

#define MOV_WIDE_OPCODE 0xE0

#define ADD_WIDE_OPCODE 0xE1
#define SUB_WIDE_OPCODE 0xE2
#define MUL_WIDE_OPCODE 0xE3
#define POW_WIDE_OPCODE 0xE4
#define DIV_WIDE_OPCODE 0xE5
#define MOD_WIDE_OPCODE 0xE6

#define SHR_WIDE_OPCODE 0xE7
#define SHL_WIDE_OPCODE 0xE8
#define  OR_WIDE_OPCODE 0xE9
#define XOR_WIDE_OPCODE 0xEA
#define AND_WIDE_OPCODE 0xEB
#define NOT_WIDE_OPCODE 0xEC

#define  CMP_WIDE_OPCODE 0xED
#define TEST_WIDE_OPCODE 0xEE

// stack instruction

// arg2 - address in stack

#define  READ_WIDE_OPCODE 0xF0
#define WRITE_WIDE_OPCODE 0xF1


// ByteCode

typedef unsigned char byte_t;

typedef struct
{
    byte_t* bytes;
    int   size;
} ByteCode;


void bc_init(ByteCode *bc);
int bc_create(ByteCode *bc, char* file);
void bc_delete(ByteCode *bc);

