#include "curses.h"
#include "window.h"
#include "privfunc.h"

/*AT&T
AT&T Create and return a pointer to a new pad data structure with the
AT&T given number of lines (or rows), nlines and columns, ncols.
AT&T A pad is a window that is not restricted by the screen size and
AT&T is not necessarily associated with a particular part of the screen.
AT&T Pads can be used when a large window is needed, and only a part of
AT&T the window will be on the screen at one time.
AT&T Automatic refreshes of pads (e.g. from scrolling or echoing of input)
AT&T do not occur.  It is not legal to call wrefresh() with a pad as an
AT&T argument; the routines prefresh() or pnoutrefresh() should be called
AT&T instead.  Note that these routines require additional parameters to
AT&T specify the part of the pad to be displayed, and the location on the
AT&T screen to be used for display.
AT&T */

WINDOW *
newpad(int nlines, int ncols)
{
  WINDOW *win;

  if(nlines==0 || ncols==0) return((WINDOW*)0);
  if((win=_mallocwindow(nlines,ncols,FALSE))==0) return((WINDOW*)0);
  win->_flags |= F_PAD;
  win->_nlines = nlines;
  win->_ncols  = ncols;
  win->_rows   = win->_cols = 0;

  (void)werase(win);
  return(win);
}
