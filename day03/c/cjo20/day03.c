#include <stdio.h>
#include <stdlib.h>

int count_lines(FILE * input, int *line_width)
{
    int lines = 0;
    int max_line_width = 0;
    int width = 0;
    char c;
    while((c = fgetc(input)) != -1)
    {
        
        if (c == '\n')
        {
            if (width > max_line_width)
            {
                max_line_width = width;
            }
            width = 0;
            lines++;
        }
        else {
            width++;
        }
    }

    *line_width = max_line_width;

    fseek(input, 0, SEEK_SET);
    return lines;
}


void read_grid(FILE * input, char * grid)
{
    char * loc = grid;
    while(1)
    {
        char c = fgetc(input);
        switch(c)
        {
            case '.':
                *loc++ = 0;
                break;

            case '#':
                *loc++ = 1;
                break;

            case -1:
                return;

            case '\n':
                continue;
        }
    }
}

int traverse_grid(char * grid, int grid_width, int grid_height, int startX, int startY, int xOffset, int yOffset)
{
    int num_trees = 0;
    int x = startX;
    int y = startY;

    while(y <= grid_height)
    {
        if (grid[y * grid_width + x])
        {
            num_trees++;
        }

        x += xOffset;
        x %= grid_width;

        y+= yOffset;
    }

    return num_trees;
}

int main(int argc, char * argv[])
{
    FILE * input = fopen("day03.txt", "r");

    int num_lines, line_width;

    num_lines = count_lines(input, &line_width);

    printf("Got a file with %d lines, max width %d\n", num_lines, line_width);

    int array_size = num_lines * line_width;

    char  * grid = malloc(array_size * sizeof(char));

    read_grid(input, grid);

    printf("Trees encountered on (3, 1): %d\n", traverse_grid(grid, line_width, num_lines, 0, 0, 3, 1));

    int64_t second_answer = 1;

    second_answer *= (int64_t) traverse_grid(grid, line_width, num_lines, 0, 0, 1, 1);
    second_answer *= (int64_t) traverse_grid(grid, line_width, num_lines, 0, 0, 3, 1);
    second_answer *= (int64_t) traverse_grid(grid, line_width, num_lines, 0, 0, 5, 1);
    second_answer *= (int64_t) traverse_grid(grid, line_width, num_lines, 0, 0, 7, 1);
    second_answer *= (int64_t) traverse_grid(grid, line_width, num_lines, 0, 0, 1, 2);

    printf("Second answer: %lu\n", second_answer);
    return 0;
}