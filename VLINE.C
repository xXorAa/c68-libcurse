#include "curses.h"

/*AT&T
AT&T This routine draws a vertical line using ch starting at the
AT&T current cursor position in the window.  The cursor position
AT&T is not changed.  The line is at most n characters long, or
AT&T as many as fit into the window.
AT&T */

int
vline(chtype ch, int n)
{
  return(wvline(stdscr,ch,n));
}
