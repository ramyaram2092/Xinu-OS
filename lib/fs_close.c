
#include <xinu.h>
#include <fs.h>

extern fsystem_t* fsd;
extern filetable_t oft[NUM_FD];


/*
 * fs_close - Return SYSERR if the file is already closed
 *     otherwise, write the file's inode back to the block
 *     device and set the entry in the oft to FSTATE_CLOSED
 */
syscall fs_close(int fd) {

  int i=0,flag=0;
  for(i=0;i<NUM_FD;i++)
  {
    if(oft[i].in.id==fd && oft[i].state==FSTATE_CLOSED)
    {
      return SYSERR;
    }
    else if(oft[i].in.id==fd)
    {
      void* buffer= &oft[i].in;
      bs_write(fd,0,buffer,sizeof(buffer));
      oft[i].state=FSTATE_CLOSED;
      oft[i].fileptr=0;
      flag=1;
      break;
    }
  }

  if(i==NUM_FS && flag==0)
  {
    return SYSERR;
  }
  
  
  return OK;
}