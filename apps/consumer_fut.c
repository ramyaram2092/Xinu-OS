#include<xinu.h>
#include<stdio.h>
#include<future.h>
#include<prodcons_fut.h>


void consumer_fut(future_t * f)
{
  printf("\n IN CONSUMER PROCESS\n");
  void* p=&value;
  
  printf("Address of value before calling futget : %d\n",p);

  // return the value that the future holds
  future_get(f,p);
  printf("Consuming : %d\n",value);
}