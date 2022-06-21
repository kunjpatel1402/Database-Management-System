#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "table.h"
//#include "row.h"
//#include "File_instructions.h"
//#include "Read_input.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

bool is_int(char *str)
{
    int i = 0;
    if (str[0] == '-')
    {
        i++;
    }
    for (; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return false;
        }
    }
    return true;
}
bool is_double(char *str)
{
    int i = 0;
    if (str[0] == '-')
    {
        i++;
    }
    for (; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            if (str[i] == '.')
            {
                i++;
                for (; str[i] != '\0'; i++)
                {
                    if (str[i] < '0' || str[i] > '9')
                    {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
    }
    return true;
}
bool is_char(char *str)
{
    if (strlen(str) == 1)
    {
        return true;
    }
    return false;
}