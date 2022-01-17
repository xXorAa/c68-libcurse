#include "curses.h"
#include "window.h"

int
is_wintouched(WINDOW *win)
{
  return((win->_flags & F_DIRTY)==F_DIRTY);
}
