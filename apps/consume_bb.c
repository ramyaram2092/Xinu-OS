#include<xinu.h>
#include<prodcons_bb.h>

void consume_bb(int count, int pid)
{
    char s[15];
    sprintf(s,"consumer_%d",pid);
    for(int k=0;k<count;)
    {
        // take hold of the semaphore
        wait(lock);

        // if the queue is not empty then read
        if(head!=tail)
        {
            tail=(tail+1)%5; 
            printf("name : %s, read : %d\n",s,arr_q[tail]);
            k++;
        }
        else
        {
            // printf("Nothing to read by %s head : %d, tail : %d\n ",s, head, tail);
        }
        // free the semaphore
        signal(lock);
    }
    // take hold of the semaphore complete to accesss the 'total' varaiable
    wait(complete);
    total+=1;
    // release the total semaphore
    signal(complete);

}