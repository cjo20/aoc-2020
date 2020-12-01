#include <stdio.h>
#include <stdlib.h>

int solveOne(int * array, int num_lines)
{
    for(int i = 0; i < num_lines; ++i)
    {
        for(int j = i  + 1; j < num_lines; ++j)
        {
            if ((array[i] + array[j]) == 2020)
            {
                printf("Answer 1: %d\n", array[i] * array[j]);
                return array[i] * array[j];
            }
        }
    }

    return -1;
}

int solveTwo(int * array, int num_lines) 
{
    for (int i = 0; i < num_lines; ++i)
    {
        for(int j = i+1; j < num_lines; ++j)
        {
            for(int k = j+1; k < num_lines; ++k)
            {
                if (array[i] + array[j] + array[k] == 2020)
                {
                    printf("Answer 2: %d\n", array[i] * array[j] * array[k]);
                    return (array[i] * array[j] * array[k]);
                }
            }
        }
    }
    return -1;
}
int main(int argc, char *argv[])
{
    FILE * input = fopen("day01.txt", "r");

    char * line = NULL; //probably not going to be more than 20-digit numbers
    size_t line_size;

    int num_lines = 0;
    int * input_array = NULL;

    while(getline(&line, &line_size, input) != -1)
    {
        num_lines++;
        free(line);
        line = NULL;
    }

    fseek(input, 0, SEEK_SET);
    input_array = (int *) malloc(num_lines * sizeof(int));

    for(int i = 0; i < num_lines; ++i)
    {
        getline(&line, &line_size, input);
        input_array[i] = atoi(line);

        free(line);
        line = NULL;
    }

    solveOne(input_array, num_lines);
    solveTwo(input_array, num_lines);

    return 0;
}