#include "curses.h"

int
mvinchstr(int y, int x, chtype *chstr)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(winchnstr(stdscr,chstr,-1));
}
