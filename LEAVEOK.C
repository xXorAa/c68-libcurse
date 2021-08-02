#include "curses.h"
#include "window.h"

int
leaveok(WINDOW *win, bool bf)
{
  if(win==0) return(ERR);
  if(bf) win->_flags &= ~F_LEAVE;
  else win->_flags |= F_LEAVE;
  return(OK);
}
