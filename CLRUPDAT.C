#include "curses.h"
#include "term.h"
#include "screen.h"
#include "window.h"
#include "privfunc.h"

/*
This routine is used to try to optimise the characters required to clear
areas of the screen at the expense of a bit of processing power.
*/

void
_clr_update(void)
{
  WINDOW *physcr = _screen->_physcr;
  _LINE *ystart, *yend, *yptr;
  chtype *xstart, *xend, *xptr;
  int ccols = curscr->_rows;
  int pcols = physcr->_cols, prows = physcr->_rows;
  chtype ch;
  int y, x;
  bool update;

#ifdef ___notused___
  if(clr_eos != 0 &&
     ((ch = *(*(curscr->_lines+curscr->_rows-1)+curscr->_cols-1)) & A_CHARTEXT) == ' ')
    {
    for(update = 0,
        y = curscr->_rows - 1,
        ystart = curscr->_lines + y,
        yend = curscr->_lines -1,
        yptr = physcr->_lines + y;
        ystart != yend;
        ystart--, yptr--, y--)
      {
      for(x = 0,
          xstart = *ystart,
          xend = xstart + curscr->_cols,
          xptr = *yptr;
          xstart != xend;
          xstart++, xptr++)
        {
        if (*xstart != ch) break;
        update |= (*xptr != ch);
        x++ ;
        }
      if(xstart == xend) break;
      }
    if(update)
      {
      mvcur(physcr->_cury, physcr->_curx, y, x);
      physcr->_cury = y;
      physcr->_curx = x;

      vidputs(ch);
      putp(clr_eos);
      for(xstart = *yptr + x,
          xend = *yptr + physcr->_cols;
          xstart != xend;
          xstart++)
        {
        *xstart = ch;
        }
      last = physcr->_last + y;
      first = physcr->_first + y;
      if(x < *last) *first = x;
      else
        {
        *first = FIRST_NOT_CHANGED;
        *last  = LAST_NOT_CHANGED;
        }

      for(ystart = physcr->_lines + y + 1,
          yend = physcr->_lines + physcr->_rows,
          first = physcr->_first + y + 1,
          last = physcr->_last + y + 1;
          ystart != yend;
          ystart++, first++, last++)
        {
        for(xstart = *ystart,
             xend = xstart + curscr->_cols;
             xstart != xend;
             xstart++)
          {
          *xstart = ch;
          }
        *first = FIRST_NOT_CHANGED;
        *last  = LAST_NOT_CHANGED;
        }
      }
    }
#endif
  if(clr_bol == 0 && clr_eol == 0) return;

  ystart = curscr->_lines;
  yend = ystart + curscr->_rows;
  yptr = physcr->_lines;
  for(y = 0; ystart != yend; ystart++, yptr++, y++)
    {
    if(ystart->first == FIRST_NOT_CHANGED) continue;

    if(clr_bol && (((ch = ystart->line[0]) & A_CHARTEXT) == ' '))
      {
      xstart = ystart->line;
      xend = xstart + ccols;
      xptr = yptr->line;
      for(x = update = 0; xstart != xend; xstart++, xptr++, x++)
        {
        if(*xstart != ch) break;
        update |= (*xptr != ch);
        }
      if(FALSE && update)
        {
        (void)mvcur(prows, pcols, y, x);
        physcr->_cury = y;
        physcr->_curx = x;
        (void)vidattr(ch);
        (void)putp(clr_bol);
        xstart = yptr->line;
        xend = xstart + x;
        for(; xstart != xend; xstart++) *xstart = ch;
        if(x < ystart->last) ystart->first = x;
        else
          {
          ystart->first = FIRST_NOT_CHANGED;
          ystart->last  = LAST_NOT_CHANGED;
          }
        }
      }
  
    if(ystart->first == FIRST_NOT_CHANGED) continue;

    if(clr_eol && ((ch = ystart->line[ccols-1]) & A_CHARTEXT) == ' ')
      {
      x = ccols - 1,
      xend = ystart->line - 1;
      xstart = ystart->line + x,
      xptr = yptr->line + x;
      for(update = 0; xstart != xend; xstart--, xptr--, x--)
        {
        if(*xstart != ch) break;
        update |= (*xptr != ch);
        }
      if(FALSE && update && (x < ystart->last))
        {
        x++;
        (void)mvcur(prows, pcols, y, x);
        physcr->_cury = y;
        physcr->_curx = x;
        (void)vidattr(ch);
        (void)putp(clr_eol);
        xstart = yptr->line + x;
        xend = xstart + ccols;
        for(; xstart != xend; xstart++) *xstart = ch;
        if(x > ystart->first) ystart->last = x-1;
        else
          {
          ystart->first = FIRST_NOT_CHANGED;
          ystart->last  = LAST_NOT_CHANGED;
          }
        }
      }
    }
}
