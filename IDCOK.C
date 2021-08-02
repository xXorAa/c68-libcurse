#include "curses.h"
#include "window.h"

void
idcok(WINDOW *win, bool bf)
{
  if(win==0) return;
  if(bf) win->_flags |= F_IC;
  else win->_flags &= ~F_IC;
}
