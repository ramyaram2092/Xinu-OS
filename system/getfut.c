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
    int *p = (int *)(f->data);      // make an integer pointer point to the future memory

    if (f->state == FUTURE_READY)
    {\
        *p = *((int *)(f->data));   // read the data in future
        f->state = FUTURE_EMPTY;    // set the future state to empty
        // resume(f->pid);             // resume the process waiting on the future  
    }
    else
    {
        f->pid=currpid;             // set the current process as the process waiting on future
        f->state = FUTURE_WAITING;  // set the future state to FUTURE_WAITING
        suspend(currpid);           //suspend the current process
        return SYSERR;
    }

    return OK;
}