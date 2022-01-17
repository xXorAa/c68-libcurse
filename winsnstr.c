#include <string.h>
#include "curses.h"
#include "window.h"

/*AT&T
AT&T This routine inserts at most n characters (or as many will fit)
AT&T on to a line) before the character under the cursor.
AT&T All characters to the right of the cursor are moved to the right, with
AT&T the possibility of the rightmost characters on the line being lost.
AT&T The cursor position does not change.
AT&T If is negative then the entire string is inserted.
AT&T */

int
winsnstr(WINDOW *win, char *str, int n)
{
  _LINE *ystart;
  chtype *xstart, *xend, *xptr;

  if(win == 0 || str == 0) return(ERR);

  if(n == -1) n = strlen(str);

/*IMB this needs a lot work, it does not deal with \t,\n,\r and \b*/
  if(win->_curx + n > win->_cols) n = win->_cols - win->_curx;

  ystart = win->_lines + win->_cury;
  xstart = ystart->line + win->_cols - n;
  xend = ystart->line + win->_curx;
  xptr = xstart - 1;
  for(; xstart != xend; xstart--, xptr--) *xstart = *xptr;

  for(xstart = ystart->line; xstart != xend; xstart++, str++)
    {
    *xstart = (*str==' ')?win->_attr:(*str | (win->_attr & A_ATTRIBUTES));
    }

  if(ystart->first > win->_curx) ystart->first = win->_curx;
  ystart->last = win->_cols - 1;

  return(OK);
}
