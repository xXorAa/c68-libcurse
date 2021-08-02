#include "curses.h"

int
mvgetstr(int y, int x, char *str)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(wgetnstr(stdscr, str, -1));
}
