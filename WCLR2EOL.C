#include "curses.h"
#include "window.h"
/*AT&T
AT&T The wclrtoeol() routine erases the current line to the right
AT&T of the cursor, inclusive.
AT&T */

int
wclrtoeol(WINDOW *win)
{
  if(win == 0) return(ERR);

  {
  _LINE *ystart = win->_lines + win->_cury;
  chtype *xstart = ystart->line + win->_curx;
  chtype *xend = ystart->line + win->_cols;
  chtype ch = win->_attr;

  for(; xstart != xend; xstart++) *xstart = ch;
  }

  return(touchline(win, win->_cury, 1));
}
