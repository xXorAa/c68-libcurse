#include "curses.h"

chtype
mvinch(int y, int x)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(winch(stdscr));
}
