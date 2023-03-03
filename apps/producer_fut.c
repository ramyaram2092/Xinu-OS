#include<xinu.h>
#include<stdio.h>
#include<future.h>
#include<prodcons_fut.h>


void producer_fut(int val,future_t* f)
{
    int v=val;
    // set the value to future 
     printf("Before setting value:%d\n",*(int *) f->data);
    future_set(f,&v);
    printf("After setting value:%d\n", f->data);
}