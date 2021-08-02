#include "curses.h"

int
mvinsch(int y, int x, chtype ch)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(winsch(stdscr,ch));
}
