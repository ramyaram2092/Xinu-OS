#include<xinu.h>
#include<prodcons_bb.h>

void produce_bb(int count, char s[])
{
    //    printf("\n In producer process ");

    for (int k=0;k<count;k++)
    {
        wait(lock);
        //write the value
        arr_q[head]=k;
        printf("name : %s write:%d",s,arr_q[head]);

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