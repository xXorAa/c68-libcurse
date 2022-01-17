#include <string.h>
#include "curses.h"
#include "window.h"

/*AT&T
AT&T This routine returns a string of type chtype, starting at the
AT&T current cursor position in the named window and ending at the
AT&T right margin of the window.  It returns at most n characters.
AT&T */

int
winchnstr(WINDOW *win, chtype *chstr, int n)
{
  if(win == 0 || chstr == 0) return(ERR);

  if((n < 0) || (n + win->_curx > win->_cols)) n = win->_cols - win->_curx;
  (void)memcpy((void *)chstr,(void *)(win->_lines[win->_cury].line+win->_curx),
							 sizeof(chtype)*n);
  return(OK);
}
