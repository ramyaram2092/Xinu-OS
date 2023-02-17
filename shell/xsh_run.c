#include <xinu.h>
#include <stdio.h>
#include <shprototypes.h>
#include <processterminator.h>

sid32 completecmd;

void helper(char *pname, int nargs, char *args[])
{
    if (strncmp(pname, "hello", 4) == 0)
    {
        resume(create((void *)xsh_hello, 4096, 20, "hello", 2, nargs - 1, &(args[1])));
    }
    else if (strncmp(pname, "prodcons", 8) == 0)
    {
        resume(create((void *)xsh_prodcons, 4096, 20, "prodcons", 2, nargs - 1, &(args[1])));
    }
     else if (strncmp(pname, "prodcons_bb", 11) == 0)
    {
        resume(create((void *)xsh_prodcons_bb, 4096, 20, "prodcons_bb", 2, nargs - 1, &(args[1])));
    }
}

shellcmd xsh_run(int nargs, char *args[])
{

    completecmd = semcreate(0);

    // print the list of known commands
    if (nargs == 1 || strncmp(args[1], "list", 4) == 0)
    {
        printf("hello\n");
        printf("list\n");
        printf("prodcons\n");
        printf("prodcons_bb\n");

    }

    helper(args[1], nargs, args);
    wait(completecmd);
    semdelete(completecmd);

    // printf("Semaphore value in run  :%d\n", semcount(completecmd));

    return 0;
}