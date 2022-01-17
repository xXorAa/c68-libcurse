#include <string.h>
#include "curses.h"
#include "window.h"

/*AT&T
AT&T This routine, for positive n, inserts n lines into the specified
AT&T window above the current line.  The bottom n lines are lost.
AT&T For negative n, deletes n lines (starting with the one under the
AT&T cursor), and move the remaining lines up,  The bottom n lines are
AT&T cleared.  The current cursor position remains the same.
AT&T */

int
winsdelln(WINDOW *win, int n)
{
  _LINE *ystart, *yend, *yptr;
  chtype *xstart, *xend;
  chtype ch;
  size_t size;

  if(win == 0) return(ERR);
  if(n == 0) return(OK);

  size = win->_cols * sizeof(chtype);
  if(n > 0)
    {
    if(n+win->_cury >= win->_rows) n = win->_rows - win->_cury - 1;
    ystart = win->_lines + win->_rows - n;
    yend = win->_lines + win->_cury;
    yptr = ystart - n;
    for(; ystart != yend; ystart--, yptr--)
      {
      (void)memcpy((void *)ystart->line, (void *)yptr->line, size);
      }
    }
  else
    {
    if(n+win->_rows >= win->_cury) n = win->_cury - win->_rows + 1;
    ystart = win->_lines + win->_cury;
    yptr = win->_lines + win->_rows + n;
    yend = ystart - n;
    for(; ystart != yend; ystart++, yptr++)
      {
      (void)memcpy((void *)ystart->line, (void *)yptr->line, size);
      }
    }

  for(ch = ' ' | (win->_attr & A_ATTRIBUTES),
      xstart = yend->line,
      xend = xstart + win->_cols - 1;
      xstart != xend;
      xstart++)
    {
    *xstart = ch;
    }

  /* NOTE: ystart and yend below are reversed in meaning!! */
  if(n > 0)
    {
    ystart = win->_lines + win->_cury + n - 1;
    yptr = yend + 1;
    for(; ystart != yend; ystart++, yptr++)
      {
      (void)memcpy((void *)yptr->line, (void *)yend->line, size);
      }
    }
  else
    {
    ystart = win->_lines + win->_rows - 1;
    yptr = yend - 1;
    for(; ystart != yend; ystart--, yptr--)
      {
      (void)memcpy((void *)yptr->line, (void *)yend->line, size);
      }
    }

  win->_flags |= F_INSERTED;
  return(touchline(win, win->_cury, win->_rows - win->_cury));
}
