#include "curses.h"
#include "term.h"
#include "privfunc.h"

/*AT&T
AT&T The def_prog_mode() routine saves the current terminal
AT&T modes as the "program" (in curses) state.
AT&T */

int
def_prog_mode(void)
{
  return( tcgetattr(0,&cur_term->_prog_mode) );
}
