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
  
    char* curr=typtr->tyihead; // for traversing through the linked list

    int i=0; 
    
      /* 
     * Copy the contents of the 'tyibuff' buffer from the 'tyihead' through 'tyitail'
     *     into the 'typrev' buffer. 
     * 
     */
    while(curr!=typtr->tyitail && i<TY_IBUFLEN)
    {
        typtr->typrev[i]=*curr; // read the charcacter
        curr++;// move to the next charcter
        // echo(typtr->typrev[i], typtr, csrptr);
        if(curr>=&typtr->tyibuff[TY_IBUFLEN]) //check wrap around
            curr=typtr->tyibuff;
        i++; // increment the buffer of typrev

    }
    if(i<TY_IBUFLEN-1)
        typtr->typrev[i]='\0';
    

  }
  
  /*
   * Check if the up key was pressed:
   * Use 'tycommand' to indicate if a command is in progress and the previous character
   *     If the characters appear in the sequence TY_ESC, then TY_BRACE, then TY_A
   *     the up key was sent
   */
  else if (ch==TY_ESC && typtr->tycommand=='\0')
  {
    // echo('E', typtr, csrptr);
     typtr->tycommand=ch;
     return SKIP;
  }
  else if (ch==TY_BRACE && typtr->tycommand==TY_ESC)
  {
    // echo('L', typtr, csrptr);
    typtr->tycommand=ch;
    return SKIP;
  }
  else if (ch==TY_A && typtr->tycommand==TY_BRACE)
  {
    // echo('O', typtr, csrptr);
    clearline(typtr,csrptr);
    int i=0;
    
    // writing into the buffer
    while(i<TY_IBUFLEN || typtr->typrev[i]!='\0')
    {
        printf("\n typrev length :%c\n",typtr->typrev[i]);

        *typtr->tyitail=typtr->typrev[i]; //typtr->typrev[i];
        // echo('X', typtr, csrptr);
        typtr->tyitail++;
        //wrap around
        if(typtr->tyitail>=&typtr->tyibuff[TY_IBUFLEN])
            typtr->tyitail=typtr->tyibuff;
        i++;
    }
    int n=i;
    // printing the input buffer
    char *curr= typtr->tyihead;
    for (i=0; i <n; i++) {
        echo(*curr, typtr, csrptr);
        curr++;
        //wrap around
        if(curr>=&typtr->tyibuff[TY_IBUFLEN])
            curr=typtr->tyibuff;
     typtr->tyicursor++;
    
    }
    typtr->tycommand='\0';

    return SKIP;
  }


 // If the up key is detected (as above)
      /*
       * Clear the current input with the 'clearline' function and copy the contents of 
       *     'typrev' buffer into the 'tyibuff' buffer
       *     remember to reset the 'tyicursor' as well
       *  Call 'echo' on each character to display it to the screen
       */
// if(typtr->tycommand=='D')
// {
//     clearline(typtr,csrptr);
    
     
//     int i=0;

//     // writing into the buffer
//     while(i<TY_IBUFLEN || typtr->typrev[i]!='\0')
//     {
//         *typtr->tyitail='X'; //typtr->typrev[i];
//         echo(typtr->typrev[i], typtr, csrptr);
//         typtr->tyitail++;
//         //wrap around
//         if(typtr->tyitail>=&typtr->tyibuff[TY_IBUFLEN])
//             typtr->tyitail=typtr->tyibuff;
//         i++;
//     }
//     int n=i;
//     // printing the input buffer
//     char *curr= typtr->tyihead;
//     for (i=0; i <n; i++) {
//         // echo('Y', typtr, csrptr);
//         curr++;
//         //wrap around
//         if(curr>=&typtr->tyibuff[TY_IBUFLEN])
//             curr=typtr->tyibuff;
//      typtr->tyicursor++;
    
//     }

//     return SKIP;

//   }
 
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