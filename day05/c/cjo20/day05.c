#include <stdio.h>

int process_pass(char * line)
{

    int front = 0; 
    int left = 0;
    int i = 0;

    int mod = 64;
    
    while (mod > 0)
    {
        if (line[i] == 'B')
        {
            front += mod;
        }
        mod >>= 1;
        i++;
    }

    mod = 4;

    while(mod > 0)
    {
        if (line[i] == 'R')
        {
            left += mod;
        }

        mod >>= 1;
        i++;
    }

    int id = front * 8 + left;


    return id;
}

int main()
{
    FILE * input = fopen("day05.txt", "r");

    char * line = NULL;
    size_t len = 0;

    #define NUM_SEATS (128 * 8)

    char seats[NUM_SEATS] = {};

    int max_id = 0;
    while(getline(&line, &len, input) != -1)
    {
        int id = process_pass(line);

        seats[id] = 1;
        max_id = (id > max_id) ? id : max_id;
    }

    char prev_present = 0;
    char present = 0;
    char next_present = 0;
    int found_id = -1;
    for (int i = 0; i < NUM_SEATS; ++i)
    {
        next_present = seats[i];

        if (next_present & !present & prev_present)
        {
            found_id = i - 1;
            break;
        }

        prev_present = present;
        present = next_present;

    }


    printf("Answer 1: %d\n", max_id);
    printf("Answer 2: %d\n", found_id);

    fclose(input);
    return 0;
}
