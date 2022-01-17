#include "curses.h"
#include "window.h"

/*AT&T
AT&T The mvderwin() routine moves a derived window (or subwindow) inside
AT&T its parent window.  The screen-relative parameters of the window
AT&T are not changed.  This routine is used to display different parts
AT&T of the parent window at the same physical position on the screen.
AT&T */

int
mvderwin(WINDOW *win, int par_y, int par_x)
{
  WINDOW *parent;
  _LINE *ystart, *yend, *sptr;

  if(win == 0 ||
     (parent = win->_parent) == 0 ||
     (par_y < 0) || (par_x < 0) ||
     (par_y + win->_rows > parent->_rows) ||
     (par_x + win->_cols > parent->_cols))
    return(ERR);

  ystart = win->_lines;
  yend = ystart + win->_rows;
  sptr = parent->_lines + par_y;
  for(; ystart != yend; ystart++, sptr++)
    ystart->line = sptr->line + par_x;

  win->_begy = parent->_begy + par_y;
  win->_begx = parent->_begx + par_x;

  return(touchwin(win));
}
