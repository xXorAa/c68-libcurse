#include "curses.h"
#include "window.h"
#include "privfunc.h"

/*AT&T
AT&T Create and return a pointer to a new window with the given number
AT&T of lines (or rows), rows, and columns, cols.  The window is at
AT&T position (begy, begx) on the screen.  (This position is relative to
AT&T the screen, and not to the window orig).  The window is made in the
AT&T middle of the window orig, so that changes made to one window will
AT&T affect the character image of both window.  When changing the image
AT&T of a subwindow, it will be necessary to call touchwin() or touchlne()
AT&T on orig before calling wrefresh() on orig.
AT&T */

WINDOW *
subwin(WINDOW *orig, int rows, int cols, int begy, int begx)
{
  WINDOW *win;
  if(orig==(WINDOW*)0) return((WINDOW*)0);
  if((win=_mallocwindow(rows,cols,TRUE))==(WINDOW*)0) return((WINDOW*)0);
  _setupsubarea(win, orig, rows, begy, begx);

  win->_begy   = begy;
  win->_begx   = begx;
  win->_parent = orig;

  orig->_children++;

  (void)touchwin(win);
  return(win);
}
