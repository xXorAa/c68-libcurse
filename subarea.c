#include "curses.h"
#include "window.h"
#include "privfunc.h"

void
_setupsubarea(WINDOW *win, WINDOW *orig, int rows, int begy, int begx)
{
  _LINE *start = win->_lines;
  _LINE *end = start + rows;
  _LINE *sptr = orig->_lines + (begy - orig->_begy);
  int xoff = begx - orig->_begx;

  for(; start != end; start++, sptr++)
    {
    start->line = sptr->line + xoff;
    }
}

