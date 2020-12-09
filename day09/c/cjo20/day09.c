#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define ARR_SIZE (1024)

void print_array(uint64_t * data, int start_idx, int preamble_length)
{
    for (int i = 0; i < preamble_length; ++i)
    {
        printf("%lu ", data[i + start_idx]);
    }
    printf("\n");
}


uint64_t find_vulnerability(uint64_t * data, uint64_t target, int num_entries)
{
    for (int i = 0; i < num_entries; ++i)
    {
        int j = i;
        int sum = data[i];
        while (sum < target && j < (num_entries - 1))
        {
            j++;
            sum += data[j];
        }

        if (sum == target && i != j)
        {
            printf("Got sum, first idx: %d, second idx: %d (%lu %lu)\n", i, j, data[i], data[j]);

            uint64_t min = ULONG_MAX;
            uint64_t max = 0;

            for (int x = i; x <= j; ++x)
            {
                if (data[x] < min) min = data[x];
                if (data[x] > max) max = data[x];
            }

            return min + max;
        }

    }

    return 0;
}

int check_value(int target, uint64_t * data, int num_entries, int preamble_length)
{
    char found_remainder = 0;
    for(int i = num_entries - preamble_length; !found_remainder && (i <= num_entries); ++i)
    {
        uint64_t remainder = target - data[i];

        for (int j = i+1; j < num_entries; ++j)
        {
            if (data[j] == remainder)
            {
                found_remainder = 1;
                break;
            }
        }
    }
        
    return found_remainder;
}

int main(int argc, char * argv[])
{

    if (argc < 2)
    {
        printf("Need a preamble length\n");
        exit(1);
    }

    int preamble_length = atoi(argv[1]);

    uint64_t data[ARR_SIZE] = {};

    FILE * input = fopen("day09.txt", "r");

    char * line = NULL;
    size_t line_size = 0;

    int free_reads = preamble_length;
    int idx = 0;

    uint64_t answer1 = -1;
    while(getline(&line, &line_size, input) != -1)
    {
        uint64_t num = strtoul(line, NULL, 0);

        if(free_reads != 0)
        {
            free_reads--;
            data[idx] = num;
            idx++;
            continue;
        }

        data[idx] = num;

        if (!check_value(num, data, idx, preamble_length))
        {
            answer1 = num;
            break;
        }

        idx++;
        if (idx >= ARR_SIZE)
        {
            printf("Input exceeded ARR_SIZE (%d)\n", ARR_SIZE);
            exit(1);
        }
    }

    printf("Answer 1: %lu\n", answer1);
    uint64_t answer2 = find_vulnerability(data, answer1, idx);
    printf("Answer 2: %lu\n", answer2);
    
}