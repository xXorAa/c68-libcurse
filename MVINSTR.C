#include "curses.h"

int
mvinstr(int y, int x, char *str)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(winnstr(stdscr,str,-1));
}
