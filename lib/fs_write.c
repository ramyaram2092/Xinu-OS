#include <xinu.h>
#include <fs.h>

extern fsystem_t *fsd;
extern filetable_t oft[NUM_FD];

/*
 * Copy 'len' bytes from 'buff' into the blocks associated with the file 'fd'
 *   - Until 'len' bytes are copied...
 *   - Check if a new block is needed (find free block and add to the file's blocks if necessary)
 *   - Write bytes from the 'buff' into the block starting at the fileptr
 *   - Write 'len' bytes or fill the block, whichever is less
 *   - Repeat until write is complete
 *   - Update inode state to reflect changes
 *   - Return the number of bytes written
 */
int fs_write(int fd, char *buff, int len)
{

  filetable_t file = oft[fd];

  // inode details
  inode_t inodeb = file.in;

  // no of bytes written
  int bwrite = 0;

  // read the inode from block device;
  void *buffer = getmem(sizeof(inode_t));

  int l = 0;
  int freeb = 0; // free block index

  int nblocks = inodeb.size / 512;
  int sizeonlbck = inodeb.size % 512;
  int writeoffset = 0;
  // Outer loop :
  while (len > 0)
  {
    int flag = 0, j = 0;

    for (j = nblocks; j < INODE_BLOCKS; j++)
    {
      // 1. if the curr data block is unused
      if (inodeb.blocks[j] == 513)
      {
        // 1.a find the next free block
        while (freeb < fsd->freemasksz)
        {
          if (fs_getmaskbit(freeb) == 0)
          {
            break;
          }
          freeb++;
        }
        // 1.b Return no of bytes written so far if  no more free  blocks is available
        if (freeb == fsd->freemasksz)
        {
          return bwrite;
        }

        // 1.c if the allocation of the inode's data block exceeds
        if (j == INODE_BLOCKS && flag == 0)
        {
          // printf("\n FAILING AT 3.a \n");
          return bwrite;
        }

        // 1.d  mark the block as used
        fs_setmaskbit(freeb);

        // 1.e update the local inode

        inodeb.blocks[j] = freeb;

        if (len > 512)
        {
          l = 512;
        }
        else
        {
          l = len;
        }

        writeoffset = 0;
      }

      // 2. if the curr block has data less than 512 bytes. Fill it up
      else if (inodeb.blocks[j] != 513)
      {

        int size = sizeonlbck;
        if (len < 512 - size)
        {
          l = len;
        }
        else
        {
          l = 512 - size;
        }

        freeb = inodeb.blocks[j];

        writeoffset = sizeonlbck;
      }

      len = len - l;

      // 3. write the file to disk device
      void *databuf = getmem(l);
      memcpy(databuf, buff, l);
      bs_write(freeb, writeoffset, databuf, l);
      buff += l;

      // 4. update the fileptr in oft table
      oft[fd].fileptr += l;

      // 5. update  local inode
      inodeb.size += l;

      //  Write the local inode  back to the disk
      memset(buffer, 0, sizeof(inode_t));
      memcpy(buffer, &inodeb, sizeof(inode_t));
      bs_write(inodeb.id, 0, buffer, sizeof(inode_t));

      // Update the inode in  oft file table
      memset(buffer, 0, sizeof(inode_t));
      bs_read(inodeb.id, 0, buffer, sizeof(inode_t));
      inode_t *in = (inode_t *)buffer;
      oft[fd].in = *in;

      // 5. update the bytes to return
      bwrite += l;

      if (len == 0)
        break;
    }
  }
  return bwrite;
}