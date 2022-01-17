#include "curses.h"

int
mvwgetstr(WINDOW *win, int y, int x, char *str)
{
  if(wmove(win,y,x)==ERR) return(ERR);
  return(wgetnstr(win, str, -1));
}
