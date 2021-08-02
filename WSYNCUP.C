#include "curses.h"
#include "window.h"

/*AT&T
AT&T The routine wsyncup() causes the changes in the status structure
AT&T of a window to be reflected in the status structures of its ancestors.
AT&T If synok() is called with second argument TRUE then wsyncup() is
AT&T called automatically whenever there is a change in the window.
AT&T */

void
wsyncup(WINDOW *win)
{
  WINDOW *parent;

  while(win != 0 && (parent = win->_parent) != 0)
    {
    if(win->_flags & F_DIRTY)
      {
      int y = win->_begy - parent->_begy;
      _LINE *sptr = win->_lines;
      _LINE *eptr = sptr + win->_rows;
      for(; sptr != eptr; sptr++, y++)
        {
        if(sptr->first == FIRST_NOT_CHANGED) continue;
        (void)touchline(parent, y, 1);
        }
      }
    win = parent;
    }
}
