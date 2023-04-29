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
  bs_read(inodeb.id, 0, buffer, sizeof(inode_t));

  // Outer loop :
  while (len > 0)
  {
    int flag = 0, j = 0;

    for (j = 0; j < INODE_BLOCKS; j++)
    {
      // 1. if the curr data block is unused
      if( inode.blocks[j]==513)
      {
        // 1.a find the next free block
        int freeb = 0; // free block index
        while (freeb < fsd->freemasksz)
        {
          if (fs_getmaskbit(freeb) == 0)
          {
            // printf("\n YOHOO FOUND A FREE BLOCK at %d\n",freeb);
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
      }
      int l=0;

      // 2. if the curr block has data less than 512 bytes. Fill it up
      else if (inodeb.blocks[j]!=513 )
      {
          void *ip = getmem(512);
          bs_read(inodeb.blocks[j], 0, ip, 512);

          int size = sizeof(ip);
          if(size<512 && size>0)
          {
              l = 512 - size;
          }
          else
          {
              l= len
          }
      }
     
     len=len-l;


     // 3. write the file to disk device
      void *databuf = getmem(l + 1);
      memcpy(databuf, buff, l);
      bs_write(freeb, oft[fd].fileptr, databuf, l);


      // 4. update the fileptr in oft table
      oft[fd].fileptr += l;

      // update the bytes to return
      bwrite += l;

      // update  local inode
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
    }
  }

}