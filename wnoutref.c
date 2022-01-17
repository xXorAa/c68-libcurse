#include "curses.h"
#include "window.h"

/*AT&T
AT&T The routine wnoutrefresh() copies the named window to the virtual screen,
AT&T describing what the programmer wants on the screen.
AT&T */

int
wnoutrefresh(WINDOW *win)
{
  if(win == 0) return(ERR);

  wsyncdown(win);

  if(win->_flags & F_DIRTY)
    {
    register _LINE *ystart = win->_lines;
    _LINE *yend = ystart + win->_rows;
    register _LINE *yptr = curscr->_lines + win->_begy;
    for(; ystart != yend; ystart++, yptr++)
      {
      register chtype *xstart;
      chtype *xend, *xptr;
      int i;

      if(ystart->first == FIRST_NOT_CHANGED) continue;

      xstart = ystart->line + ystart->first;
      xend = ystart->line + (ystart->last + 1);
      xptr = yptr->line + win->_begx + ystart->first;
      for(; xstart != xend; xstart++, xptr++) *xptr = *xstart;

      if((i=ystart->first + win->_begx) < yptr->first) yptr->first = i;
      if((i=ystart->last + win->_begx) > yptr->last) yptr->last = i;

      ystart->first = FIRST_NOT_CHANGED;
      ystart->last  = LAST_NOT_CHANGED;
      }
    }

  curscr->_flags |= win->_flags;
  win->_flags &= ~(F_CLEAR | F_DIRTY | F_INSERTED);
  curscr->_cury = win->_begy + win->_cury;
  curscr->_curx = win->_begx + win->_curx;

  return(OK);
}
