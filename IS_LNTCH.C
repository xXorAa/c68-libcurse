#include "curses.h"
#include "window.h"

int
is_linetouched(WINDOW *win, int y)
{
  if(y < 0 || y > win->_rows) return(ERR);
  return(win->_lines[y].first != FIRST_NOT_CHANGED);
}
