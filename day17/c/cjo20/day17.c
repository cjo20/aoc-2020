#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DIM 26

int grid_index(int h, int r, int c)
{
    return h * DIM * DIM + r * DIM + c;
}

int count_neighbours_active(char * grid, int h, int r, int c)
{
    int num_active = 0;
    for (int hh = h - 1; hh <= h + 1; hh++)
    {
        for (int rr = r - 1; rr <= r + 1; rr++)
        {
            for (int cc = c - 1; cc <= c + 1; cc++)
            {
                if (h == hh && r == rr && c == cc) continue;
                num_active += grid[grid_index(hh, rr, cc)];
            }
        }
    }
    return num_active;
}

void run_step(char * grid, int current_width, int current_offset)
{
    char * grid_copy = (char *) malloc(DIM * DIM * DIM * sizeof(char));

    memcpy(grid_copy, grid, DIM*DIM*DIM*sizeof(char));
    for (int hh = current_offset; hh < current_width + current_offset; hh++)
    {
        for (int rr = current_offset; rr < current_width + current_offset; rr++)
        {
            for (int cc = current_offset; cc < current_width + current_offset; cc++)
            {
                int active_neighbours = count_neighbours_active(grid_copy, hh, rr, cc);
                if (grid_copy[grid_index(hh, rr, cc)])
                {
                    switch (active_neighbours)
                    {
                        case 2:
                        case 3:
                            // do nothing
                            break;
                        default:
                            grid[grid_index(hh, rr, cc)] = 0;
                            break;
                    }
                }

                if (!grid_copy[grid_index(hh, rr, cc)])
                {
                    if (active_neighbours == 3) grid[grid_index(hh, rr, cc)] = 1;;
                }
            }
        }
    }
}

int count_active(char * grid, int current_width, int current_offset)
{
    int active = 0;
    for (int hh = current_offset; hh < current_width + current_offset; hh++)
    {
        for (int rr = current_offset; rr < current_width + current_offset; rr++)
        {
            for (int cc = current_offset; cc < current_width + current_offset; cc++)
            {
                active += grid[grid_index(hh, rr, cc)];
            }
        }
    }
    printf("Found %d active\n", active);
    return active;
}

void print_grid(char * grid, int current_width, int current_offset)
{
    for (int hh = current_offset; hh < current_width + current_offset; hh++)
    {
        printf("\n\nZ = %d\n", hh);
        for (int rr = current_offset; rr < current_width + current_offset; rr++)
        {
            for (int cc = current_offset; cc < current_width + current_offset; cc++)
            {
                printf("%d", grid[grid_index(hh, rr, cc)]);
            }
            printf("\n");
        }
    }   
}


int main(void)
{
    int answer1 = 0;
    int answer2 = 0;

    FILE * input = fopen("day17.txt", "r");

    printf("Hello, world!\n");
            // h   r    c 
    //char grid[DIM][DIM][DIM] = {0};

    char * grid = (char *) calloc(DIM * DIM * DIM, sizeof(char));
    int initial_width = 0;
    int initial_offset = 0;
    int current_width = 0;
    int current_offset = 0;
    fscanf(input, "%d\n", &initial_width);
    initial_offset = (DIM - initial_width) / 2;
    current_width = initial_width;
    current_offset = initial_offset;

    printf("Initial width: %d, Initial offset %d\n", initial_width, initial_offset);
  //  while(getline(&line, &line_size, input) != -1)
  //  {
        for(int r = initial_offset; r < initial_width + initial_offset; ++r)
        {
            for( int c = initial_offset; c < initial_width + initial_offset; ++c)
            {
                
                char inp = fgetc(input);
                printf("%d %d %d: %c\n", initial_offset, r, c, inp);
                if (inp == '.') grid[grid_index(initial_offset, r, c)] = 0;
                else grid[grid_index(initial_offset, r, c)] = 1;
            }
            printf("Done row %d\n", r);
            fgetc(input);

        }
 //   }

    print_grid(grid, current_width, current_offset);
    for(int i = 0; i < 6; ++i)
    {
        printf("Step = %d\n", i);
        current_width += 2;
        current_offset -= 1;
        run_step(grid, current_width, current_offset);
        print_grid(grid, current_width, current_offset);
    }

    printf("Current width: %d, Current offset %d\n", current_width, current_offset);
    answer1 = count_active(grid, current_width, current_offset);

    printf("Answer 1: %d\n", answer1);
    printf("Answer 2: %d\n", answer2);
}