#include "curses.h"
#include "window.h"

/*AT&T
AT&T This routine draws a vertical line using ch starting at the
AT&T current cursor position in the window.  The cursor position
AT&T is not changed.  The line is at most n characters long, or
AT&T as many as fit into the window.
AT&T */

int
wvline(WINDOW *win, chtype ch, int n)
{
  _LINE *ystart, *yend;
  int x;

  if(win == 0) return(ERR);

  if(win->_cury + n > win->_rows) n = win->_rows - win->_cury;

  x = win->_curx;
  ch |= (win->_attr & A_ATTRIBUTES);
  ystart = win->_lines + win->_cury;
  yend = ystart + n;
  for(; ystart != yend; ystart++) ystart->line[x] = ch;
  return(OK);
}
