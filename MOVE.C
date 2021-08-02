#include "curses.h"

/*AT&T
AT&T The cursor associated with the window is moved to line (row) y,
AT&T column x.  This does not move the physical cursor of the terminal
AT&T until wrefresh() is called.  The position specified is relative to
AT&T the upper left corner of the window, which is (0,0).
AT&T */

int
move(int y, int x)
{
  return(wmove(stdscr,y,x));
}
