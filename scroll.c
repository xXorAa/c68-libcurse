#include "curses.h"

int
scroll(WINDOW *win)
{
  return(wscrl(win,1));
}
