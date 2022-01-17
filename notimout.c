#include "curses.h"
#include "window.h"

int
notimeout(WINDOW *win, bool bf)
{
  if(bf) win->_flags &= ~F_TIMEOUT;
  else win->_flags |= F_TIMEOUT;
  return(OK);
}
