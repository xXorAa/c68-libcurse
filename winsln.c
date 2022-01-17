#include "curses.h"

int
winsertln(WINDOW *win)
{
  return(winsdelln(win,1));
}
