#include "curses.h"
#include "screen.h"
#include "window.h"

/*AT&T
AT&T The virtual screen cursor is set to y,x.  If y and x are both -1,
AT&T then leaveok() will be set.  The two routines getsyx() and setsyx()
AT&T are designed to be used by a library routine which manipultes curses
AT&T windows but does not want to change the current position of the
AT&T program's cursor.  The library routine would call getsyx() at the
AT&T beginning, do its manipulation of its own windows, do a
AT&T wnoutrefresh() on its window, call setsyx(), and then call doupdate().
AT&T */

int
setsyx(int y, int x)
{
  WINDOW *physcr;

  if(_screen == 0 || (physcr = _screen->_physcr) == 0 ||
     y<(-1) || x<(-1) || y>=physcr->_rows || x>=physcr->_cols)
    return(ERR);

  if(y == -1 && x == -1) return leaveok(physcr, TRUE);
  else
    {
    if(y != -1) physcr->_cury = y;
    if(x != -1) physcr->_curx = x;
    }
  return(OK);
}
