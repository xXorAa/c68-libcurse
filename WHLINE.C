#include "curses.h"
#include "window.h"

/*AT&T
AT&T This routine draws a horizontal line using ch starting at the
AT&T current cursor position in the window.  The cursor position is
AT&T not changed.  The line is at most n characters long, or as many
AT&T as fit into the window.
AT&T */

int
whline(WINDOW *win, chtype ch, int n)
{
  chtype *xstart, *xend;

  if(win == 0) return(ERR);

  if(win->_curx + n > win->_cols) n = win->_cols - win->_curx;

  ch |= (win->_attr & A_ATTRIBUTES);
  xstart = win->_lines[win->_cury].line + win->_curx;
  xend = xstart + n;
  for(; xstart != xend; xstart++) *xstart = ch;
  return(OK);
}
