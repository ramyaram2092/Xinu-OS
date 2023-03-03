#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <processterminator.h>
#include <prodcons_fut.h>
#include <helper.h>
#include <string.h>
#include <ctype.h>

future_t *f1, f2;
int value, n;
volatile int flag;
sid32 print;

shellcmd xsh_futest(int nargs, char *args[])
{
    value = -1;
    flag = 0;
    n=0;
    print=semcreate(1);

    // case 1: missing arguments
    if (nargs < 3)
    {
        printf("Missing arguments\n");
        // signal(completecmd);
        return 0;
    }

    // case 2: check the correctness of input
    else
    {
        for (int i = 1; i < nargs; i++)
        {
            if (!(isnumber(args[i]) || strncmp(args[i], "g", 1) == 0))
            {
                printf("Invalid arguments \n");
                // signal(completecmd);
                return 0;
            }
        }
    }

    // create future
    f1 = future_alloc(FUTURE_EXCLUSIVE, sizeof(uint), 1);

    // iterate through the arguments and perform the expected operations
    for (int i = 1; i < nargs; i++)
    {
        // printf("Executing loop :%d times\n",i);
        if (isnumber(args[i]))
        {
            resume(create(producer_fut, 1024, 20, "producer_fut", 2, atoi(args[i]), f1));
        }
        else if (strncmp(args[i], "g", 1) == 0)
        {
            resume(create(consumer_fut, 1024, 20, "consumer_fut", 1, f1));
        }
    }


    // case 1: if last processor is producer
    if (atoi(args[nargs - 1]))
    {
        n = nargs - 1;
    }
    // case 2 : if last but one processor is consumer
    else if (strncmp(args[nargs - 2], "g", 1) == 0)
    {
        n = nargs - 2;
    }

    while (flag < n)
    {
        // wait untill all process are complete
    }

    // free the future and kill the suspended process
    future_free(f1);
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