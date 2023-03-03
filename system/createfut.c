#include <xinu.h>
#include <stdio.h>
#include <future.h>


// create future
future_t *future_alloc(future_mode_t mode, uint size, uint nelems)
{
    // create a structure of type future_t
    struct future_t s,*p;
  
    // set  the mode
    s.mode=FUTURE_EXCLUSIVE;

    //set state
    s.state=FUTURE_EMPTY;

    // set size field
    s.size=size;

    // allocate size for the data
    s.data=(void *)getmem(size);

    *s.data=10;
    

    //point the future pointer to the structure
    p=&s;


    // initialize value in the memory data is pointing to
    // p->data=1;

    

    //return the address of the future 

    return p;



     
}