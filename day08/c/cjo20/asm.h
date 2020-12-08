#include <stdlib.h>

#define MAX_PROGRAM_SIZE 1024

typedef enum opcode
{
    OP_ACC,
    OP_JMP,
    OP_NOP
} op_t;

typedef struct instruction
{
    op_t opcode;
    int arg;

} instr_t;

void print_instruction(instr_t * instr);
void process_instruction(char * line, size_t line_size, instr_t * instr);
int execute_program(instr_t program[], size_t num_instr, char visited[], int * result);