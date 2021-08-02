#include "curses.h"

int
wdeleteln(WINDOW *win)
{
  return(winsdelln(win,-1));
}
