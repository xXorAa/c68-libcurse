#include "curses.h"
#include "window.h"

/*AT&T
AT&T The wsetscrreg() routine allows the application programmer to set
AT&T a software scrolling region in a window.  top and bot are the line
AT&T numbers of the top and bottom margin of the scrolling region.
AT&T If this option and scrollok are enabled, an attempt to move off the
AT&T bottom margin line causes all lines in the scrolling region to scoll
AT&T up one line.  Only the text of the window is scrolled.
AT&T */

int
wsetscrreg(WINDOW *win, int top, int bot)
{
  if(win == 0 || top < 0 || bot > win->_rows-1 || top > win->_rows)
    return(ERR);

  win->_top = top;
  win->_bot = bot;
  return(OK);
}
