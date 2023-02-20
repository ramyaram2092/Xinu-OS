#include<xinu.h>
#include<prodcons_bb.h>

void consume_bb(int count, char s[])
{
    // printf("\n In consumer process  %s\n", s);
    for(int k=0;k<count;k++)
    {
        wait(lock);

        if(head!=tail)
        {
            printf("name : %s read : %d\n",s,arr_q[tail]);
            tail++;     
        }
        // if tail ptr has reached the end of queue
        if(tail==5)
        {
            tail=0;
        }

        signal(lock);
       

    }
    total+=1;

}