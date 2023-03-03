#include<xinu.h>
#include<stdio.h>
#include<future.h>
#include<prodcons_fut.h>


void producer_fut(int val,future_t* f)
{
    int v=val;
    // set the value to future 
    future_set(f,&v);
    printf("Producing:%d\n", f->data);
}