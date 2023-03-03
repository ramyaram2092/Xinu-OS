#include<xinu.h>
#include<stdio.h>
#include<future.h>
#include<prodcons_fut.h>


void producer_fut(int val,future_t* f)
{
    int v=val;
    // set the value to future 
    //  printf("Before setting value:%d\n",*(int *) f->data);
    future_set(f,&v);
    
    printf("Future address :%d\n", f->data);

    printf("Produced :%d\n", *(int*)(f->data));
}