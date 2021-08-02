#include "curses.h"

int
mvgetch(int y, int x)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(wgetch(stdscr));
}
