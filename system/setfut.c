#include <xinu.h>
#include <stdio.h>
#include <future.h>

// setFuture
/*
case 1: if future is empty 
        -> set state as FUTURE_READY
        -> set the new value
        -> return ok
case 2: Future is not empty and state is FUTURE_READY
        -> return syserror
*/
syscall future_set(future_t *f, void *in)
{
   struct	procent *prptr;		/* Ptr to process' table entry	*/
   printf(" In setfut new value: %d  old value : %d\n", *(int*)in, f->data);
   if(f->state==FUTURE_EMPTY )
   {
        f->state=FUTURE_READY;
        f->data=*(int*)in; // write the value in the future
        printf("Updated future data : %d\n",f->data);
        return OK;
   }
   else
   {
        prptr->prstate = PR_WAIT;	/* Set process state to waiting	*/
        resched();			        /*   and reschedule	*/
        return SYSERR;
   }
   
}