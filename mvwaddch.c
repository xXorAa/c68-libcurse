#include "curses.h"

int
mvwaddch(WINDOW *win, int y, int x, chtype ch)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(waddch(win,ch));
}
