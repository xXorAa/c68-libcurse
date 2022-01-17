#include "curses.h"

int
werase(WINDOW *win)
{
  (void) wmove(win,0,0);
  return(wclrtobot(win));
}
