#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <processterminator.h>
#include <prodcons_fut.h>
#include <helper.h>
#include <string.h>
#include <ctype.h>

future_t *f1,f2;
int value ,flag;


shellcmd xsh_futest(int nargs, char *args[])
{
    value=-1;
    flag=0;

    // complete=semcreate(0);

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
        for (int i = 1; i < nargs; i++)
        {
            if ( !(!isnumber(args[i]) || args[i][0] != 'g'))
            {
                printf("Invalid arguments \n");
                // signal(completecmd);
                return 0;
            }
        
    }
    }

    // create future
    f1= future_alloc(FUTURE_EXCLUSIVE, sizeof(uint), 1);

    // iterate through the arguments and perform the expected operations
    for (int i = 1; i < nargs; i++)
    {
        // printf("Executing loop :%d times\n",i);
        if (isnumber(args[i]))
        {
            resume(create(producer_fut, 1024, 20, "producer_fut", 2, atoi(args[i]), f1));
        }
        else if (args[i][0] == 'g')
        {
            resume(create(consumer_fut, 1024, 20, "consumer_fut", 1, f1));
        }
    }

    while(flag<nargs-1)
    {
        // wait untill all process are complete
    }

    // free the future
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