#include<xinu.h>
#include<prodcons_bb.h>

void produce_bb(int count, char s[])
{
       printf("In producer process: %s\n ",s);

    for (int k=0;k<count;k++)
    {
        wait(lock);

        //check if the queue is full
        if(head!=tail)
        {
            arr_q[head]=k;
            printf("%s\n",s);
            printf("name : %s write : %d\n",s,arr_q[head]);
            head++;
        }

        // if the head reaches the end of the queue
        if(head==5)
        {
            head=0;
        }

        // Implementation specific logic :if the tail is -1 move it to 0
        if(tail==-1)
        {
            tail=0;
        }

    
        signal(lock);

    }
    total+=1;

}