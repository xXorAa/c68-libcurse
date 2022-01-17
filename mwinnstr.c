#include "curses.h"

int
mvwinnstr(WINDOW *win, int y, int x, char *str, int n)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(winnstr(win,str,n));
}
