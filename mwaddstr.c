#include "curses.h"

int
mvwaddstr(WINDOW *win, int y, int x, char *s)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(waddstr(win,s));
}
