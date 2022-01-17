#include "curses.h"
#include "window.h"

int
wattron(WINDOW *win, chtype attrs)
{
  if(win == 0) return(ERR);
  win->_attr |= (attrs & A_ATTRIBUTES);
  return(OK);
}
