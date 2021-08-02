#include "curses.h"
#include "screen.h"
#include "window.h"

/*AT&T
AT&T Move the window so that the upper left corner will be at
AT&T position (y,x).  If the move would cause the window to be
AT&T off the screen it is an error and the window is not moved.
AT&T Moving subwindows is allowed, but should be avoided.
AT&T */

int
mvwin(WINDOW *win, int y, int x)
{
  if(win == 0) return(ERR);

  if((y < 0) || (x < 0) ||
     (y + win->_rows >= _screen->_physcr->_rows) ||
     (x + win->_cols >= _screen->_physcr->_cols))
    return(ERR);

  win->_begy = y;
  win->_begx = x;
  return(touchwin(win));
}
