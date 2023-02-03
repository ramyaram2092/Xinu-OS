#include <xinu.h>
#include <prodcons.h>


void producer(sid32 prod,sid32 cons,int count) {
  // TODO: implement the following:
  // - Iterates from 0 to count (count including)
  //   - setting the value of the global variable 'n' each time
  //   - print produced value (new value of 'n'), e.g.: "produced : 8"
 for (int i=0;i<=count;i++)
 {
   wait(cons);
    n=i;
    printf("produced : %d\n",n);
    signal(prod);
 }

}
