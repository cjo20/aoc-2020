#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct requirement
{
    char colour[32];
    int amount;
} req_t;

typedef struct rule
{
    char colour[32];
    int num_requirements;
    req_t requirement[8];
} rule_t;

int read_colour(char * colour, char * input)
{
    sscanf(input, "%s ", colour);
    int len = strlen(colour);
    colour[len] = ' ';
    sscanf(input + len + 1, "%s ", colour + len + 1);

    return strlen(colour);
}

void readRule(rule_t * rule, char * line, size_t line_size)
{
    int read = 0;
    rule->num_requirements = 0;
    int i = read_colour(rule->colour, line);
    i += strlen(" bags contai"); //leave "n " because it's the same number of chars as ", ". Simplifies the loop

    while(line[i] != '.')
    {
        i += 2;

        if (line[i] == 'n') // case where it contains no other bags
        {
            return;
        }
        sscanf(line + i, "%d%n", &rule->requirement[rule->num_requirements].amount, &read);
        i += read;
        
        i += read_colour(rule->requirement[rule->num_requirements].colour, line + i);
        sscanf(line + i, "%*[^,.]%n", &read); //Skip "bag(s?)"
        i += read;
        rule->num_requirements++;
    }
}

int find_rule(char * colour, rule_t rules[], int num_rules)
{
    for (int i = 0; i < num_rules; ++i)
    {
        if(!strcmp(colour, rules[i].colour))
        {
            return i;
        }
    }

    printf("Could not find rule for %s\n", colour);
    exit(1);
    return 0;
}

int can_bag_contain(char * target, int rule_offset, rule_t rules[], int num_rules)
{
    rule_t * rule = rules + rule_offset;

    for (int i = 0; i < rule->num_requirements; ++i)
    {
        if (!strcmp(rule->requirement[i].colour, target))
        {
            return 1;
        }

        int t  = can_bag_contain(target, find_rule(rule->requirement[i].colour, rules, num_rules), rules, num_rules);
        if(t)
        {
            return 1;
        }
    }

    return 0;
}

int must_contain(rule_t * rule, rule_t rules[], int num_rules)
{
    int num_required = 1;

    for (int i = 0; i < rule->num_requirements; ++i)
    {
        req_t * req = rule->requirement + i;
        num_required += req->amount * must_contain(rules + find_rule(req->colour, rules, num_rules), rules, num_rules);
    }

    return num_required;
}

int num_bags_contain(char * target, rule_t rules[], int num_rules)
{
    int sum = 0;
    for(int i = 0; i < num_rules; ++i)
    {
        sum += can_bag_contain(target, i, rules, num_rules);
    }

    return sum;
}

int main()
{

    int num_rules = 0;    
    rule_t rules[1024];

    FILE * input =  fopen("day07.txt", "r");

    char * line = NULL;
    size_t line_size = 0;

    while(getline(&line, &line_size, input) != -1)
    {
        readRule(rules + num_rules, line, line_size);
        num_rules++;
    }

    int total_allowed = num_bags_contain("shiny gold", rules, num_rules);

    int num_bags = must_contain(rules + find_rule("shiny gold", rules, num_rules), rules, num_rules) - 1;
    
    printf("Answer 1: %d\n", total_allowed);
    printf("Answer 2: %d\n", num_bags);
}