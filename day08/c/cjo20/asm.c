#include <stdio.h>
#include <string.h>
#include "asm.h"

op_info_t op_desc[OP_NUM_OPCODES] = {
    {"ACC", 1},
    {"JMP", 1},
    {"NOP", 1}
};

void print_instruction(instr_t * instr)
{
    printf("%s ", op_desc[instr->opcode].opcode);
    printf("%d\n", instr->arg);
}

void process_instruction(char * line, size_t line_size, instr_t * instr)
{
    int offset = 0;

    char opcode[8] = {};
    int arg;
    
    sscanf(line, "%s%n", opcode, &offset);
    line += offset;

    if (!strcmp(opcode, "acc")) {
        instr->opcode = OP_ACC;
    } else if (!strcmp(opcode, "jmp")) {
        instr->opcode = OP_JMP;
    } else if (!strcmp(opcode, "nop")) {
        instr->opcode = OP_NOP;
    } else {
        printf("Invalid opcode %s\n", opcode);
        exit(1);
    }

    sscanf(line, "%d", &arg);
    instr->arg = arg;

    //printf("Got instruction: ");
    //print_instruction(instr);
}

int execute_instruction(instr_t * instr, int pc, int * accumulator)
{
    switch(instr->opcode)
    {
        case OP_ACC:
            *accumulator += instr->arg;
            pc++;
            break;

        case OP_JMP:
            pc += instr->arg;
            break;

        case OP_NOP:
            pc++;
            break;

        default:
            printf("Trying to execute invalid opcode %d\n", instr->opcode);
            exit(1);
    }

    return pc;
}

int execute_program(instr_t program[], size_t num_instr, char visited[], int * result)
{
    int accumulator = 0;

    int pc = 0;

    while(pc != num_instr)
    {
        if (visited[pc]) {
            *result = accumulator;
            return 0;
        }
        if (pc > num_instr) {
            printf("Max program size exceeded: %d\n", pc);
            exit(1);
        }

        visited[pc]++;
        pc = execute_instruction(program + pc, pc, &accumulator);
    }

    *result = accumulator;
    return 1;
}