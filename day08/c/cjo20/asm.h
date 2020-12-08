#include <stdlib.h>

#define MAX_PROGRAM_SIZE 1024

typedef enum opcode
{
    OP_ACC,
    OP_JMP,
    OP_NOP,
    OP_NUM_OPCODES
} op_t;

typedef struct op_info
{
    char * opcode;
    int num_args;
} op_info_t;

typedef struct instruction
{
    op_t opcode;
    int arg;

} instr_t;

void print_instruction(instr_t * instr);
void process_instruction(char * line, size_t line_size, instr_t * instr);
int execute_program(instr_t program[], size_t num_instr, char visited[], int * result);

extern op_info_t op_desc[OP_NUM_OPCODES];