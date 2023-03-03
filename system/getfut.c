#include <xinu.h>
#include <stdio.h>
#include <future.h>


/**
case 1: if the future state is FUTURE_READY
        -> read value 
        -> change status to FUTURE_EMPTY
case 2:  if the future state is FUTURE_EMPTY
        -> return SYSERR
 */
syscall future_get(future_t *f, void *out)
{
    struct	procent *prptr;		/* Ptr to process' table entry	*/

    if(f->state==FUTURE_READY )
    {
        printf("Address of future data : %d\n",f->data);
        printf("Value of future data :%d\n", *(int*)(f->data));

        printf("Address of value after calling futget: %d\n",out);

        int *p=(int*)out;

        *p=*((int *)(f->data));
        printf("Value in out: %d\n",*p);
        f->state=FUTURE_EMPTY;
    }
    else 
    {
        // block the process and put the process in waiting state
        prptr->prstate = PR_WAIT;	/* Set process state to waiting	*/
        resched();			        /*   and reschedule	*/
        f->state=FUTURE_WAITING;   
        return SYSERR;
    }

    return OK;

}