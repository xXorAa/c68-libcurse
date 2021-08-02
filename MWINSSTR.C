#include "curses.h"

int
mvwinsstr(WINDOW *win, int y, int x, char *str)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(winsnstr(win,str,-1));
}
