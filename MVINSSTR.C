#include "curses.h"

int
mvinsstr(int y, int x, char *str)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(winsnstr(stdscr,str,-1));
}
