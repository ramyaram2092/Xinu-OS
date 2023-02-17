#include<xinu.h>
#include<prodcons_bb.h>

void consume_bb(int count, char s[])
{
    for(int i=0;i<count;i++)
    {
        wait(lock);
        printf("name : %s read:%d",s,arr_q[tail]);
        tail++;
        // if tail ptr has reached the end of queue
        if(tail==5)
        {
            tail=0;
        }
        signal(lock);
       

    }
    total+=1;

}