#include<xinu.h>
#include<prodcons_bb.h>

void produce_bb(int count, int pid)
{
    char s[15];
    sprintf(s,"producer_%d",pid);
    for (int k=0;k<count;)
    {
        // take hold of the semaphore for write operation
        wait(lock);

        //check if the queue is full , write otehrwise
        if(tail!=(head+1)%5)
        {
            head=(head+1)%5;
            arr_q[head]=k;
            printf("name : %s, write : %d\n",s,arr_q[head]);
            k++;
        }
        else
        {
            // printf("Unable to write by %s as the queue is full, head : %d, tail:%d\n ",s,head,tail);
        }

        // release the semaphore 
        signal(lock);

    }
    // take hold of the complete semaphore to update the process completion 
    wait(complete);
    total+=1;
    // release the semaphore
    signal(complete); 
}