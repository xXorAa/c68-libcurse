#include <stdlib.h>
#include "curses.h"
#include "window.h"

/*AT&T
AT&T Delete the named window, freeing up all memory associated with it.
AT&T If you try to delete a main window before all of its subwindows
AT&T have been deleted, ERR will be returned.
AT&T */

int
delwin(WINDOW *win)
{
  if(win == 0 || win->_children != 0) return(ERR);
  if(win->_parent != 0) win->_parent->_children--;
  free((void *)win);
  return(OK);
}

