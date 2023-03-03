#include <xinu.h>
#include <stdio.h>
#include <future.h>

/*create future */
future_t *future_alloc(future_mode_t mode, uint size, uint nelems)
{
    intmask mask;
    mask = disable();
    // set  the mode
    f2.mode = mode;

    // set state
    f2.state = FUTURE_EMPTY;

    // set size field
    f2.size = size;

    // allocate size for the data
    f2.data = (void *)getmem(size);

    restore(mask);
    return &f2;
}

/* free future*/
syscall future_free(future_t *f)
{
    intmask mask;
    mask = disable();
    freemem((char *)(f->data), sizeof(uint));
    kill(f->pid);
    restore(mask);
    return OK;
}

/* set the future value*/

syscall future_set(future_t *f, void *in)
{
    intmask mask;
    mask = disable();
    int *p = (int *)(f->data); // make an integer pointer point to the future memory

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
    restore(mask);
    return OK;
}

/* get the future value*/
syscall future_get(future_t *f, void *out)
{
    intmask mask;
    mask = disable();
    int *p = (int *)(out); // make an integer pointer point to the out memory

    if (f->state == FUTURE_EMPTY)
    {
        f->pid = currpid;          // set the current process as the process waiting on future
        f->state = FUTURE_WAITING; // set the future state to FUTURE_WAITING
        suspend(currpid);          // suspend the current process
    }

    if (f->state == FUTURE_READY)
    {
        *p = *((int *)(f->data)); // read the data from future into the out

        f->state = FUTURE_EMPTY; // set the future state to empty
        return OK;
    }
    else if (f->state == FUTURE_WAITING)
    {
        return SYSERR;
    }
    restore(mask);
    return OK;
}