#include "curses.h"

int
winstr(WINDOW *win, char *str)
{
  return(winnstr(win,str,-1));
}
