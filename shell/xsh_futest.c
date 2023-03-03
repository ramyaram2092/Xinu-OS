#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <processterminator.h>
#include <prodcons_fut.h>
#include <helper.h>
#include <string.h>
#include <ctype.h>

future_t *f;
// int value = 0;

shellcmd xsh_futest(int nargs, char *args[])
{

    // case 1: missing arguments
    if (nargs <= 1)
    {
        printf("Missing arguments\n");
        // signal(completecmd);
        return 0;
    }

    // case 2: check the correctness of input
    else
    {
        for (int i = 1; i < sizeof(args); i++)
        {
            if ( isnumber(args[i]) || args[i][0] != 'g')
            {
                printf("Invalid arguments : %c\n",args[i][0]);
                // signal(completecmd);
                return 0;
            }
        
    }
    }

    // create future
    f = future_alloc(FUTURE_EXCLUSIVE, sizeof(uint), 1);

    // iterate through the arguments and perform the expected operations
    for (int i = 0; i < sizeof(args); i++)
    {
        if (isnumber(args[i]))
        {
            resume(create(producer_fut, 1024, 20, "producer_fut", 2, atoi(args[i]), f));
        }
        else if (args[i] == 'g')
        {
            resume(create(consumer_fut, 1024, 20, "consumer_fut", 1, f));
        }
    }

    // destroy the future
}

// check if the the string is a valid number
bool isnumber(char *val)
{
    char *s;
    for (s = val; *s != '\0'; s++)
    {
        if (!isdigit(*s))
        {
            return false;
        }
    }
    return true;
}