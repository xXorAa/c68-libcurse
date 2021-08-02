#include "curses.h"

int
mvaddstr(int y, int x, char *s)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(waddstr(stdscr,s));
}
