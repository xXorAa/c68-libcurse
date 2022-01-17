#include "curses.h"
#include "window.h"
#include "screen.h"
#include "privfunc.h"

/*AT&T
AT&T Create and return a pointer to a new window with the given number
AT&T of lines (or rows), rows, and columns, cols.
AT&T The upper left corner of the window is at line begy, column begx.
AT&T If either rows or cols is 0, they will be set to the value of
AT&T LINES-begy and COLS-begx.
AT&T A new full-screen window is created by calling newwin(0,0,0,0);
AT&T */

WINDOW *
newwin(int rows, int cols, int begy, int begx)
{
  register WINDOW *win;

  if(rows == 0) rows = LINES - begy;
  if(cols == 0) cols = COLS - begx;
  if((win=_mallocwindow(rows,cols,FALSE))==0) return((WINDOW*)0);

  win->_begy   = begy + _screen->_stdtop;
  win->_begx   = begx;
  win->_vmin   = -1;
  win->_vtime  = -1;

  (void)werase(win);
  return(win);
}

