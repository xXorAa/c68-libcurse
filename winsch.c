#include "curses.h"
#include "window.h"

/*AT&T
AT&T The character ch is inserted before the character under the cursor.
AT&T All characters to the right are moved one space to the right, losing
AT&T the rightmost character of the line.
AT&T The cursor position does not change.
AT&T */

int
winsch(WINDOW *win, chtype ch)
{
  _LINE *ystart;
  chtype *xstart, *xend;
  chtype *xptr;

  if(win== 0) return(ERR);

  ystart = win->_lines + win->_cury;
  xstart = ystart->line + win->_cols - 1;
  xend = ystart->line + win->_curx;
  xptr = xstart - 1;
  for(; xstart != xend; xstart--, xptr--) *xstart = *xptr;
  *xstart = ch | win->_attr;

  if(ystart->first > win->_curx) ystart->first = win->_curx;
  ystart->last = win->_cols - 1;
  return(OK);
}
