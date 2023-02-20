#include<xinu.h>
#include<prodcons_bb.h>

void produce_bb(int count, char s[])
{
    //    printf("In producer process: %s\n ",s);
    
    for (int k=0;k<count;)
    {
        wait(lock);

        //check if the queue is full
        if(tail!=head)
        {
            arr_q[head]=k;
            printf(" Executing %s\n",s);
            printf("name : %s write : %d\n",s,arr_q[head]);
            head=(head+1)%5;
            k++;
        }
        else
        {
            printf("Unable to write by %s as the queue is full, head : %d, tail:%d\n ",s,head,tail);
        }

        // Implementation specific logic :if the tail is -1 move it to 0
        if(tail==-1)
        {
            printf("Moving tail from -1 to 0\n");
            tail=0;
        }

    
        signal(lock);

    }
    wait(complete);
    total+=1;
    signal(complete);  
}