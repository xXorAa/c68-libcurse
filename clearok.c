#include "curses.h"
#include "window.h"

int
clearok(WINDOW *win, bool bf)
{
  if(bf) win->_flags |= F_CLEAR;
  else win->_flags &= (~F_CLEAR);
  return(OK);
}
