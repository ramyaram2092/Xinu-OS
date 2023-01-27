#include<xinu.h>
#include<stdio.h>
#include<prodcons.h>
#include<string.h>
#include <ctype.h>


shellcmd xsh_prodcons(int nargs, char *args[])
{
    int count;
    
    // check if the argument  passed is a number 
    char s[]= args[1];
    if(nargs==2)
    {
        int i=0;
        while(i<strlen(s))
        {
            if(!isdigit(s[i]))
            {
                printf("Not a number \n");
                return 0;
            }
            i++;
        }
    }


    // if there are no argument passed 
    else if(nargs==1)
    {
        count=2000;
    }
    else
    {
        count=atoi(args[1]);
    }

        resume(create(producer,1024,20, "producer",1,count));
        resume(create(consumer,1024,20,"consumer",1,count));

    return 0;
}

