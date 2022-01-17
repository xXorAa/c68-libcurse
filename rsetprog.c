#include "curses.h"
#include "term.h"
#include "privfunc.h"

/*AT&T
AT&T The reset_prog_mode() routine resets the current terminal
AT&T modes as the "program" (in curses) state.
AT&T */

int
reset_prog_mode(void)
{
  return( tcsetattr(0, TCSADRAIN, &cur_term->_prog_mode));
}
