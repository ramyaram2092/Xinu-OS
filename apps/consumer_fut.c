#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <prodcons_fut.h>


/** The consumer_fut function  reads the future value*/
void consumer_fut(future_t *f)
{
  void *p = &value;
  int res = future_get(f, p);

  if (res == 1)
  {
    wait(print);
    printf("Consumed %d\n", value);
    signal(print);
  }
  else
  {
    wait(print);
    printf("future_get failed\n");
    signal(print);
  }

  flag+=1;
}