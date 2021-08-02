#include "curses.h"
#include "window.h"

/*AT&T
AT&T The wclrtobot() routine erases all lines below the cursor in the window.
AT&T Also the current line to the right of the cursor, inclusive, is erased.
AT&T */

int
wclrtobot(WINDOW *win)
{
  _LINE *ystart, *yend;
  int cols;
  chtype ch;

  if(win == 0) return(ERR);

  ch = win->_attr;
  ystart = win->_lines + win->_cury + 1;
  yend = win->_lines + win->_rows;
  cols = win->_cols;
  for(; ystart != yend; ystart++)
    {
    chtype *xstart = ystart->line;
    chtype *xend = xstart + cols;
    for(; xstart!=xend; xstart++) *xstart = ch;
    }

  (void) wclrtoeol(win);
  return(touchwin(win));
}
