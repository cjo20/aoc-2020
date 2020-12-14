#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
int main(void)
{
    int answer1 = 0;

    FILE * input = fopen("day13.txt", "r");

    char * line = NULL;
    size_t line_size = 0;

    printf("Hello, world!\n");

    getline(&line, &line_size, input);

    int value = 0;
    int offset = 0;
    sscanf(line, "%d", &value);
    printf("Arriving at %d\n", value);
    getline(&line, &line_size, input);
    int soonest_id = -1;
    int shortest_wait = 61;
    char id_str[4];
    int len = 0;

    int busses[60] = {};
    int num_busses = 0;
    while(sscanf(line+offset, "%[^,]%n", id_str, &len) == 1)
    {
        offset += len + 1;
        if (id_str[0] == 'x')
        {
            busses[num_busses++] = -1;
            continue;
        }

        int id = atoi(id_str);
        busses[num_busses++] = id;
        int mod = value % id;

        if (mod == 0)
        {
            soonest_id = id;
            shortest_wait = 0;
            break;
        }

        int wait = id - mod;
        
        if (wait < shortest_wait)
        {
            shortest_wait = wait;
            soonest_id = id;
        }
    }

    answer1 = shortest_wait * soonest_id;

    uint64_t  t = 1;
    uint64_t step = 1;
    for(int i = 0; i < num_busses; ++i)
    {
        if (busses[i] == -1) continue;
        while(1)
        {
            printf("Trying bus %d at time %lu. Must arrive in %d minutes, ", busses[i], t, i);
            printf("Arrives in %lu minutes\n", ((t + i) % busses[i]));
            if ((((t + i) % busses[i])) == 0) break;
            t += step;
        }
        step *= busses[i];       
    }
    printf("Answer 1: %d\n", answer1);
    printf("Answer 2: %lu\n", t);

    return 0;
}