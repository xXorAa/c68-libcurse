#include "curses.h"
#include "screen.h"

/*AT&T
AT&T The routine isendwin() returns TRUE if endwin() has been called
AT&T without any subsequent calls to wrefresh(), and FALSE otherwise.
AT&T */

int
isendwin(void)
{
  return(_screen ? _screen->_state == SHELL_STATE : TRUE);
}
