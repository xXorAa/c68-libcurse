#include "curses.h"
#include "window.h"

int
wstandout(WINDOW *win)
{
  if(win == 0) return(ERR);
  win->_attr = A_STANDOUT | (win->_attr & A_CHARTEXT);
  return(OK);
}
