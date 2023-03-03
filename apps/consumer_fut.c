#include<xinu.h>
#include<stdio.h>
#include<future.h>
#include<prodcons_fut.h>


void consumer_fut(future_t * f)
{
  int value;
  // return the value that the future holds
  future_get(f,(void*)&value);
  printf("%d\n",value);
}