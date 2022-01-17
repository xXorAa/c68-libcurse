#include "curses.h"

int
mvwinsch(WINDOW *win, int y, int x, chtype ch)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(winsch(win,ch));
}
