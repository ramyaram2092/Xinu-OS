#include<xinu.h>
#include<stdio.h>
#include<prodcons.h>
#include<string.h>


shellcmd xsh_prodcons(int nargs, char *args[])
{
    int count;
    // printf("nargs]: %d\n ",nargs);
    if(nargs==1)
    {
        count=2000;
    }
    else
    {
        count=atoi(args[1]);
    }

    if(!isdigit(count))
    {
        printf("Not a number\n");
        exit(1);
    }

    resume(create(producer,1024,20, "producer",1,count));
    resume(create(consumer,1024,20,"consumer",1,count));


    return 0;
}

