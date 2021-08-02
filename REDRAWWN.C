#include "curses.h"

int
redrawwin(WINDOW *win)
{
  if(touchwin(win)==ERR) return(ERR);
  return(wrefresh(win));
}
