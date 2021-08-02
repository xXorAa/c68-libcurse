#include "curses.h"
#include "window.h"
#include "privfunc.h"

int
_gety(WINDOW *win)
{
  return(win->_cury);
}

int
_getx(WINDOW *win)
{
  return( win->_curx);
}

int
_getby(WINDOW *win)
{
  return(win->_begy);
}

int
_getbx(WINDOW *win)
{
  return( win->_begx);
}

int
_getmy(WINDOW *win)
{
  return(win->_rows);
}

int
_getmx(WINDOW *win)
{
  return( win->_cols);
}

int
_getpy(WINDOW *win)
{
  return((win->_parent)?(win->_begy - win->_parent->_begy):(-1));
}

int
_getpx(WINDOW *win)
{
  return((win->_parent)?(win->_begx - win->_parent->_begx):(-1));
}

