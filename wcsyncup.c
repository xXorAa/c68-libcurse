#include "curses.h"
#include "window.h"

/*AT&T
AT&T The routine wcursyncup() updates the current cursor position of all
AT&T the ancestors of the window to reflect the current cursor position
AT&T of the window.
AT&T */

void
wcursyncup(WINDOW *win)
{
  WINDOW *parent;
  int y, x;

  if(win != 0 && (parent = win->_parent) != 0)
    {
    getparyx(win, y, x);
    parent->_cury = y + win->_cury;
    parent->_curx = x + win->_curx;
    wcursyncup(parent);
    }
}
