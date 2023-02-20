#include<xinu.h>
#include<prodcons_bb.h>

void consume_bb(int count, char s[])
{
    // printf("\n In consumer process  %s\n", s);
    for(int k=0;k<count;)
    {
        wait(lock);

        if(head!=tail)
        {
            tail=(tail+1)%5; 
            printf("name : %s read : %d\n",s,arr_q[tail]);
            k++;
        }
        else
        {
            printf("Nothing to read by %s head : %d, tail : %d\n ",s, head, tail);
        }
       

        signal(lock);
       

    }
    wait(complete);
    total+=1;
    signal(complete);

}