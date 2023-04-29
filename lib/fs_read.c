#include <xinu.h>
#include <fs.h>

extern fsystem_t *fsd;
extern filetable_t oft[NUM_FD];

/*
 * Copy the data from the block device into the 'buff' argument
 *    Use the fileptr field of the oft to track the location of the next read/write
 *    operation.
 *    - Determine the current block and offset from the fileptr
 *    - Copy bytes into the 'buff' until you have exhausted the block or copied 'len' bytes
 *    - Repeat until 'len' bytes are copied
 *    - Update the fileptr field
 *    - Return the number of bytes read
 */
int fs_read(int fd, char *buff, int len)
{
  // get the inode
  inode_t inode = oft[fd].in;

  // file ptr
  int fptr=oft[fd].fileptr;

  // local buffer  for inode
  // void *ibuffer = getmem(sizeof(inode_t));

  // no of blocks
  // int maxblck = inode.size / 512;


  //no of bytes read
  int rbytes=0;
  int size=len;
  int i = fptr/512; // block offset
  int readsize=0;
  


  while (size > 0 && i<INODE_BLOCKS)
  {
    int offset=fptr%512; // offset within the block
    if(512-offset>size)
    {
      readsize=size;
    }
    else
    {
      readsize=512-offset;
    }
    // read the data from the block device into buff
    int didx = inode.blocks[i];
    bs_read(didx, offset, buff, readsize);

    // increment the buff pointer
    buff += readSize;

    rbytes+=readSize;

   // update the filepointer
    oft[fd].fileptr+=readsize;

    // update the size
    size = size - readsize;

    i++;
  }

  return rbytes;
}