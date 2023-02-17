#include<xinu.h>
#include<prodcons_bb.h>

void produce_bb(int count, char s[])
{
    for (int i=0;i<count;i++)
    {
        wait(lock);
        //write the value
        arr_q[head]=i;

        head++;

        // if head ptr has reached the end of queue
        if(head==5)
        {
            head=0;
        }

        // if the queue is full
        if (head==tail)
        {
            head-=1;
            //do nothing    
        }
       
        signal(lock);

    }
    total+=1;

}