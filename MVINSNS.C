#include "curses.h"

int
mvinsnstr(int y, int x, char *str, int n)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(winsnstr(stdscr,str,n));
}
