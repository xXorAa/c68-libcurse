#include "curses.h"

int
winchstr(WINDOW *win, chtype *chstr)
{
  return(winchnstr(win,chstr,-1));
}
