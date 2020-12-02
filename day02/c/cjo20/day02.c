#include <stdio.h>
#include <stdlib.h>

int check_sled_password(int min, int max, char c, char * password)
{
    int idx = 0;
    int count = 0;

    while(password[idx] != 0)
    {
        if(password[idx] == c)
        {
            count++;
        }
        idx++;
    }

    if (count < min || count > max)
    {
        return 0;
    }

    return 1;
}

int check_toboggan_password(int left, int right, char c, char * password)
{
    int left_present = password[left - 1] == c;
    int right_present = password[right - 1] == c;

    return left_present ^ right_present;
}

int main(int argc, char *argv[])
{
    FILE * input = fopen("day02.txt", "r");

    char * line = NULL;
    size_t line_size;

    int valid_sled_passwords = 0;
    int valid_toboggan_passwords = 0;

    int min, max;
    char required_char;
    char * password = (char *) malloc(128 * sizeof(char));

    while(getline(&line, &line_size, input) != -1)
    {  
        sscanf(line, "%d-%d %c: %s", &min, &max, &required_char, password);

        valid_sled_passwords += check_sled_password(min, max, required_char, password);
        valid_toboggan_passwords += check_toboggan_password(min, max, required_char, password);
    }

    printf("Valid sled passwords found: %d\n", valid_sled_passwords);
    printf("Valid toboggan passwords found: %d\n", valid_toboggan_passwords);
}