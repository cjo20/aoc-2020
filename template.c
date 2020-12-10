#include <stdio.h>


int main(void)
{
    int answer1 = 0;
    int answer2 = 0;

    FILE * input = fopen("", "r");

    char * line = NULL;
    size_t line_size = 0;

    printf("Hello, world!\n");

    while(getline(&line, &line_size, input) != -1)
    {
        printf("%s", line);
    }

    printf("Answer 1: %d\n", answer1);
    printf("Answer 2: %d\n", answer2);
}