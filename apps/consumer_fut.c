#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <prodcons_fut.h>

void consumer_fut(future_t *f)
{
  void *p = &value;
  int res = future_get(f, p);

  if (res == 1)
  {
    printf("Consumed : %d\n", value);
  }
  else
  {
    printf("future_get failed\n");
  }

  flag+=1;
}