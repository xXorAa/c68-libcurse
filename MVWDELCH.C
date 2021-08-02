#include "curses.h"

int
mvwdelch(WINDOW *win, int y, int x)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(wdelch(win));
}
