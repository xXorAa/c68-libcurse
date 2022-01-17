#include "curses.h"

int
wclear(WINDOW *win)
{
  if(werase(win)==ERR) return(ERR);
  return(wrefresh(win));
}
