#include <xinu.h>
#include <stdio.h>
#include <shprototypes.h>
#include <processterminator.h>

sid32 completecmd;

shellcmd xsh_run(int nargs, char *args[])
{   

    completecmd=semcreate(0);

    // print the list of known commands 
    if(nargs==1 || strncmp(args[1],"list",4)==0)
    {
        printf("hello\n");
        printf("list\n");
        printf("prodcons\n");
    }
    // execute hello command
    else if(strncmp(args[1],"hello",4)==0)
    {
        resume (create((void *) xsh_hello, 4096, 20, "hello", 2, nargs - 1, &(args[1])));
    }

    //execute prodcons command
    else if(strncmp(args[1],"prodcons",8)==0)
    {
        resume (create((void *) xsh_prodcons, 4096, 20, "prodcons", 2, nargs - 1, &(args[1])));

    }
    
    wait(completecmd);


    // printf("Semaphore value in run  :%d\n", semcount(completecmd));
    
    return 0;
}