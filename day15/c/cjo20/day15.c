#include <stdio.h>
#include <stdlib.h>

int calculate_next(int * turns, int num, int turn)
{
    if (turns[num] == 0) return 0;
    return  turn - turns[num];
}

#define SIZE 30000000

int main(void)
{
    int answer1 = 0;

    FILE * input = fopen("day15.txt", "r");

    int * turns  = (int *) calloc(SIZE, sizeof(int));
    int turn = 1;

    int last_result = 0;
    int inp = 0;

    while(fscanf(input, "%d,", &inp) > 0)
    {       
        last_result = calculate_next(turns, inp, turn);
        turns[inp] = turn++;
    }

    for(int i = turn; i < SIZE; ++i)
    {
        int next_result = calculate_next(turns, last_result, i);
        turns[last_result] = i;
        last_result = next_result;

        if(i == 2019) answer1 = last_result;
    }
 
    printf("Answer 1: %d\nAnswer2: %d\n", answer1, last_result);
    return 0;
}