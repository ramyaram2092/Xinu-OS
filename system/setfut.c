#include <xinu.h>
#include <stdio.h>
#include <future.h>

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

        int *p = (int *)(f->data);        // make an integer pointer point to the future memory

        if (f->state == FUTURE_READY)
        {
                return SYSERR;
        }

        else if (f->state == FUTURE_EMPTY)
        {
                *p = *(int *)in;         // write the value in the future
                f->state = FUTURE_READY; // set state
                return OK;
        }
        else if (f->state = FUTURE_WAITING)
        {
                *p = *(int *)in;         // write the value in the future
                f->state = FUTURE_READY; // set the future state to ready
                resume(f->pid);          // resume the process waiting on the future
                return OK;
        }

        return OK;
}