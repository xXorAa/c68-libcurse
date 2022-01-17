#include "curses.h"
#include "window.h"

int
wattroff(WINDOW *win, chtype attrs)
{
  if(win == 0) return(ERR);
  win->_attr &= ((~attrs) & A_ATTRIBUTES) | (~A_ATTRIBUTES);
  return (OK);
}
