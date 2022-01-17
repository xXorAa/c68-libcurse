#include "curses.h"
#include "window.h"

int
wattrset(WINDOW *win, chtype attrs)
{
  if(win == 0) return(ERR);
  win->_attr = (attrs & A_ATTRIBUTES) | (win->_attr & A_CHARTEXT);
  return(OK);
}
