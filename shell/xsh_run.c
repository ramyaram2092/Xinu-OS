#include<xinu.h>
#include<stdio.h>


shellcmd xsh_hello(int nargs, char *args[])
{
    printf("Hello %s, Welcome to the world of Xinu!!",args[1]);
    return 0;
}