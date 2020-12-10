#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

void merge_sort(int * array, int array_size, int left, int right, int end, int * tmp)
{
    int i  = left;
    int j = right;

    for(int k = left; k < end; ++k)
    {
        if (i < right && (j >= end || array[i] <= array[j]))
        {
            tmp[k] = array[i];
            i++;
        } else {
            tmp[k] = array[j];
            j++;
        }
    }
}

void sort_adapters(int * array, int array_size)
{
    int * tmp = (int *) calloc(array_size, sizeof(int));

    for (int width = 1; width < array_size; width <<= 1)
    {
        for(int i = 0; i < array_size; i += 2 * width)
        {
            int lower_limit = (array_size < (i+width)) ? array_size : (i + width);
            int upper_limit = (array_size < (i+2*width)) ? array_size : (i + 2*width);
            merge_sort(array, array_size, i, lower_limit, upper_limit, tmp);
        }

        memcpy(array, tmp, array_size * sizeof(int));
    }

}

//Calculate permutations. This'll be very slow for large inputs
uint64_t calc_permutations(int * array, int size, int idx, int target, int step)
{
    uint64_t count = (array[idx] + 3) >= target;
    printf("%d\n", idx);
    for (int i = idx + 1; i < size && (array[idx] + 3) >= array[i]; ++i)
    {
        count += calc_permutations(array, size, i, target, step+1);
    }

    return count;
}

uint64_t calc_reachable(int * array, int size)
{
    uint64_t count = 0;

    int * tmp = (int *) calloc(size + 1, sizeof(int));
    memcpy(tmp, array, size * sizeof(int));
    array[size] = array[size - 1] + 3;
    uint64_t* reachable = (uint64_t *) calloc(size + 1, sizeof(uint64_t));


    for(int i = 0; i < size; ++i)
    {
        for(int j = i + 1; j < (size + 1); ++j)
        {
            if (array[j] > (array[i] + 3))
            {
                break;
            }
            reachable[i]++;
        }
        reachable[i]--;
    }

    for(int i = size - 1; i >= 0; --i)
    {
        for(int j = i + 1; j <= size; ++j)
        {
            if (array[j] <= array[i] + 3)
            {
                reachable[i] += reachable[j];
            }
        }
    }
  
    for(int i  = 0; i < size && array[i] <= 3; ++i)
    {
        count += reachable[i] + 1;
    }

    return count;
}

uint64_t count_options(int * array, int size, int target)
{
    uint64_t count = 0;
    int i = 0;

    while(array[i] <= 3)
    {
        count += calc_permutations(array, size, i, array[size - 1] + 3, 0);
        i++;
    }

    return count;
}

int count_jumps(int * array, int size)
{
    int three_count = 1;
    int one_count = 0;

    int curr_value = 0;
    for (int i = 0; i < size; ++i)
    {
        switch(array[i] - curr_value)
        {
            case 3:
                three_count++;
                break;
            case 1:
                one_count++;
                break;
            default:
                break;
        }

        curr_value = array[i];
    }

    //printf("Threes: %d, Ones: %d, total: %d\n", three_count, one_count, three_count * one_count);
    return three_count * one_count;

}
int main(int argc, char ** argv)
{
    FILE * input = fopen("day10.txt", "r");

    int adapters[1024] = {};
    int idx = 0;

    char * line = NULL;
    size_t line_size = 0;

    while(getline(&line, &line_size, input) != -1)
    {
        adapters[idx++] = atoi(line);
        if( idx > 1024) 
        {
            printf("Exceeded array size\n");
            exit(1);
        }
    }

    sort_adapters(adapters, idx);
    printf("Answer 1: %d\n", count_jumps(adapters, idx));
    printf("Answer 2: %lu\n", calc_reachable(adapters, idx));

}