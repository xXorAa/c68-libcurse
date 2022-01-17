#include "curses.h"
#include "screen.h"
#include "window.h"

/*AT&T
AT&T The soft labels are cleared from the screen.
AT&T */

int
slk_clear(void)
{
  _LINE *ystart;
  chtype *xstart, *xend;
  chtype ch;

  if(_screen->_slkscr == 0) return(ERR);

  /* What colour should the slk line be drawn in? - I have choosen to
     do it in the same background that stdscr currently has. */
  ch = stdscr->_attr;
  ystart = curscr->_lines + curscr->_rows - 1;
  xstart = ystart->line;
  xend = xstart + curscr->_cols;
  for(; xstart != xend; xstart++)
    {
    *xstart = ch;
    }
  ystart->first = 0;
  ystart->last = curscr->_cols - 1;
  curscr->_flags |= F_DIRTY;
  return doupdate();  /* should the screen really be updated now ? */
}
