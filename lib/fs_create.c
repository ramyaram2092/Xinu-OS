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

  int freeb = 0;                 // free block index
  directory_t r = fsd->root_dir; // root directory reference

  //  // print the bit mask
  //  fs_print_mask();

  // 1.  Find an available block on the block store
  while (freeb < fsd->freemasksz)
  {
    if (fs_getmaskbit(freeb) == 0)
    {
      break;
    }
    freeb++;
  }

  printf("\n FIRST AVILABLE FREE BLOCK : %d", freeb);

  // 2. Return SYSERR if not enough space is available
  if (i == fsd->freemasksz)
  {
    return SYSERR;
  }

  // 3. Return SYSERR if filename already exists

  int i = 0;
  while (i < DIR_SIZE)
  {
    if (strcmp(filename, r.entry[i].name) == 0)
    {
      return SYSERR;
    }
    i++;
  }

  // 4. create inode_t for the new file

  struct inode_t in;
  in.id = 1;

  // 5. Write the inode and free bitmask back to the block device

  fs_setmaskbit(freeb);
  int i = 0;
  for (int i = 0; i < DIR_SIZE; i++)
  {
    if(r.entry[i].inode_bloc!=0)
    {
      r.entry[i].inode_block=freeb;
      int j=0;
      while(j<FILENAME_LEN)
      {
        name[j]=filename;
        j++;
        filename++;
      }
    }
  }

  return OK;
}