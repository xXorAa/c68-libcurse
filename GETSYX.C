#include "curses.h"
#include "screen.h"
#include "window.h"
#include "privfunc.h"

int
_getsy(void)
{
  WINDOW *physcr = _screen->_physcr;
  return( (physcr->_flags & F_LEAVE)?(-1):physcr->_cury);
}

int
_getsx(void)
{
  WINDOW *physcr = _screen->_physcr;
  return( (physcr->_flags & F_LEAVE)?(-1):physcr->_curx);
}

