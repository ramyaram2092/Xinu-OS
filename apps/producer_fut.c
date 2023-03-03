#include<xinu.h>
#include<stdio.h>
#include<future.h>
#include<prodcons_fut.h>


void producer_fut(int val,future_t* f)
{
    // set the value to future 
    future_set(f,f->data);
}