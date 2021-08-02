#include "curses.h"

int
winsstr(WINDOW *win, char *str)
{
  return(winsnstr(win,str,-1));
}
