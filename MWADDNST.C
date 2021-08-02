#include "curses.h"

int
mvwaddnstr(WINDOW *win, int y, int x, char *s, int n)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(waddnstr(win,s,n));
}
