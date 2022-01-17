#include "curses.h"
#include "window.h"

/*AT&T
AT&T The derwin() routine is the same as subwin, except that begin_y
AT&T and begin_x are relative to the origin of the window orig rather
AT&T than the screen.  There is no difference between the subwindows
AT&T and the derived windows.
AT&T */

WINDOW *
derwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x)
{
  if(orig == 0) return((WINDOW *)0);
  return(subwin(orig,nlines,ncols,orig->_begy+begin_y,orig->_begx+begin_x));
}

