#include "curses.h"

int
mvwinstr(WINDOW *win, int y, int x, char *str)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(winnstr(win,str,-1));
}
