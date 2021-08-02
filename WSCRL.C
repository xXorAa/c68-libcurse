#include "curses.h"
#include "window.h"

/*AT&T
AT&T The wscrl() routine, for positive n scroll the window up n lines
AT&T (line i+n becomes n); otherwise scroll the window down n lines.
AT&T This involves moving the lines in the window character image structure.
AT&T The current cursor position is not changed.
AT&T */

int
wscrl(WINDOW *win, int n)
{
  int y;
  int ret;

  if(win == 0) return(ERR);

  y = win->_cury;
  win->_cury = 0;
  ret = winsdelln(win, -n);
  win->_cury = y;
  return(ret);
}
