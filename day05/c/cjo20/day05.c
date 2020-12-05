#include <stdio.h>

int process_pass(char * line)
{
    int front = 0, left = 0, i = 0; 
    
    for(int mod = 64; mod; mod >>= 1, i++)
    {
        front |= (line[i] == 'B') * mod;
    }

    for(int mod = 4; mod; mod >>=1, i++)
    {
        left |= (line[i] == 'R') * mod;
    }
    
    return front * 8 + left;
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

    char prev_present = 0, present = 0, next_present = 0;
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
