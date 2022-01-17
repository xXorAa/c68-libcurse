#include "curses.h"
#include "window.h"
#include "term.h"
#include "screen.h"

/*AT&T
AT&T This routine is equivalent to wechochar() but for pads.
AT&T The last location of the pad ob the screen is reused for
AT&T the arguments to prefresh().
AT&T */

int
pechochar(WINDOW *pad, chtype ch)
{
  WINDOW *physcr;
  chtype *chptr;
  int y, x;

  if(pad == 0) return(ERR);

  if(pad->_flags & F_DIRTY || curscr->_flags & F_DIRTY)
    {
    /* There are some other changes which also need to */
    /* be written out. */
    return(waddch(pad, ch) == ERR ? ERR :
           prefresh(pad, 0, 0,
                    pad->_begy, pad->_begx, pad->_rows, pad->_cols));
    }

  pad->_lines[y=pad->_cury].line[x=pad->_curx++] = ch;
  if(x > curscr->_cols) {x = 0; pad->_cury++;}
  y += pad->_begy;
  x += pad->_begx;
  chptr = &curscr->_lines[y].line[x];
  physcr = _screen->_physcr;
  physcr->_lines[y].line[x] = *chptr = ch;
  (void)mvcur(physcr->_cury, physcr->_curx, y, x);
  physcr->_cury = y;
  physcr->_curx = x;
  (void)vidattr(ch & A_ATTRIBUTES);
  putchar((int) (ch & A_CHARTEXT));
  (void)fflush(stdout);

  return(OK);
}
