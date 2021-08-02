#include "curses.h"

int
touchline(WINDOW *win, int y, int n)
{
  return(wtouchln(win,y,n,1));
}
