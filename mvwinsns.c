#include "curses.h"

int
mvwinsnstr(WINDOW *win, int y, int x, char *str, int n)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(winsnstr(win,str,n));
}
