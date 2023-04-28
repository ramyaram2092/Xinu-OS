
#include <xinu.h>
#include <fs.h>

extern fsystem_t *fsd;
extern filetable_t oft[NUM_FD];

/*
 * fs_close - Return SYSERR if the file is already closed
 *     otherwise, write the file's inode back to the block
 *     device and set the entry in the oft to FSTATE_CLOSED
 */
syscall fs_close(int fd)
{
  intmask mask = disable();

  int i = 0;

  if (oft[fd].state == FSTATE_CLOSED)
  {
    restore(mask);
    return SYSERR;
  }

  void *buffer = (void *)&oft[fd].in;
  bs_write(oft[fd].in.id, 0, buffer, sizeof(buffer));
  oft[fd].state = FSTATE_CLOSED;
  oft[fd].fileptr = 0;

  restore(mask);
  return OK;
}