#include <string.h>
#include "curses.h"
#include "window.h"
#include "privfunc.h"

/*AT&T
AT&T The dupwin() routine creates an exact duplicate of the window win.
AT&T */

WINDOW *
dupwin(WINDOW *win)
{
  WINDOW *dup;
  int rows, cols;
  size_t linesz;
  _LINE *sptr, *dptr;

  if(win == 0) return((WINDOW *)0);
  rows = win->_rows;
  cols = win->_cols;
  sptr = win->_lines;
  dup = _mallocwindow(rows,cols,FALSE);
  if(dup == (WINDOW*)0) return((WINDOW*)0);

  linesz = sizeof(chtype)*cols;
  for(dptr = dup->_lines; rows > 0; rows--, sptr++, dptr++)
    {
    (void)memcpy((void *)dptr->line, (void *)sptr->line, linesz);
    }

  dup->_attr   = win->_attr;
  dup->_flags  = win->_flags;
  dup->_begy   = win->_begy;
  dup->_begx   = win->_begx;
  dup->_cury   = win->_cury;
  dup->_curx   = win->_curx;
  if((dup->_parent = win->_parent) != 0)
    {
    dup->_parent->_children++;
    dup->_children = 0 ;
    }

  (void)touchwin(dup);
  return(dup);
}
