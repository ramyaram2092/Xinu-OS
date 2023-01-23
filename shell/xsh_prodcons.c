#include<xinu.h>
#include<stdio.h>
#include<prodcons.h>


shellcmd xsh_prodcons(int nargs, char *args[])
{
    printf("Hello %s, Welcome to the world of Xinu!!",args[1]);
    return 0;
}

void producer(int count)
{

}

void consumer(int count)
{
    
}