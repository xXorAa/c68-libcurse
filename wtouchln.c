#include "curses.h"
#include "window.h"

/*AT&T
AT&T The wtouchln() routine makes n lines in the window, starting at
AT&T line y, look as if they have (changed = 1) or have not
AT&T (changed = 0) been changed since the last call to wrefresh().
AT&T */

int
wtouchln(WINDOW *win, int y, int n, int changed)
{
  _LINE *sptr, *eptr;
  int cols;

  if(win == 0) return(ERR);

  if((n<0) || (win->_begx + (n += y) > win->_rows)) n = win->_rows;

  cols = changed ? 0 : FIRST_NOT_CHANGED;
  sptr = win->_lines + y;
  eptr = win->_lines + n;
  for(; sptr != eptr; sptr++) sptr->first = cols;

  cols = changed ? (win->_cols - 1) : LAST_NOT_CHANGED;
  sptr = win->_lines + y,
  eptr = win->_lines + n;
  for(; sptr != eptr; sptr++) sptr->last = cols;

  if(changed) win->_flags |= F_DIRTY;
  else
    {
    win->_flags &= ~F_DIRTY;
    /* need to determine if there are in fact any lines left
       which have a change on it */
    sptr = win->_lines;
    eptr = sptr + win->_rows;
    for(; sptr != eptr; sptr++)
      {
      if(sptr->last != LAST_NOT_CHANGED)
        {
        win->_flags |= F_DIRTY;
        break;
        }
      }
    }

  return(OK);
}
