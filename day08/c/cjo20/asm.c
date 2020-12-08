#include <stdio.h>
#include <string.h>
#include "asm.h"

void print_instruction(instr_t * instr)
{
    
    switch(instr->opcode)
    {
        case OP_ACC:
            printf("ACC ");
            break;
        case OP_JMP:
            printf("JMP ");
            break;
        case OP_NOP:
            printf("NOP ");
            break;
    }

    printf(" %d\n", instr->arg);
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
    }

    sscanf(line, "%d", &arg);
    instr->arg = arg;

  //  printf("Got instruction: ");
  //  print_instruction(instr);
}

int execute_program(instr_t program[], size_t num_instr, char visited[], int * result)
{
    int accumulator = 0;

    int pc = 0;

    while(pc < num_instr)
    {
        if (visited[pc]) {
            *result = accumulator;
            return 0;
        }
        if (pc > MAX_PROGRAM_SIZE) {
            printf("Max program size exceeded: %d\n", pc);
            exit(1);
        }

        visited[pc]++;
        switch(program[pc].opcode)
        {
            case OP_ACC:
                accumulator += program[pc].arg;
                pc++;
                break;

            case OP_JMP:
                pc += program[pc].arg;
                break;

            case OP_NOP:
                pc++;
                break;
        }

    }

    *result = accumulator;
    return 1;
}