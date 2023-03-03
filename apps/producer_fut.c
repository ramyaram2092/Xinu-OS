#include<xinu.h>
#include<stdio.h>
#include<future.h>

void producer(int val,future_t* f)
{
    // set the value to future 
    future_set(f,f->data);
}