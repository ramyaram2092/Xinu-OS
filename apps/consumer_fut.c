#include<xinu.h>
#include<stdio.h>
#include<future.h>
#include<prodcons_fut.h>


void consumer_fut(future_t * f)
{
  // printf("\n IN CONSUMER PROCESS\n");
  //    printf("Address of future data : %d\n",f->data);
  //       printf("Value of future data :%d\n", *(int*)(f->data));
  void* p=&value;

  // printf("Address of value before calling futget : %d\n",p);

  // return the value that the future holds
  future_get(f,p);
  printf("Consumed : %d\n",p);
}