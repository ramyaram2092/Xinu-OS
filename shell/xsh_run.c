#include <xinu.h>
#include <stdio.h>
#include <shprototypes.h>

// shellcmd xsh_prodcons(int32, char *[]);
// shellcmd xsh_hello	(int32, char *[]);



shellcmd xsh_run(int nargs, char *args[])
{   
    // print the list of known commands 
    if(nargs==1 || strncmp(args[1],"list",4)==0)
    {
        printf("hello\n");
        printf("prodcons\n");
    }
    // execute hello command
    else if(strncmp(args[1],"hello")==0)
    {
        resume (create((void *) xsh_hello, 4096, 20, "hello", 2, nargs - 1, &(args[1])));

    }

    //execute prodcons command
    else if(strncmp(args[1],"prodcons")==0)
    {
        resume (create((void *) xsh_prodcons, 4096, 20, "prodcons", 2, nargs - 1, &(args[1])));

    }
    
    return 0;
}