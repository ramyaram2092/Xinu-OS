#include<xinu.h>
#include<stdio.h>
#include<future.h>


void consumer(future_t * f)
{
  int value;
  // return the value that the future hols
  future_get(f,(void*)&value);
  printf("%d\n",value);
}