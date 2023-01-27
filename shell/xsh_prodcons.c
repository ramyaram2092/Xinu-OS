#include<xinu.h>
#include<stdio.h>
#include<prodcons.h>
#include<string.h>
#include <ctype.h>


shellcmd xsh_prodcons(int nargs, char *args[])
{
    int count; // local variable
    
    // check if the argument  passed is a number 
    char *s;    
    if(nargs==2)
    {
        for(s=args[1];*s!='\0';s++)
        {
            if(!isdigit(*s))
            {
                printf("Not a number \n");
                return 0;
            }
        }
        count=atoi(args[1]);
    }


    // if there are no argument passed 
    else if(nargs==1)
    {
        count=2000;
    }

    resume(create(producer,1024,20, "producer",1,count));
    resume(create(consumer,1024,20,"consumer",1,count));

    return 0;
}

