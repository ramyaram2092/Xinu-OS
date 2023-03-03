#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <prodcons_fut.h>



void producer_fut(int val, future_t *f)
{
    int v = val;
    int res=future_set(f, &v);
    if ( res== 1)
    {
        printf("Producing :%d\n", *(int *)(f->data));
    }
    else
    {
        printf("future_set failed\n");
    }

    flag+=1;
}