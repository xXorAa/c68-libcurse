#include "curses.h"

int
untouchwin(WINDOW *win)
{
  return(wtouchln(win,0,-1,0));
}
