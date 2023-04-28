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
  int freeb = 0;                 // free block index
  directory_t *r = fsd->root_dir; // root directory reference


  // 1.  Find an available block on the block store
  while (freeb < fsd->freemasksz)
  {
    if (fs_getmaskbit(freeb) == 0)
    {
      break;
    }
    freeb++;
  }

  // printf("\n FIRST AVILABLE FREE BLOCK : %d", freeb);

  // 2. Return SYSERR if not enough space is available
  if (freeb == fsd->freemasksz)
  {
    return SYSERR;
  }

  // 3. Return SYSERR if filename already exists

  int i = 0;
  while (i < DIR_SIZE)
  {
    if (strcmp(filename, r->entry[i].name) == 0)
    {
      return SYSERR;
    }
    i++;
  }

  // 4. create inode_t for the new file

  inode_t in;
  in.id = 1;
  for (int i = 0; i < DIR_SIZE; i++)
  {
    in.blocks[i]=0;
  }

  // 5. Write the inode and free bitmask back to the block device

  // mark the block as used
  fs_setmaskbit(freeb);

  // add the inode details in the directory entries
  for (int i = 0; i < DIR_SIZE; i++)
  {
    if (r->entry[i].inode_block != 0)
    {
      r->entry[i].inode_block = freeb;
      int j = 0;
      while (j < FILENAME_LEN)
      {
        r->entry[i].name[j] = filename;
        j++;
        filename++;
      }
    }
  }

 // write the inode into the block assigned for the inode 
  void *buffer = getmem(sizeof(inode_t));

  memcpy(buffer, &in, sizeof(inode_t));

  inode_t *cpy = (inode_t *)buffer;

  // printf("\n COPIED VALUE OF BUFFER INODE ID : %d", cpy->id);
  bs_write(freeb, 0, buffer, sizeof(buffer));
  restore(mask);
  return OK;
}