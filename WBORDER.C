#include "curses.h"
#include "window.h"

/*AT&T
AT&T The wborder routine draws a border around the edges of the window.
AT&T The argument ls is a character and attributes used for the left
AT&T side of the border,
AT&T rs - right side, ts - top side, bs - bottom side,
AT&T tl - top left-hand corner,  tr - top right-hand corner,
AT&T bl - bottom left-hand corner, and br - bottom right-hand corner.
AT&T If any of these arguments is zero, then the following default
AT&T values are used instead: ACS_VLINE, ACS_VLINE, ACS_HLINE,
AT&T ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_BLCORNER, ACS_BRCORNER
AT&T */

int
wborder(WINDOW *win, chtype ls, chtype rs, chtype ts, chtype bs,
        chtype tl, chtype tr, chtype bl, chtype br)
{
  _LINE *ystart, *yend;
  chtype *xstart, *xend;
  chtype *xptr;
  int cols;

  if(win == 0) return(ERR);

#ifdef A_ALTCHARSET
  if(ls == (chtype)0) ls = ACS_VLINE;
  if(rs == (chtype)0) rs = ACS_VLINE;
  if(ts == (chtype)0) ts = ACS_HLINE;
  if(bs == (chtype)0) bs = ACS_HLINE;
  if(tl == (chtype)0) tl = ACS_ULCORNER;
  if(tr == (chtype)0) tr = ACS_URCORNER;
  if(bl == (chtype)0) bl = ACS_LLCORNER;
  if(br == (chtype)0) br = ACS_LRCORNER;
#else
  if(ls == (chtype)0) ls = (chtype) '|';
  if(rs == (chtype)0) rs = (chtype) '|';
  if(ts == (chtype)0) ts = (chtype) '-';
  if(bs == (chtype)0) bs = (chtype) '-';
  if(tl == (chtype)0) tl = (chtype) '+';
  if(tr == (chtype)0) tr = (chtype) '+';
  if(bl == (chtype)0) bl = (chtype) '+';
  if(br == (chtype)0) br = (chtype) '+';
#endif

  xstart = win->_lines[0].line;
  xend = xstart + win->_cols;
  xptr = win->_lines[win->_rows-1].line;
  
  for(; xstart != xend; xstart++, xptr++)
    {
    *xstart = ts;
    *xptr = bs;
    }

  cols = win->_cols - 1;
  ystart = win->_lines;
  yend = ystart + win->_rows;
  for(; ystart != yend; ystart++)
    {
    ystart->line[0] = ls;
    ystart->line[cols] = rs;
    ystart->first = 0;
    ystart->last = cols;
    }

  win->_lines[0].line[0] = tl;
  win->_lines[0].line[win->_cols-1] = tr;
  win->_lines[win->_rows-1].line[0] = bl;
  win->_lines[win->_rows-1].line[win->_cols-1] = br;

  win->_flags |= F_DIRTY;

  return(OK);
}
