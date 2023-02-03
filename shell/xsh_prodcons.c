#include<xinu.h>
#include<stdio.h>
#include<prodcons.h>
#include<string.h>
#include <ctype.h>

/** Global Variables **/ 
int n=0; 
sid32 prod,cons;

/** prodcons function definition **/
shellcmd xsh_prodcons(int nargs, char *args[])
{
    int count; 
    prod=semcreate(0);
    cons=semcreate(1);

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
        count=200;
    }

    resume(create(producer,1024,20, "producer",3,prod,cons,count));
    resume(create(consumer,1024,20,"consumer",3,prod,cons,count));

    return 0;
}

