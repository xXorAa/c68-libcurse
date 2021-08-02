#include "curses.h"

int
mvaddnstr(int y, int x, char *s, int n)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(waddnstr(stdscr,s,n));
}
