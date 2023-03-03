#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <stdbool.h>
#include <processterminator.h>



bool isnumber(char *s);
future_t *f;
int value = 0;
int *p;

shellcmd xsh_futest(int nargs, char *args[])
{
    p = &value;

    

    // case 1: missing arguments
    if (nargs == 0)
    {
        printf("Missing arguments\n");
        signal(completecmd);
        return 0;
    }

    // case 2: check the correctness of input
    else
    {
        for (int i = 0; i < sizeof(args); i++)
        {
            if (args[i] != isnumber(args[i]) || args[i] != "g")
            {
                printf("Invalid arguments\n");
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
        if (args[i] == isnumber(args[i]))
        {
            resume(create(produce_fut, 1024, 20, "producer_fut", 2, atoi(args[i]), f));
        }
        else if (args[i] == "g")
        {
            resume(create(produce_fut, 1024, 20, "consumer_fut", 1, f->data));
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