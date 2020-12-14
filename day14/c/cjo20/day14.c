#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>


void print_binary(uint64_t bin)
{
    for(int i = (sizeof(bin) * 8) - 1; i >= 0; --i)
    {
        printf("%c", (char) ((bin >> i) & 1) + '0');
    }
}
void process_v1_mask(char * mask, uint64_t * and_mask, uint64_t * or_mask)
{
    *and_mask = (uint64_t) -1;
    *or_mask = (uint64_t) 0;
 
    for (int i = 35; i >= 0; --i)
    {
        int offset = 35 - i;
        if (mask[i] == 'X') continue;
        if (mask[i] == '0') 
        {
            (*and_mask) ^= (1UL << offset);
        }
        if (mask[i] == '1') 
        { 
            (*or_mask) ^= (1UL << offset);
        }
    }
}

void process_v2_mask(char * mask, uint64_t * and_mask, uint64_t * or_mask, uint64_t * floating_mask)
{
    *and_mask = (uint64_t) -1;
    *or_mask = (uint64_t) 0;
    *floating_mask = (uint64_t) 0;
 
    for (int i = 35; i >= 0; --i)
    {
        int offset = 35 - i;
        if (mask[i] == 'X')
        {
            (*floating_mask) ^= (1UL << offset);
        }
        if (mask[i] == '0') 
        {
            (*and_mask) ^= (1UL << offset);
        }
        if (mask[i] == '1') 
        { 
            (*or_mask) ^= (1UL << offset);
        }
    }
}


uint64_t process_v1(FILE * input)
{
    uint64_t answer1 = 0;
    char * line = NULL;
    size_t line_size = 0;

    uint64_t mem_size = (uint64_t) 1 << 36;
    uint64_t * mem = (uint64_t *) calloc(mem_size, sizeof(uint64_t));
    uint64_t and_mask = (uint64_t) -1;
    uint64_t or_mask = (uint64_t) 0;

    char mask[36];
    uint64_t addr = 0, val = 0;
    while(getline(&line, &line_size, input) != -1)
    {
       // printf("%s", line);
        if(line[1] == 'a')
        {
            sscanf(line, "mask = %s", mask);
            process_v1_mask(mask, &and_mask, &or_mask);
            
           // print_binary(and_mask);
           // printf(" (And mask)\n");
           // print_binary(or_mask);
           // printf(" (Or mask)\n");
            
        } else {
            sscanf(line, "mem[%lu] = %lu", &addr, &val);

            //printf("Writing %lu to address %lu. ", addr, val);
            val &= and_mask;
            val |= or_mask;

            //printf("After masking: %lu\n", val);
            mem[addr] = val;
        }
    }
    for(int i = 0; i < mem_size; ++i)
    {
        answer1 += mem[i];
    }

    free(mem);

    return answer1;
}

void apply_v2_write(uint64_t * mem, uint64_t address, uint64_t val, uint64_t floating_mask)
{
    int i = 0;
    while(i < 36 && (floating_mask & (1UL << i)) == 0)
    {
        i++;
    }

    if( i < 36)
    {
        //printf("Found floating at offset %d\n", i);
        apply_v2_write(mem, address & ~(1UL << i), val, floating_mask ^ (1UL << i));
        apply_v2_write(mem, address | (1UL << i), val, floating_mask ^ (1UL << i));
    } else {
        printf("Writing %lu to address %lX\n", val, address);
        *(mem + address) = val;
    }
}

uint64_t process_v2(FILE * input)
{
    uint64_t answer1 = 0;
    char * line = NULL;
    size_t line_size = 0;

    uint64_t mem_size = (uint64_t) 1 << 36;
    uint64_t * mem = (uint64_t *) calloc(mem_size, sizeof(uint64_t));
    uint64_t and_mask = (uint64_t) -1;
    uint64_t or_mask = (uint64_t) 0;
    uint64_t floating_mask = (uint64_t) 0;

    char mask[36];
    uint64_t addr = 0, val = 0;
    while(getline(&line, &line_size, input) != -1)
    {
       // printf("%s", line);
        if(line[1] == 'a')
        {
            sscanf(line, "mask = %s", mask);
            process_v2_mask(mask, &and_mask, &or_mask, &floating_mask);
            //print_binary(and_mask);
            //printf(" (And mask)\n");
            //print_binary(or_mask);
            //printf(" (Or mask)\n");
            //print_binary(floating_mask);
            //printf(" (Floating mask)\n");
        } else {
            sscanf(line, "mem[%lu] = %lu\n", &addr, &val);
            //print_binary(addr);
            //printf(" (Address)\n");

            addr |= or_mask;
            //print_binary(addr);
            //printf(" (After mask)\n");
            apply_v2_write(mem, addr, val, floating_mask);
            //mem[addr] = val;
            
        }
    }

    printf("Summing answer...\n");
    int i = 0;
    for(uint64_t i = 0; i < mem_size; ++i)
    {
        if (i % (1UL << 30) == 0)
        {
            printf("%lu\n", i);
        }
        answer1 += mem[i];
    }
    printf("%X\n", i);
    free(mem);

    return answer1;
}

int main(void)
{
    FILE * input = fopen("day14.txt", "r");


    printf("Answer 1: %lu\n", process_v1(input));
    fseek(input, 0, SEEK_SET);
    printf("Answer 2: %lu\n", process_v2(input));
}
