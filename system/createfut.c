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

    int v=10;

    f2.data=&v;
    // printf("Set the vlue during create :%d\n", *(int*)f2.data);
    
    

    // //point the future pointer to the structure
    // p=&s;


    // initialize value in the memory data is pointing to
    // p->data=1;

    

    //return the address of the future 

    return &f2;



     
}