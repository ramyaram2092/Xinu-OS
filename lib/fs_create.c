#include <xinu.h>
#include <fs.h>

extern fsystem_t *fsd;

/*
 * fs_create - Return SYSERR if not enough space is available
 *     in the directory or the filename already exists.
 *     Otherwise:
 *        1. Find an available block on the block store
 *        2. Create an inode_t for the new file
 *        3. Update the root directory
 *        4. Write the inode and free bitmask back to the block device
 */
syscall fs_create(char *filename)
{
  intmask mask = disable();
  int freeb = 0;    // free block index

  /* 1. Find an available block on the block store*/

  while (freeb < fsd->freemasksz)
  {
    if (fs_getmaskbit(freeb) == 0)
    {
      break;
    }
    freeb++;
  }

  /* 2. Return SYSERR if not enough space is available */
  if (freeb == fsd->freemasksz)
  {
    return SYSERR;
  }

  /* 3. Return SYSERR if filename already exists */

  for (int i = 0; i < DIR_SIZE; i++)
  {
    if (strcmp(filename, fsd->root_dir.entry[i].name) == 0)
    {
      return SYSERR;
    }
  }

  /* 4. create inode_t for the new file */

  // initialize inode
  inode_t in;
  in.id = freeb;
  for (int i = 0; i < INODE_BLOCKS; i++)
  {
    in.blocks[i] = 0;
  }

  /* 5. Write the inode and free bitmask back to the block device */

  fs_setmaskbit(freeb);               // mark the block as used
  int i=0,k=0;
  for ( i = 0; i < DIR_SIZE; i++) // add the inode details in the directory entries
  {
    if (strcmp(fsd->root_dir.entry[i].name, "") == 0)
    {
      fsd->root_dir.entry[i].inode_block = freeb;
      strcpy(fsd->root_dir.entry[i].name, filename);
      k=1;
      break;
    }
  }
  if(i==DIR_SIZE && k==0)
  {
    return SYSERR;
  }
  fsd->root_dir.numentries += 1;

  /* 6.  write the inode into the block assigned for the inode */
  void *buffer = getmem(sizeof(inode_t));
  memcpy(buffer, &in, sizeof(inode_t));
  bs_write(freeb, 0, buffer, sizeof(buffer));
  restore(mask);
  return OK;
}