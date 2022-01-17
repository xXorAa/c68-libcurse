#include "curses.h"

/*AT&T
AT&T The routine wrefresh() copies the named window to the physical
AT&T terminal screen, taking into account what is already there
AT&T in order to do optimisations.
AT&T */

int
wrefresh(WINDOW *win)
{
  return(wnoutrefresh(win) == ERR ? ERR : doupdate());
}
