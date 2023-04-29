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

   oft[fd].fileptr=0;

  // local buffer  for inode
  void *ibuffer = getmem(sizeof(inode_t));

  // no of blocks
  int maxblck = inodeb.size / 512;

  //no of bytes read
  int rbytes=0;

  if (len > 512)
  {
    size = 512;
  }
  else
  {
    size = len;
  }

  int i = 0;
  while (size > 0 && i <= maxblck)
  {
    offset=oft[fd].fileptr;
    // read the data from the block device into buff
    int didx = inode.blocks[i];
    bs_read(didx, offset, buff, size);
    // increment the buff pointer
    buff += size;

    rbytes+=size;

    // update the size
    size = size - len;

    // update the filepointer
    oft[fd].filept+=size;

    i++;
  }

  return rbytes;
}