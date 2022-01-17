#include "curses.h"
#include "window.h"

int
scrollok(WINDOW *win, bool bf)
{
  if(win==0) return(ERR);
  if(bf) win->_flags |= F_SCROLL;
  else win->_flags &= ~F_SCROLL;
  return(OK);
}
