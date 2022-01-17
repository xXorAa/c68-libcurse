#include "curses.h"
#include "window.h"

int
syncok(WINDOW *win, bool bf)
{
  if(win==0) return(ERR);
  if(bf) win->_flags |= F_SYNC;
  else win->_flags &= ~F_SYNC;
  return(OK);
}
