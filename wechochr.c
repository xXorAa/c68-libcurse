#include "curses.h"
#include "term.h"
#include "screen.h"
#include "window.h"
#include <ctype.h>

/*AT&T
AT&T This routine is functionally equivalent to a call to waddch()
AT&T followed by a call to wrefresh().  The knowledge that only a
AT&T single character is being output is taken  into consideration
AT&T and, for non-control characters, a conciderable performance gain
AT&T can be seen by using this routine instead of their equivalents.
AT&T */

int
wechochar(WINDOW *win, chtype ch)
{
  int c, curx, cury;
  int y, x;

  if(win == 0) return(ERR);

  if(win->_flags & F_DIRTY || curscr->_flags & F_DIRTY)
    {
    /* There are some other changes which also need to be written out */
    return(waddch(win, ch) == ERR ? ERR : wrefresh(win));
    }

  curx = win->_curx;
  cury = win->_cury;

  switch(c = (ch & A_CHARTEXT))
    {
  case '\t' :
      {
      ch = 0;
      for(; ((curx+1)%8)!=0; curx++) {}
      break;
      }
  case '\r' :
      {
      ch = 0;
      curx = -1;
      break;
      }
  case '\b' :
      {
      ch = 0;
      curx -= 2;
      break;
      }
  case ' ' :
      {
      ch = (win->_attr & A_CHARTEXT) | (ch & A_ATTRIBUTES);
      break;
      }
  default :
      if(!iscntrl(c)) break;
      /*FALLTROUGH*/
  case '\n' :
      return(waddch(win, ch) == ERR ? ERR : wrefresh(win));
    }

  y = cury + win->_begy;
  x = curx + win->_begx;

  if(ch != 0)
    {
    WINDOW *physcr = _screen->_physcr;
    win->_lines[cury].line[curx] = ch;
    curscr->_lines[y].line[x] = ch;
/*IMB check that the following works after ripoffline()*/
    physcr->_lines[y].line[x] = ch;
    (void)mvcur(physcr->_cury, physcr->_curx, y, x);
    physcr->_cury = y;
    physcr->_curx = x;
    (void)vidattr(ch & A_ATTRIBUTES);
    putchar ((int) (ch & A_CHARTEXT));
    }

  win->_curx = curx + 1;
  win->_cury = cury;
  if(win->_curx > win->_cols)
    {
    win->_curx = 0;
    win->_cury++;
    if(win->_cury > win->_bot)
      {
      if(win->_flags & F_SCROLL)
        {
        (void)wscrl(win,1);
        (void)wrefresh(win);
        }
      win->_cury--;
      }
    (void)mvcur(-1, -1, win->_begy+win->_cury, win->_begx+win->_curx);
    }

  (void)fflush(_screen->_outfd);
  return(OK);
}
