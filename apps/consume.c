#include <xinu.h>
#include <prodcons.h>


void consumer(int count, sid32  prod, sid32 cons) {
  // TODO: implement the following:
  // - Iterates from 0 to count (count including)
  //   - reading the value of the global variable 'n' each time
  //   - print consumed value (the value of 'n'), e.g. "consumed : 8"

  for(int i=0;i<=count;i++)
  {
    wait(prod);
    printf("consumed : %d\n",n);
    signal(cons);
  }
  
}
