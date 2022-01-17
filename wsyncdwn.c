#include "curses.h"
#include "window.h"

/*AT&T
AT&T The routine wsyncdown() updates the status structure of the window
AT&T to reflect the changes in the status structures of its ancestors.
AT&T Applications seldom call this routine because it is called
AT&T automatically by wrefresh().
AT&T */

void
wsyncdown(WINDOW *win)
{
  WINDOW *parent;

  if(win != 0 && (parent = win->_parent) != 0)
    {
    _LINE *sptr = parent->_lines + (win->_begy - parent->_begy);
    _LINE *eptr = sptr + win->_rows;
    int y;
    wsyncdown(parent);
    for(y = 0; sptr != eptr; sptr++, y++)
      {
      if(sptr->first == FIRST_NOT_CHANGED) continue;
      (void)touchline(win, y, 1);
      }
    }
}
