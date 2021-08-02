#include <string.h>
#include "curses.h"
#include "window.h"

/*AT&T
AT&T This routine copies chstr directly into the window image
AT&T structure starting at the current cursor position.
AT&T It will copy at most n elements, but no more than will fit on a line.
AT&T If n=-1 then the whole string is copied, to the maximum that fits
AT&T on a line.
AT&T
AT&T The position of the cursor is NOT advanced.  These routines works
AT&T faster then waddnstr because they merely copy chstr into the window
AT&T image structure.
AT&T On the other hand, care must be taken when using these functions
AT&T because they don't perform any kind of checking (such as for
AT&T newline characters), they don't advance the current cursor position,
AT&T and they truncate the string, rather than wrapping it around
AT&T to the new line.
AT&T*/

int
waddchnstr(WINDOW *win, chtype *chstr, int n)
{
  if(win == 0 || chstr == 0) return(ERR);

  if((n == -1) || ((win->_curx+n)> win->_cols)) n = win->_cols - win->_curx;
  (void)memcpy((void *)&win->_lines[win->_cury].line[win->_curx],
					(void *)chstr,n*sizeof(chtype));
  return(OK);
}
