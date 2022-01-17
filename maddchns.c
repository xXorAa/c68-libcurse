#include "curses.h"

int
mvaddchnstr(int y, int x, chtype *chstr, int n)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(waddchnstr(stdscr,chstr,n));
}
