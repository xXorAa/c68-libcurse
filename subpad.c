#include "curses.h"
#include "window.h"
#include "privfunc.h"

/*AT&T
AT&T Create and return a pointer to a subwindow within a pad with the
AT&T given number of lines (or rows), nlines, and columns, ncols.
AT&T Unlike subwin(), which uses screen coordinates, the window is
AT&T at position (begy, begx) on the pad.  The window is made in the
AT&T middle of the window orig, so that changes made to one window will
AT&T affect the character image of both windows.  When changing the
AT&T image of a subwindow, it will be necessary to call touchwin() or
AT&T touchline() on orig before calling prefresh() on orig.
AT&T */

WINDOW *
subpad(WINDOW *orig, int nlines, int ncols, int begy, int begx)
{
  WINDOW *win;

  if(orig==(WINDOW*)0) return((WINDOW*)0);
  if((win=_mallocwindow(nlines,ncols,TRUE))==(WINDOW*)0) return((WINDOW*)0);
  _setupsubarea(win, orig, nlines, begy, begx);

  win->_flags  |= F_PAD;
  win->_nlines = nlines;
  win->_ncols  = ncols;
  win->_rows   = win->_cols = 0;
  win->_begy   = win->_begx = 0;
  win->_parent = orig;

  orig->_children++;

  (void)touchwin(win);
  return(win);
}
