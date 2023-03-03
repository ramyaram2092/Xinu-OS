#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <prodcons_fut.h>

void producer_fut(int val, future_t *f)
{
    int v = val;

    if (future_set(f, &v) == 0)
    {
        printf("Produced :%d\n", *(int *)(f->data));
    }
    else
    {
        printf("future_set failed\n");
    }
}