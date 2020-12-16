#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


typedef struct rules
{
    char name[32];
    int lower_a, upper_a;
    int lower_b, upper_b;
} rule_t;

int test_rule(rule_t * rule, int num)
{
    int valid = 0;
   // printf("Testing: %s\n", rule->name);
    if (rule->lower_a <= num && rule->upper_a >= num) valid = 1;
    if (rule->lower_b <= num && rule->upper_b >= num) valid = 1;

    return valid;
}

// Return a bitmasks of rules for which num is valid
int  test_all_rules(rule_t * rules, int num_rules, int num)
{
    int valid = 0;

    for(int i = 0; i < num_rules; ++i)
    {
        valid |= (test_rule(rules+i, num) << i);
    }

    return valid;
}

void process_rule(rule_t * rules, int idx, char * line)
{
    char name[32] = {};
    int lower_a = 0, lower_b = 0; 
    int upper_a = 0, upper_b = 0;

    sscanf(line, "%[^:]: %d-%d or %d-%d\n", name, &lower_a, &upper_a, &lower_b, &upper_b);

    strcpy(rules[idx].name, name);
    rules[idx].lower_a = lower_a;
    rules[idx].lower_b = lower_b;
    rules[idx].upper_a = upper_a;
    rules[idx].upper_b = upper_b;

    printf("Got rule (%s) -> (%d-%d, %d-%d)\n", rules[idx].name, rules[idx].lower_a, rules[idx].upper_a, rules[idx].lower_b, rules[idx].upper_b);
}

int count_bits(int num)
{
    int count = 0;
    if (num == 0) return 0;
    while (num)
    {
        count++;
        num &= (num - 1);
    }
    return count;
}

int get_bit_position(int num)
{
    int pos = 0;
    for (pos = 0; pos < sizeof(num) * 8; ++pos)
    {
        if ((1 << pos) == num) return pos;
    }

    return 0;
}
int main(void)
{
    int answer1 = 0;
    uint64_t answer2 = 0;

    FILE * input = fopen("day16.txt", "r");

    char * line = NULL;
    size_t line_size = 0;
    int string_length = 0;
    printf("Hello, world!\n");

    rule_t * rules = NULL;
    int num_rules = 0;

    //Read in the rules
    while((string_length = getline(&line, &line_size, input)) != 1)
    {  
        num_rules++;
        rules = realloc(rules, num_rules * sizeof(rule_t));
        process_rule(rules, num_rules - 1, line);
    }

    getline(&line, &line_size, input); // "your ticket"

    //Store my ticket
    int * my_ticket = (int *) calloc(num_rules, sizeof(int));   
    int i = 0;
    int val = 0;
    while(fscanf(input, "%d", &val) == 1)
    {
        my_ticket[i++] = val;
        if(fgetc(input) == '\n') break;
    }

    getline(&line, &line_size, input); // \n
    getline(&line, &line_size, input); // "nearby tickets:"

    int*  rule_masks = (int *) calloc(num_rules, sizeof(int));
    int * tmp_masks = (int *) calloc(num_rules, sizeof(int));
    int * mapping = (int *) calloc(num_rules, sizeof(int));

    //Initialise the global mask for rules 
    for (int i = 0; i < num_rules; ++i)
    {
        rule_masks[i] = (1 << num_rules) - 1;
    }

    while(!feof(input))
    {
        int ticket_valid = 1;
        int val = 0;
        int rule_num = 0;
        memset(tmp_masks, 0, num_rules * sizeof(int));
        
        while(fscanf(input, "%d", &val) == 1)
        {
            int mask = test_all_rules(rules, num_rules, val);
            if(!mask) { answer1 += val;}
            ticket_valid &= !!mask; //reduce mask to a 1 or 0
            //Mask of rules for which val is valid
            tmp_masks[rule_num++] = mask;

            if(fgetc(input) == '\n') break;
        }

        // If the ticket is valid, update the global masks
        if (ticket_valid)
        {
            for(int i = 0; i < num_rules; ++i)
            {
                rule_masks[i] &= tmp_masks[i];
            }
        }
    }

    // Multiple valid positions for some rules. Starts with
    // one rule with only one valid position, remove that position from
    // all the other rules, repeat until done
    int stable = 0;

    while(!stable)
    {
        for(int i = 0; i < num_rules; ++i)
        {
            stable = 1;
            if (count_bits(rule_masks[i]) == 1)
            {
                mapping[i] = get_bit_position(rule_masks[i]);
                for(int k = 0; k < num_rules; ++k)
                {
                    rule_masks[k] &= ~(1 << mapping[i]);
                }
                stable = 0;
                break;
            }
        }
    }
 
    answer2 = 1;
    for(int i = 0; i < num_rules; ++i)
    {
        rule_t * rule = rules+mapping[i];
        if(strncmp(rule->name, "departure", 9) == 0) 
        {
            answer2 *= my_ticket[i];
        }

    }
    printf("\nAnswer 1: %d\n", answer1);
    printf("Answer 2: %lu\n", answer2);
}