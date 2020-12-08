#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "asm.h"


int main(int argc, char * argv[])
{
    instr_t program[MAX_PROGRAM_SIZE] = {};
    char visited[MAX_PROGRAM_SIZE] = {};
    FILE * input = fopen("day08.txt", "r");

    int instr_count = 0;
    char * line = NULL;
    size_t line_size = 0;

    while(getline(&line, &line_size, input) != -1)
    {
        process_instruction(line, line_size, program + instr_count++);
    }

    int result = 0;
    
    execute_program(program, instr_count, visited, &result);
    printf("Answer 1: %d\n", result); 
    instr_t program_copy[1024] = {};

    for(int i = 0; i < instr_count; ++i)
    {
        if (program[i].opcode != OP_ACC)
        {
            memcpy(program_copy, program, instr_count * sizeof(instr_t));
            memset(visited, 0, sizeof(char) * instr_count);
            program_copy[i].opcode ^= 0x3; // swap NOP and JMP (JMP = 0b01, NOP = 0b10)
            int res = execute_program(program_copy, instr_count, visited, &result);

            if (res)
            {
                printf("Answer 2: %d\n", result);
                break;
            }
        }
    }

    return 0;
}