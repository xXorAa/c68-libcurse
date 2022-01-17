#include "curses.h"

chtype
mvwinch(WINDOW *win, int y, int x)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(winch(win));
}
