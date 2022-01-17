#include "curses.h"

int
mvinchnstr(int y, int x, chtype *chstr, int n)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(winchnstr(stdscr,chstr,n));
}
