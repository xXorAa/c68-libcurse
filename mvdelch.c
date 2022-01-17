#include "curses.h"

int
mvdelch(int y, int x)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(wdelch(stdscr));
}
