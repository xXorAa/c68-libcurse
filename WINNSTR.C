#include "curses.h"
#include "window.h"

/*AT&T
AT&T This routine returns a string of characters in str, starting at the
AT&T current cursor position in the named window and ending at the right
AT&T margin of the window.  Attributes are stripped from the characters.
AT&T */

int
winnstr(WINDOW *win, char *str, int n)
{
  chtype *xstart, *xend;

  if(win == 0 || str== 0) return(ERR);

  if((n<0) || (n+win->_curx > win->_cols)) n = win->_cols - win->_curx;

  for(xstart = win->_lines[win->_cury].line + win->_curx,
      xend = xstart + n + 1;
      xstart != xend;
      xstart++, str++)
    {
    *str = (char) (*xstart & A_CHARTEXT);
    }
  return(OK);
}
