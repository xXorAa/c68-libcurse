#include "curses.h"
#include "window.h"

chtype
winch(WINDOW *win)
{
  return(win->_lines[win->_cury].line[win->_curx]);
}
