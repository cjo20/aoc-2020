#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define IDX(r, c) (((r) * num_columns) + (c))

#define UL 0
#define U 1
#define UR 2
#define L 3
#define R 4
#define DL 5
#define D 6
#define DR 7

void print_table(char* array, int num_lines, int num_columns)
{

    for (int r = 0; r < num_lines; ++r)
    {
        for (int c = 0; c < num_columns; ++c)
        {
            switch (array[IDX(r,c)])
            {
                case 0:
                    printf("L");
                    break;
                case 1:
                    printf("#");
                    break;
                case CHAR_MAX:
                    printf(".");
                    break;
            }
        }
        printf("\n");
    }
}

int check_adjacent(char * array, int num_lines, int num_columns, int r, int c, int dir)
{
    switch(dir)
    {
        case UL:
            if (r == 0 || c == 0) return 0;
            else return array[IDX(r-1, c-1)] == 1;
            break;

        case U:
            if (r == 0) return 0;
            else return array[IDX(r-1, c)] == 1;
            break;

        case UR:
            if (r == 0 || c == (num_columns - 1)) return 0;
            else return array[IDX(r-1, c+1)] == 1;
            break;

        case L:
            if (c == 0) return 0;
            else return array[IDX(r, c-1)] == 1;
            break;

        case R:
            if (c == (num_columns - 1)) return 0;
            else return array[IDX(r, c+1)] == 1;
            break;

        case DL:
            if (r == (num_lines - 1) || c == 0) return 0;
            else return array[IDX(r+1, c-1)] == 1;
            break;

        case D:
            if (r == (num_lines - 1)) return 0;
            else return array[IDX(r+1, c)] == 1;
            break;

        case DR:
            if (r == (num_lines - 1) || c == (num_columns - 1)) return 0;
            else return array[IDX(r+1, c+1)] == 1;
            break;                      
    }

    return 0;
}

int check_all_directions(char * array, int num_lines, int num_columns, int r, int c)
{
    int sum = 0;

    sum += check_adjacent(array, num_lines, num_columns, r, c, UL);
    sum += check_adjacent(array, num_lines, num_columns, r, c, U);
    sum += check_adjacent(array, num_lines, num_columns, r, c, UR);
    sum += check_adjacent(array, num_lines, num_columns, r, c, L);
    sum += check_adjacent(array, num_lines, num_columns, r, c, R);
    sum += check_adjacent(array, num_lines, num_columns, r, c, DL);
    sum += check_adjacent(array, num_lines, num_columns, r, c, D);
    sum += check_adjacent(array, num_lines, num_columns, r, c, DR);

    if( r == 0)
    {
      // printf("c: %d, sum: %d\n", c, sum);
    }
    return sum;
}


int check_adjacent_2(char * array, int num_lines, int num_columns, int r, int c, int dir)
{
    while(1)
    {
        switch(dir)
        {
            case UL:
                if (r == 0 || c == 0) return 0;
                else if (array[IDX(r-1,c-1)] == CHAR_MAX) {
                    r -= 1;
                    c -= 1;
                    continue;
                }
                else return array[IDX(r-1, c-1)] == 1;
                break;

            case U:
                if (r == 0) return 0;
                else if (array[IDX(r-1,c)] == CHAR_MAX) {
                    r -= 1;
                    continue;
                }                
                else return array[IDX(r-1, c)] == 1;
                break;

            case UR:
                if (r == 0 || c == (num_columns - 1)) return 0;
                else if (array[IDX(r-1,c+1)] == CHAR_MAX) {
                    r -= 1;
                    c += 1;
                    continue;
                }                
                else return array[IDX(r-1, c+1)] == 1;
                break;

            case L:
                if (c == 0) return 0;
                else if (array[IDX(r,c-1)] == CHAR_MAX) {
                    c -= 1;
                    continue;
                }                
                else return array[IDX(r, c-1)] == 1;
                break;

            case R:
                if (c == (num_columns - 1)) return 0;
                else if (array[IDX(r,c+1)] == CHAR_MAX) {
                    c += 1;
                    continue;
                }                
                else return array[IDX(r, c+1)] == 1;
                break;

            case DL:
                if (r == (num_lines - 1) || c == 0) return 0;
                else if (array[IDX(r+1,c-1)] == CHAR_MAX) {
                    r += 1;
                    c -= 1;
                    continue;
                }                
                else return array[IDX(r+1, c-1)] == 1;
                break;

            case D:
                if (r == (num_lines - 1)) return 0;
                else if (array[IDX(r+1,c)] == CHAR_MAX) {
                    r += 1;
                    continue;
                }                
                else return array[IDX(r+1, c)] == 1;
                break;

            case DR:
                if (r == (num_lines - 1) || c == (num_columns - 1)) return 0;
                else if (array[IDX(r+1,c+1)] == CHAR_MAX) {
                    r += 1;
                    c += 1;
                    continue;
                }                
                else return array[IDX(r+1, c+1)] == 1;
                break;                      
        }
    }

    return 0;
}

