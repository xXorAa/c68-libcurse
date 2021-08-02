#include <stdlib.h>
#include <string.h>
#include "curses.h"
#include "screen.h"
#include "window.h"
#include "privfunc.h"

WINDOW *
_mallocwindow(int rows, int cols, bool sub)
{
  register WINDOW *win;
  size_t winsz = sizeof(WINDOW) + sizeof(_LINE)*(rows-1);
  if(!sub) winsz += sizeof(chtype)*rows*cols;
  if((win = (WINDOW *)calloc((size_t)1,winsz)) != 0)
    {
    if(!sub)
      {
      /* setup line pointers */
      register _LINE *start = win->_lines;
      register _LINE *end = start + rows;
      register chtype *area = (chtype*)&win->_lines[rows];

      for(;start != end; start++, area += cols) start->line = area;
      }

    win->_attr   = A_NORMAL | ' ';
    win->_flags  = F_NORMAL | F_TIMEOUT | F_LEAVE;
    win->_rows   = rows;
    win->_cols   = cols;
    win->_bot    = rows - 1;
    win->_parent = (WINDOW *)0;
    win->_vmin   =
    win->_vtime  = -1;
    return(win);
    }
  return((WINDOW*)0);
}

