#include <xinu.h>
#include <stdio.h>
#include <future.h>


// create future
future_t *future_alloc(future_mode_t mode, uint size, uint nelems)
{
    // create a structure of type future_t
    struct future_t s,*p;


    //point the future pointer to the structure
    p=&s;

    // set  the mode
    p->mode=FUTURE_EXCLUSIVE;

    //set state
    p->state=FUTURE_EMPTY;

    // set size field
    p->size=size;

    // allocate size for the data
    p->data=getmem(size);

    

    //return the address of the future 

    return p;



     
}