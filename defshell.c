#include "curses.h"
#include "term.h"
#include "privfunc.h"

/*AT&T
AT&T The def_shell_mode() routine saves the current terminal
AT&T modes as the "shell" (not in curses) state.
AT&T */

int
def_shell_mode ()
{
  return( tcgetattr(0, &cur_term->_shell_mode) );
}
