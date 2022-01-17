#include <string.h>
#include "curses.h"
#include "term.h"
#include "screen.h"
#include "window.h"
#include "privfunc.h"

/*
This routine checks to see if it is possible to update most of
the screen by scrolling it.
*/

void
_scroll_update(void)
{
  WINDOW *physcr = _screen->_physcr;
  int rows = physcr->_rows, cols = physcr->_cols;
  size_t linesz = cols*sizeof(chtype);
  _LINE *ystart, *yend, *yptr;
  chtype ch = physcr->_attr;
  int y;

  if((curscr->_flags & F_INSERTED) == 0 || insert_line == 0) return;

  for(y = 1; y < rows - 2; y++)
    {
    ystart = curscr->_lines;
    yend = ystart + (curscr->_rows - 1);
    yptr = physcr->_lines + y;
    for(; ystart != yend; ystart++, yptr++)
      {
      if(memcmp((void *)ystart->line, (void *)yptr->line, linesz)) break;
      }
    if(ystart == yend)
      {
      /* Yipee!! We can scroll the screen */
      (void)mvcur(physcr->_cury, physcr->_curx, physcr->_rows-1, 0);
      physcr->_cury = rows - 1;
      physcr->_curx = 0;

      ystart = curscr->_lines;
      yend = ystart + (curscr->_rows - y);
      yptr = physcr->_lines;
      for(; ystart != yend; ystart++, yptr++)
        {
        (void)memcpy((void *)yptr->line, (void *)ystart->line, linesz);
        ystart->first = FIRST_NOT_CHANGED;
        ystart->last  = LAST_NOT_CHANGED;
        }
      ystart = physcr->_lines + (rows - y);
      yend = ystart + rows;
      for(; ystart != yend; ystart++)
        {
        chtype *xstart = ystart->line, *xend = xstart + cols;
        for(; xstart != xend; xstart++) *xstart = ch;
        }

      for(; y; y--) (void)putp(insert_line);
      return;
      }
    }
}
