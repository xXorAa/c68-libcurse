#include "curses.h"
#include "window.h"

/*AT&T
AT&T The cursor associated with the window is moved to line (row) y,
AT&T column x.  This does not move the physical cursor of the terminal
AT&T until wrefresh() is called.  The position specified is relative to
AT&T the upper left corner of the window, which is (0,0).
AT&T */

int
wmove(WINDOW *win, int y, int x)
{
  if(win==0) return(ERR);
  if(y<0 || x<0 || y>=win->_rows || x>=win->_cols) return(ERR);
  win->_cury = y;
  win->_curx = x;
  return(OK);
}
