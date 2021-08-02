#include "curses.h"

int
mvwaddchnstr(WINDOW *win, int y, int x, chtype *chstr, int n)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(waddchnstr(win,chstr,n));
}
