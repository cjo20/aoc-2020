#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

int validate_passport(char num_fields, char has_cid, char valid)
{
    //printf("Valid?%d, Fields?%d CID?%d\n", valid, num_fields, has_cid);
    return valid && ((num_fields - has_cid) == 7);
}

int read_passport(FILE * input)
{
    char num_fields = 0;
    char has_cid = 0;

    char * line = NULL;
    size_t line_length = 0;

    size_t chars_read = 0;
    
    char valid = 1;

    while(!feof(input))
    {
        chars_read = getline(&line, &line_length, input);
        if (chars_read == 1 && line[0] == '\n') //next entry
        {
            free(line);
            //printf("Found passport with %d fields, CID: %d\n", num_fields, has_cid);
            return validate_passport(num_fields, has_cid, valid);
        }

        char ident[4] = {};
        char data[128] = {};

        
        int line_offset = 0;
        int chars_read = 0;
        while (sscanf(line+line_offset, "%[^:] : %[^ \n] %n", ident, data, &chars_read) == 2)
        {
            line_offset += chars_read;
            
           // printf("Got %s:%s (%d)\n", ident, data, chars_read);
            if(strcmp(ident, "cid") == 0)
            {
                has_cid = 1;
                num_fields++;
                continue;
            }

            if(!strcmp(ident, "byr"))
            {
                num_fields++;
                int year = atoi(data);
                if (year < 1920 || year > 2002 || strlen(data) != 4)
                {
                 //   printf("%d is invalid byr", year);
                    valid = 0;
                } 
                
                continue;
            }

            if(!strcmp(ident, "iyr"))
            {
                num_fields++;
                int year = atoi(data);
                if (year < 2010 || year > 2020 || strlen(data) != 4)
                {
                 //   printf("Invalid iyr %s\n", data);
                    valid = 0;
                }
                continue;
            }

            if(!strcmp(ident, "eyr"))
            {
                num_fields++;
                int year = atoi(data);
                if (year < 2020 || year > 2030 || strlen(data) != 4) 
                {
                  //  printf("Invalid eyr %s\n", data);
                    valid = 0;
                }
                continue;
            }

            
            if(!strcmp(ident, "hcl"))
            {
                num_fields++;
                regex_t reg;
                regcomp(&reg,"#[0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f]",0);
                if(strlen(data) != 7 || regexec(&reg, data, 0, NULL, 0)){
                    valid = 0;
                }
                continue;
            }

            if(!strcmp(ident, "ecl"))
            {
                num_fields++;
                char amb = strcmp(data, "amb");
                char blu = strcmp(data, "blu");
                char brn = strcmp(data, "brn");
                char gry = strcmp(data, "gry");
                char grn = strcmp(data, "grn");
                char hzl = strcmp(data, "hzl");
                char oth = strcmp(data, "oth");
                
                if (amb && blu && brn && gry && grn && hzl && oth)
                {
                   // printf("Invalid ecl %s\n", data);
                    valid = 0;
                }
                continue;
            }

            if(!strcmp(ident, "pid"))
            {
                num_fields++;
                if (strlen(data) != 9) 
                {
                    valid = 0;
                    continue;

                }
                for(int i = 0; i < 9; ++i)
                {
                    if (data[i] < '0' || data[i] > '9')
                    {
                        valid = 0;
                    }
                    //valid &= !!isdigit(data[i]);
                }

                continue;

            }

            if(!strcmp(ident, "hgt"))
            {
                num_fields++;
                int num = 0;
                char unit[4] = {};
                int read = sscanf(data, "%d%s", &num, unit);

                if (read != 2)
                {
                    valid = 0;
                }

                if (strcmp(unit, "cm") && strcmp(unit, "in"))
                {
                   // printf("invalid height unit");
                    valid = 0;
                    continue;
                }

                if (unit[0] == 'c')
                {
                    if(num < 150 || num > 193) valid = 0;
                }
                else {
                
                    if (num < 59 || num > 76) valid = 0;
                }
                continue;
            }

            valid = 0;

            
        }

        free(line);
        line = NULL;
        line_length = 0;
    }

    return validate_passport(num_fields, has_cid, valid);
}

int main(int argc, char * argv[])
{
    FILE * input = fopen("day04.txt", "r");

    int valid_count = 0;
    while(!feof(input))
    {
        valid_count += read_passport(input);
    }

    printf("Found %d valid passports\n", valid_count);
}