int check_all_directions_2(char * array, int num_lines, int num_columns, int r, int c)
{
    int sum = 0;

    sum += check_adjacent_2(array, num_lines, num_columns, r, c, UL);
    sum += check_adjacent_2(array, num_lines, num_columns, r, c, U);
    sum += check_adjacent_2(array, num_lines, num_columns, r, c, UR);
    sum += check_adjacent_2(array, num_lines, num_columns, r, c, L);
    sum += check_adjacent_2(array, num_lines, num_columns, r, c, R);
    sum += check_adjacent_2(array, num_lines, num_columns, r, c, DL);
    sum += check_adjacent_2(array, num_lines, num_columns, r, c, D);
    sum += check_adjacent_2(array, num_lines, num_columns, r, c, DR);

    if( r == 0)
    {
      // printf("c: %d, sum: %d\n", c, sum);
    }
    return sum;
}

int solution_one(char * table, int num_lines, int num_columns)
{
    int table_size = num_lines * num_columns;
    char * table_copy = (char *) calloc(table_size, sizeof(char));
    int num_changes = 1;
    memcpy(table_copy, table, table_size * sizeof(char));
    while(num_changes)
    {
        num_changes = 0;
        for(int r = 0; r < num_lines; ++r)
        {
            for (int c = 0; c < num_columns; ++c)
            {
                if (table[IDX(r,c)] == 0 && check_all_directions(table, num_lines, num_columns, r, c) == 0)
                {
                    table_copy[IDX(r,c)] = 1;
                    num_changes++;
                }

                if(table[IDX(r,c)] == 1 && check_all_directions(table, num_lines, num_columns, r, c) >= 4)
                {
                    table_copy[IDX(r,c)] = 0;
                    num_changes++;
                }
            }
        }

        memcpy(table, table_copy, table_size * sizeof(char));
        printf("Num changes: %d\n", num_changes);
       // print_table(table, num_lines, num_columns);
        printf("\n\n");
    }


    int answer = 0;
    for (int i = 0 ; i < table_size; ++i)
    {
        answer += (table[i] == 1);
    }

    return answer;
}

int solution_two(char * table, int num_lines, int num_columns)
{
    int table_size = num_lines * num_columns;
    char * table_copy = (char *) calloc(table_size, sizeof(char));
    int num_changes = 1;
    memcpy(table_copy, table, table_size * sizeof(char));
    while(num_changes)
    {
        num_changes = 0;
        for(int r = 0; r < num_lines; ++r)
        {
            for (int c = 0; c < num_columns; ++c)
            {
                if (table[IDX(r,c)] == 0 && check_all_directions_2(table, num_lines, num_columns, r, c) == 0)
                {
                    table_copy[IDX(r,c)] = 1;
                    num_changes++;
                }

                if(table[IDX(r,c)] == 1 && check_all_directions_2(table, num_lines, num_columns, r, c) >= 5)
                {
                    table_copy[IDX(r,c)] = 0;
                    num_changes++;
                }
            }
        }

        memcpy(table, table_copy, table_size * sizeof(char));
        printf("Num changes: %d\n", num_changes);
        print_table(table, num_lines, num_columns);
        printf("\n\n");
    }


    int answer = 0;
    for (int i = 0 ; i < table_size; ++i)
    {
        answer += (table[i] == 1);
    }

    return answer;
}

int main(void)
{
    int answer1 = 0;
    int answer2 = 0;

    FILE * input = fopen("day11.txt", "r");

    char * line = NULL;
    size_t line_size = 0;
    int line_len = 0;

    int num_lines = 0;
    int num_columns = 0;
    while((line_len = getline(&line, &line_size, input)) != -1)
    {
        num_lines++;
        line_len--;
        num_columns = num_columns > line_len ? num_columns : line_len;
    }

    printf("Got %d lines and %d columns\n", num_lines, num_columns);
    int table_size = num_lines * num_columns;
    char * table = (char *) calloc(table_size, sizeof(char));
    char * fresh_table = (char *) calloc(table_size, sizeof(char));
    
    fseek(input, 0 , SEEK_SET);


    int row = 0;
    while((line_len = getline(&line, &line_size, input)) != -1)
    {
        for (int col = 0; col < line_len && line[col] != '\n'; col++)
        {
            if (line[col] == 'L')
            {
                table[IDX(row, col)] = 0;
            } else if (line[col] == '.')
            {
                table[IDX(row, col)] = CHAR_MAX;
            }
        }
        row++;
    }

    print_table(table, num_lines, num_columns);

    fresh_table = memcpy(fresh_table, table, table_size * sizeof(char));
    answer1 = solution_one(fresh_table, num_lines, num_columns);
    answer2 = solution_two(table, num_lines, num_columns);
    printf("Answer 1: %d\n", answer1);
    printf("Answer 2: %d\n", answer2);
}