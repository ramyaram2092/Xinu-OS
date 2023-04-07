#include <xinu.h>

#define TY_ESC   0x1b
#define TY_BRACE 0x5b
#define TY_A     0x41

#define SKIP     0
#define DO_PRINT 1

local void echo(char ch, struct ttycblk* typtr, struct uart_csreg* csrptr);
local void clearline(struct ttycblk* typtr, struct uart_csreg* csrptr);

/*
 * ttydiscipline - Handles special character interactions.
 * 
 * Returns - Whether to print character (SKIP or DO_PRINT)
 */
int ttydiscipline(char ch,
		  struct ttycblk *typtr,
		  struct uart_csreg* csrptr) {

  if (ch == TY_NEWLINE || ch == TY_RETURN) {
    /* 
     * Copy the contents of the 'tyibuff' buffer from the 'tyihead' through 'tyitail'
     *     into the 'typrev' buffer.
     * 
     *   char    typrev[TY_IBUFLEN];      buffer to store prev command 
         char    tycommand;              /* previous command state 
     * 
     */
    char* curr=typtr->tyihead; // for traversing through the linked list

    int i=0; 
    
    // i think i dont have to worry about the traversal in a ring buffer because it is linked list
    //  discuss with kaushi
    while(curr!=typtr->tyitail && i<128)
    {
        typtr->typrev[i]=*curr; // read the charcacter
        curr++;// move to the necxt charcter
        i++; // increment the buffer of typrev
    }
    typtr->tycommand='N';
    
  }
  
  /*
   * Check if the up key was pressed:
   * Use 'tycommand' to indicate if a command is in progress and the previous character
   *     If the characters appear in the sequence TY_ESC, then TY_BRACE, then TY_A
   *     the up key was sent
   */
  else if (ch==TY_ESC && typtr->tycommand='N')
  {
     typtr->tycommand='E';
  }
  else if (ch==TY_BRACE && typtr->tycommand=='E')
  {
    typtr->tycommand='B';
  }
  else if (ch==TY_A && typtr->tycommand='B')
  {
    typtr->tycommand='A';
  }


 // If the up key is detected (as above)
      /*
       * Clear the current input with the 'clearline' function and copy the contents of 
       *     'typrev' buffer into the 'tyibuff' buffer
       *     remember to reset the 'tyicursor' as well
       *  Call 'echo' on each character to display it to the screen
       */
if(ch==TY_ESC && typtr->tycommand=='A')
{
    clearline(typtr,csrptr);

    int i=0;

    while(i<strlen(typtr->typrev))
    {
        typtr->tyitail=typtr->typrev[i];
        typtr->tyitail++;
        i++;
        typtr->tyicursor++;
    }

    char *curr= typtr->tyihead;
    for (i=0; i < typtr->tyicursor; i++) {
    echo(*curr, typtr, csrptr);
    ttyhandle_out(typtr, csrptr);
    }
  }

 
  return DO_PRINT;
}

local void echo(char ch, struct ttycblk* typtr, struct uart_csreg* csrptr) {
  *typtr->tyetail++ = ch;

  /* Wrap around buffer, if needed */
  if (typtr->tyetail >= &typtr->tyebuff[TY_EBUFLEN])
    typtr->tyetail = typtr->tyebuff;
  ttykickout(csrptr);
  return;
}

local void clearline(struct ttycblk* typtr, struct uart_csreg* csrptr) {
  int i, j;
  while (typtr->tyitail != typtr->tyihead)
    if ((--typtr->tyitail) < typtr->tyibuff)
      typtr->tyitail += TY_IBUFLEN;

  for (i=0; i < typtr->tyicursor; i++) {
    echo(TY_BACKSP, typtr, csrptr);
    echo(TY_BLANK, typtr, csrptr);
    echo(TY_BACKSP, typtr, csrptr);
    for (j=0; j<3; j++)
      ttyhandle_out(typtr, csrptr);
  }
  typtr->tyicursor = 0;
}