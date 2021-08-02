#include "curses.h"

int
mvwinchstr(WINDOW *win, int y, int x, chtype *chstr)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(winchnstr(win,chstr,-1));
}
