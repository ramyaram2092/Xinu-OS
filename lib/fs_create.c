#include <xinu.h>
#include <fs.h>

extern fsystem_t* fsd;

/*
 * fs_create - Return SYSERR if not enough space is available
 *     in the directory or the filename already exists.
 *     Otherwise:
 *        1. Find an available block on the block store
 *        2. Create an inode_t for the new file
 *        3. Update the root directory
 *        4. Write the inode and free bitmask back to the block device
 */
syscall fs_create(char* filename) {
 
 char *itr= fsd->freemask;
 int i=0;

 // print the bit mask
 fs_print_mask();

// Find an available block on the block store
 while(i<fsd->freemasksz)
 {
   printf ("\n Curr Bit mask value : %c",itr);

   if(itr==0)
   {
      break;
   }

   i++;
   itr++;
 }

 printf("\n FIRST AVILABLE FREE BLOCK : %d",i);

 
 // Return SYSERR if not enough space is available
 if(i==fsd->freemasksz)
 {
   return SYSERR;
 }

 //Return SYSERR if filename already exists
  
  
  return OK;
}