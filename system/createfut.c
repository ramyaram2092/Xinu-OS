#include <xinu.h>
#include <stdio.h>
#include <future.h>


// create future
future_t *future_alloc(future_mode_t mode, uint size, uint nelems)
{

    // set  the mode
    f2.mode=FUTURE_EXCLUSIVE;

    //set state
    f2.state=FUTURE_EMPTY;

    // set size field
    f2.size=size;

    // allocate size for the data
    f2.data=(void *)getmem(size);

    return &f2;



     
}