#include <xinu.h>
#include <stdio.h>
#include <future.h>
#include <prodcons_fut.h>

void consumer_fut(future_t *f)
{
  void *p = &value;
  int a = future_get(f, p);

  if (a == 1)
  {
    printf("Consumed : %d\n", value);
  }
  else
  {
    printf("suture_get failed\n");
  }
}