#include "curses.h"

int
box(WINDOW *win, chtype v, chtype h)
{
  return(wborder(win,v,v,h,h,(chtype)0,(chtype)0,(chtype)0,(chtype)0));
}
