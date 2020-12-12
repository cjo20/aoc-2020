#include <stdio.h>
#include <stdlib.h>


int answer_one(FILE * input)
{
    char * line = NULL;
    size_t line_size = 0;
    int r = 0, c = 0;
    char facing_dirs[] = {'N', 'E', 'S', 'W'};
    int facing = 1;
    while(getline(&line, &line_size, input) != -1)
    {
        char dir;
        int distance;

        sscanf(line, "%c%d", &dir, &distance);
       // printf("Got %c%d\n", dir, distance);

        if (dir == 'F')
        {
            dir = facing_dirs[facing];
        }

        switch(dir)
        {
            case 'N':
                r += distance;
                break;

            case 'S':
                r -= distance;
                break;

            case 'E':
                c += distance;
                break;

            case 'W':
                c -= distance;
                break;

            case 'L':
                facing -= (distance / 90);
                facing += 4;
                facing %= 4;
                break;

            case 'R':
                facing += (distance / 90);
                facing %= 4;
                break;
        }

       // printf("Now at E%d N%d, ", c, r);
       // printf("Facing: %c\n", facing_dirs[facing]);
    }
    return abs(c) + abs(r);
}


int answer_two(FILE * input)
{
    char * line = NULL;
    size_t line_size = 0;
    
    int ship_r = 0, ship_c = 0;
    int way_r =  1, way_c = 10;

    while(getline(&line, &line_size, input) != -1)
    {
        char dir;
        int distance;

        sscanf(line, "%c%d", &dir, &distance);
       // printf("Got %c%d\n", dir, distance);
        int tmp = 0;
        switch(dir)
        {
            case 'F':
                ship_r += distance * way_r;
                ship_c += distance * way_c;
                break;

            case 'N':
                way_r += distance;
                break;

            case 'S':
                way_r -= distance;
                break;

            case 'E':
                way_c += distance;
                break;

            case 'W':
                way_c -= distance;
                break;

            case 'R':
                for (int i = 0; i < distance; i += 90)
                {
                    way_c *= -1;
                    tmp = way_c;
                    way_c = way_r;
                    way_r = tmp;
                }
                break;

            case 'L':
                for (int i = 0; i < distance; i += 90)
                {
                    way_r *= -1;
                    tmp = way_c;
                    way_c = way_r;
                    way_r = tmp;
                }
                break;
        }

       // printf("Now at E%d N%d, ", ship_c, ship_r);
       // printf("Waypoint: %dE %dN\n", way_c, way_r);
    }
    return abs(ship_c) + abs(ship_r);    
}

int main(void)
{
    FILE * input = fopen("day12.txt", "r");

    printf("Answer 1: %d\n", answer_one(input));
    fseek(input, 0 , SEEK_SET);
    printf("Answer 2: %d\n", answer_two(input));
}