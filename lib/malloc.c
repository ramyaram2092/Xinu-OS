#include <xinu.h>
#include <heap.h>

extern heap_t heaptab[];

typedef struct heapblock{
  struct heapblock* next;
  uint32 size;
}hb;


hb heaphead; //head node



void initheap(char* startaddr, uint32 size) {
  /* This function is called when the heap is constructed */
  /*   Use as needed to setup the free list               */
  
  intmask mask;
  mask= disable();
  if(size==0)
  {
    restore(mask);
    return (char *) SYSERR;
  }

  size=(uint32) roundmb(size);
  heaphead.next=(hb*)startaddr;
  heaphead.size=size;
  hb *curr= heaphead.next;
  curr->size=size;
  curr->next=NULL;
  heaptab[currpid].freelist=(char*)heaphead.next;
  restore(mask);
  return;
}

void* malloc(uint32 size) {
  /* Implement memory allocation within the process heap here       */
  /*   Your implementation MUST NOT use getmem                      */
  /*   Your implementation SHOULD use explicit in-memory free lists */
  
  hb *prev, *curr,* leftover;
  intmask mask;
  mask=disable();
  if(size==0 || heaptab[currpid].freelist==NULL || size>heaphead.size)
  {
    restore (mask);
    return (void *) SYSERR;
  }
  size=(uint32) roundmb(size);
  prev=&heaphead;
  curr=(struct heapblock *)heaphead.next;
 
  /* Search the Heap*/
  while(curr!=NULL) 
  {
    if(curr->size==size) // block requested is the entire heap size
    {
      prev->next=curr->next;
      heaphead.size-=size;
      restore(mask);
      return (char*)(curr);
    }
    else if (curr->size>size) // Split the big block
    {
      leftover=(struct hb*)((uint32) curr +size);
      prev->next=leftover;
      leftover->size=(curr->size)-size;
      leftover->next=curr->next;
      heaphead.size-=size;
      restore(mask);
      return (char *)(curr);
    }

    else // move to next available block
    {
      prev=curr;
      curr=curr->next;
    }

  }
  restore(mask);
  return (char*)SYSERR;
}

void free(char* blck, uint32 size) {
  /* Implement memory free within process heap here */
  /*   Your implementation MUST implement coalesing */
  intmask mask;
  struct heapblock *nex,*prev, *block;
  uint32 top;

  mask=disable();
  if(size==0)
  {
    restore(mask);
    return SYSERR;
  }

  size=(uint32)roundmb(size);
  block=(struct hb*)blck;

  prev=&heaphead;
  nex=heaphead.next;
 

  while((nex!=NULL) &&(nex<block))
  {
    prev=nex;
    nex=nex->next;
  }

  /* Computing the top of previous block*/
  if(prev==&heaphead)
  {
    top=(uint32)NULL;
  }
  else
  {
    top=(uint32)prev+prev->size;

  }

 /* Ensure new block doesnt overlap previous or next blocks*/

 if((prev!=&heaphead)&& (uint32)block<top || (nex!=NULL) &&(uint32)block+size >(uint32)nex)
 {
  restore(mask);
  return SYSERR;
 }

 heaphead.size+=size;

 /* Either coalesce with previous block or add to free list*/


 if(top==(uint) block) // coalesce with previous block
 {
   prev->size+=size;
   block=prev;
 }
 else // link into list as new node
 {
  block->next=nex;
  block->size=size;
  prev->next=block;
 }

 // coalesce with next block if adjacent

 if(((uint32) block + block->size)==(uint32)nex)
 {
  block->size+=nex->size;
  block->next=nex->next;
 }

restore(mask);

  }


  
 