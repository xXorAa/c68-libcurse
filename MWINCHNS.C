#include "curses.h"

int
mvwinchnstr(WINDOW *win, int y, int x, chtype *chstr, int n)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(winchnstr(win,chstr,n));
}
