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

  printf("\n TEST CASE BEGIN \n ");
  printf("File at entry %d needs to be written with %d data",fd, len);

  filetable_t file = oft[fd];

  // inode details
  inode_t inodeb = file.in;

  // no of bytes written
  int bwrite = 0;

  // read the inode from block device;
  void *buffer = getmem(sizeof(inode_t));
  bs_read(inodeb.id, 0, buffer, sizeof(inode_t));

  // no of blocks needed
  int nblocks = len / MDEV_BLOCK_SIZE;

  // Outer loop : Perform the following operation for nblock  times
  while(len>0)
  {
    // 1. Find a free block
    int freeb = 0; // free block index

    while (freeb < fsd->freemasksz)
    {
      if (fs_getmaskbit(freeb) == 0)
      {
        printf("\n YOHOO FOUND A FREE BLOCK at %d\n",freeb);
        break;
      }
      freeb++;
    }
    // 2. Return no of bytes written so far if  no more free  blocks is available
    if (freeb == fsd->freemasksz)
    {
      return bwrite;
    }

    // 3. if found a free block update the inode of the file
    int flag=0, j=0;
    for(j=0;j<INODE_BLOCKS;j++)
    {
      if(inodeb.blocks[j]!=0)
      {
        inodeb.blocks[j]=freeb;
        flag=1;
      }
    }
    // if the allocation of the inode's data block exceeds
    if(j==INODE_BLOCKS && flag==0)
    {
      return bwrite;
    }

    int l=0;
    if(len>MDEV_BLOCK_SIZE)
    {
      l=MDEV_BLOCK_SIZE;
    }
    else
    {
      l=len;
    }
    printf("\n  FILE SIZE In INODE BEFORE UPDATE: %d\n",inodeb.size);

    inodeb.size+=l;

    printf("\n Gonna write %d bytes of data\n",l);
    printf("\n FILE SIZE UPDATED IN INODE : %d BYTES\n", inodeb.size);


    // mark the block as used
    fs_setmaskbit(freeb);

    // 4. Now write the file to the disk
    void * databuf= getmem(l);
    memcpy(databuf,buff,l);

    printf("\nSIZE OF DATABUFF before writing to the disk :%d\n", (strlen((char*)databuf)));

    bs_write(freeb,0,databuf,sizeof(databuf));

        memset(databuf,0,sizeof(databuf));
        bs_read(freeb,0,databuf,sizeof(databuf));
        printf("\nSIZE OF DATABUFF after writing to the disk :%d\n", (strlen((char*)databuf)));



    //5. Write the inode  back to the disk
    memset(buffer,0,sizeof(inode_t));
    memcpy(buffer,&inodeb,sizeof(inode_t));
    printf("\n  FILE SIZE In BUFFER before writing to the disk : %d\n",((inode_t* )buffer)->size);
    bs_write(inodeb.id,0,buffer,sizeof(inode_t));



    //6. Update the file table
    memset(buffer,0,sizeof(inode_t));
    bs_read(inodeb.id, 0, buffer, sizeof(inode_t)); 
    inode_t *in=(inode_t*)buffer;
    printf("\n  FILE SIZE In INODE after Read from disk : %d\n",((inode_t* )buffer)->size);
    oft[fd].in=*in;
    printf("\n UPDATED FILE SIZE In INODE : %d\n",oft[fd].in.size);


    // 6. track the data written so far
    len=len>MDEV_BLOCK_SIZE? len-MDEV_BLOCK_SIZE:0;
    bwrite+=l;
    oft[fd].fileptr+=l;

  }

  return bwrite;
}