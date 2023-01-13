#include<xinu.h>
#include<stdio.h>


shellcmd xsh_hello(int nargs, char *args[])
{
    printf("\n 	Hello %s, Welcome to the world of Xinu!!",args[0]);
    return 0;
}