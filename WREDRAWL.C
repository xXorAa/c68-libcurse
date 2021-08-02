#include "curses.h"
#include "window.h"

/*AT&T
AT&T The routine redrawln() routine indicates to curses that some
AT&T screen lines are corrupted and should be thrown away before
AT&T anything is written over them.  This routine could be used for
AT&T programs such as editors, which want a command to redraw somepart
AT&T of the screen.
AT&T */

int
wredrawln(WINDOW *win, int beg_line, int num_lines)
{
  if(win == 0) return(ERR);
  return(touchline(curscr, win->_begy + beg_line, num_lines));
}
