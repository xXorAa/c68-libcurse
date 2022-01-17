#include "curses.h"
#include "window.h"

/*AT&T
AT&T This routine is analogous to wnoutrefresh() except that pads,
AT&T instead of windows, are involved.  The additional parameters
AT&T are needed to indicate what part of the pad and screen are involved.
AT&T pminrow and pmincol specify the upper left corner, in the pad,
AT&T of the rectangle to be displayed.
AT&T sminrow, smincol, smaxrow and smaxcol specify the edges,
AT&T on the screen, of the rectangle to be displayed.
AT&T The lower right corner in the pad of the rectangle to be displayed
AT&T is calculated from the screen coordinates, since the rectangles
AT&T must be the same size.
AT&T Both rectangles must be entirely contained within their respective
AT&T structures.  Negative values of pminrow, pmincol, sminrow
AT&T and smincol are treated as if they were zero.
AT&T */

int
pnoutrefresh(WINDOW *pad, int pminrow, int pmincol, int sminrow,
             int smincol, int smaxrow, int smaxcol)
{
  _LINE *ystart, *yend, *yptr;
  chtype *xstart, *xend, *xptr;
  int pmaxcol, pmaxrow;
  int f, l;

  if(pad == 0 || !(pad->_flags & F_PAD) || !(pad->_flags & F_DIRTY))
    return(ERR);

  if(pmincol < 0) pmincol = 0;
  if(pminrow < 0) pminrow = 0;
  if(smincol < 0) smincol = 0;
  if(sminrow < 0) sminrow = 0;

  pmaxrow = pminrow + smaxrow - sminrow;
  pmaxcol = pmincol + smaxcol - smincol;

  curscr->_flags |= pad->_flags;
  pad->_flags = F_NORMAL;

  ystart = pad->_lines + pminrow;
  yend = ystart + pmaxrow;
  yptr = curscr->_lines + sminrow;
  for(; ystart != yend; ystart++, yptr++)
    {
    if(ystart->first == FIRST_NOT_CHANGED) continue;

    if((ystart->first > pmaxcol) || (ystart->last < pmincol))
      {
      /* there are changes on this line which */
      /* will not have been written by this call */
      pad->_flags |= F_DIRTY;
      continue;
      }

    f = (ystart->first < pmincol) ? pmincol : ystart->first;
    l = (ystart->last > pmaxcol) ? pmaxcol : ystart->last;
    xstart = ystart->line + f;
    xend = ystart->line + l + 1;
    xptr = yptr->line + smincol + f;
    for(; xstart != xend; xstart++, xptr++) *xptr = *xstart;

    if(f + smincol < yptr->first) yptr->first = f + smincol;
    if(l + smincol > yptr->last) yptr->last = l + smincol;

    if((f >= ystart->first) && (l <= ystart->last))
      {
      ystart->first = FIRST_NOT_CHANGED;
      ystart->last  = LAST_NOT_CHANGED;
      }
    else
      pad->_flags |= F_DIRTY;
    }

  pad->_begy = sminrow;
  pad->_begx = smincol;
  pad->_rows = smaxrow;
  pad->_cols = smaxcol;

  return(OK);
}
