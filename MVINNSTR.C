#include "curses.h"

int
mvinnstr(int y, int x, char *str, int n)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(winnstr(stdscr,str,n));
}
