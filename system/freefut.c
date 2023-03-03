#include <xinu.h>
#include <stdio.h>
#include <future.h>


syscall future_free(future_t *f)
{
     freemem((char *)(f->data),sizeof(uint));
     kill(f->pid);


}