#include "curses.h"
#include "window.h"

/*AT&T
AT&T This routine provides finer control over the overlay() and
AT&T overwrite() routines.  As in the prefresh() routine, a rectangle
AT&T is spedified in the destination window, (dminrow, dmincol) and
AT&T (dmaxrow, dmaxcol), and the upper-left-corner coordinates of the
AT&T source window (sminrow, smincol).  If the arguments overlay is
AT&T TRUE, then copying is non-destructive, as in overlay().
AT&T */

int
copywin(WINDOW *srcwin, WINDOW *dstwin, int sminrow, int smincol,
        int dminrow, int dmincol, int dmaxrow, int dmaxcol, int ovrlay)
{
  _LINE *ystart, *yend, *yptr;
  chtype *xstart, *xend, *xptr;
  chtype ch;
  int smaxrow, smaxcol;

  if((srcwin == 0) || (dstwin == 0)) return(ERR);

  if(dmaxrow > dstwin->_rows) dmaxrow = dstwin->_rows;
  if(dmaxcol > dstwin->_cols) dmaxcol = dstwin->_cols;

  smaxrow = sminrow + (dmaxrow - dminrow);
  smaxcol = smincol + (dmaxcol - dmincol);

  if(smaxrow > srcwin->_rows) smaxrow = srcwin->_rows;
  if(smaxcol > srcwin->_cols) smaxcol = srcwin->_cols;

  dmaxrow = dminrow + (smaxrow - sminrow);
  dmaxcol = dmincol + (smaxcol - smincol);

  ystart = srcwin->_lines + sminrow;
  yend = srcwin->_lines + smaxrow + 1;
  yptr = dstwin->_lines + dmincol;
  for(; ystart != yend; ystart++, yptr++)
    {
    xstart = ystart->line + smincol;
    xend = ystart->line + smaxcol + 1;
    xptr = yptr->line + dmincol;
    for(; xstart != xend; xstart++, xptr++)
      {
      ch = *xstart & A_CHARTEXT;
      if(ovrlay && (ch == (chtype) ' ')) *xptr = ch | dstwin->_attr;
      }
    }
  return wtouchln(dstwin, dminrow, dmaxrow - dminrow + 1, (int)TRUE);
}
