#include <stdio.h>

int count_bits(int num)
{
    int count = 0;

    while (num)
    {
        num &= (num - 1);
        count++;
    }

    return count;
}

int answer_mask(char * line, int num_chars)
{
    int i = 0;
    int answer_mask = 0;
    while(i < num_chars && line[i] != '\n')
        answer_mask |= (1 << (line[i++] - 'a'));

    return answer_mask;
}

int main()
{
    FILE * input  = fopen("day06.txt", "r");

    char * line = NULL;
    size_t line_length = 0;
    int num_chars = 0;

    int answer_any_mask = 0;
    int answer_all_mask = 0x3ffffff;
    int total_any = 0;
    int total_all = 0;
    while((num_chars = getline(&line, &line_length, input)) != -1)
    {
        //printf("Read %d characters - %s", num_chars, line);
        if (num_chars > 1 || feof(input))
        {
            answer_any_mask |= answer_mask(line, num_chars);
            answer_all_mask &= answer_mask(line, num_chars);
        }

        if(num_chars == 1 || feof(input))
        {
            total_any += count_bits(answer_any_mask);
            int tmp  =  count_bits(answer_all_mask);
            total_all += tmp;
            answer_any_mask = 0;
            answer_all_mask = 0x3ffffff;    
        }
    }

    printf("Answer 1: %d\n", total_any);
    printf("Answer 2: %d\n", total_all);
}