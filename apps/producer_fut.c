#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <prodcons_fut.h>



void producer_fut(int val, future_t *f)
{
    int v = val;
    int res=future_set(f, &v);
    printf("Producing :%d\n", v);
    if ( res== -1)
    {
        printf("future_set failed\n");
    }

    flag+=1;
}