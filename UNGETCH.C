#include "curses.h"
#include "privfunc.h"

/*
This routine is an internal routine which pushes the character
back onto the input stream.
*/

int
ungetch(int ch)
{
  _ungetchar(ch);
  return(OK);
}
