#include "curses.h"

int
touchwin(WINDOW *win)
{
  return(wtouchln(win,0,-1,1));
}
