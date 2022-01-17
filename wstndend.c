#include "curses.h"
#include "window.h"

int
wstandend(WINDOW *win)
{
  if(win == 0) return(ERR);
  win->_attr = A_NORMAL | (win->_attr & A_CHARTEXT);
  return(OK);
}
