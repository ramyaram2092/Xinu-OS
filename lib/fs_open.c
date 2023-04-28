
#include <xinu.h>
#include <fs.h>

extern fsystem_t *fsd;
extern filetable_t oft[NUM_FD];

/*
 * fs_open - Return SYSERR if the file is already open or does not exist
 *     otherwise, add a record to the oft in the first current FSTATE_CLOSED
 *     slot corresponding to the opened file and copy the inode from the block
 *     device to the oft record and return the index into the oft table for the
 *     newly opened file.
 */
int fs_open(char *filename, int flags)
{

  int inode_blk = 0, inode_id=0, de=0;
  int i = 0, flag = 0;

  for (i = 0; i < DIR_SIZE; i++)
  {
    if (strcmp(fsd->root_dir.entry[i].name, filename) == 0)
    {
      inode_blk = fsd->root_dir.entry[i].inode_block;
      flag = 1;
      de=i;
    }
  }

  /* 1. Return SYSERR if file does not exists*/

  if (i == DIR_SIZE && flag == 0)
  {
    return SYSERR;
  }

  /*2. Return SYSERR if file is already open*/

    void *buffer = getmem(sizeof(inode_t));
    bs_read(inode_blk,0,buffer,sizeof(inode_t));// read the inode from the device
    inode_t* ind=(inode_t *)buffer;
    inode_id=ind->id; // get the inode id


    for(i=0;i<NUM_FD;i++)
    {
      if(oft[i].in.id==inode_id && oft[i].state==FSTATE_OPEN)
      {
        return SYSERR;
      }
    }

  /* 3. If file exists and not opened add an entry into oft*/
  flag=0;

  for(i=0;i<NUM_FD;i++)
  {
    if(oft[i].state==FSTATE_CLOSED)
    {
      oft[i].de=de;
      // oft[i].in.id=ind->id;
      // oft[i].in.size=ind->size;
      // memcpy(oft[i].in.blocks,ind->blocks,INODE_BLOCKS*sizeof(int));
      memcpy(oft[i].in, buffer,sizeof(inode_t));
      oft[i].flag=flags;
      oft[i].state=FSTATE_OPEN;
      oft[i].fileptr=0;
      flag=1;
      return i;
    }
  }

  if(i==NUM_FD && flag==0)
  {
    return SYSERR;
  }

  return OK;
}