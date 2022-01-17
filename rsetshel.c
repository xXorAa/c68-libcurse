#include "curses.h"
#include "term.h"
#include "privfunc.h"


/*AT&T
AT&T The reset_shell_mode() routine restores the current terminal
AT&T modes as the "shell" (not in curses) state.
AT&T */

int
reset_shell_mode(void)
{
  return( tcsetattr(0, TCSADRAIN, &cur_term->_shell_mode) );
}
