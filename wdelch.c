#include "curses.h"
#include "window.h"

/*AT&T
AT&T The characters under the cursor in the window is deleted.
AT&T All characters to the right on the same line are moved to the left
AT&T one position and the last character on the line is filled with a blank.
AT&T The cursor position does not change.
AT&T */

int
wdelch(WINDOW *win)
{
  _LINE *ystart;
  chtype *xstart, *xend;
  chtype *xptr;

  if(win == 0) return(ERR);


  ystart = win->_lines + win->_cury;
  xstart = ystart->line + win->_curx;
  xptr = xstart + 1;
  xend = ystart->line + win->_cols - 1;
  for(; xstart != xend; xstart++, xptr++) *xstart = *xptr;
  *xstart = ' ' | (win->_attr & A_ATTRIBUTES);

  if(ystart->first > win->_curx) ystart->first = win->_curx;
  ystart->last = win->_cols - 1;
  win->_flags |= F_DIRTY;
  return(OK);
}
