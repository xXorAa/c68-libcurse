#include "curses.h"

int
mvwgetch(WINDOW *win, int y, int x)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(wgetch(win));
}
