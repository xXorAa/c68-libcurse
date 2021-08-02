#include "curses.h"
#include "term.h"
#include "privfunc.h"

/*AT&T
AT&T The savetty() routine saves the state of the terminal modes
AT&T in a buffer.
AT&T */

int
savetty(void)
{
  return( tcgetattr(0, &_tty_state) );
}
