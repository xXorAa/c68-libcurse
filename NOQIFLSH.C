#include "curses.h"
#include "term.h"

/*AT&T
AT&T When the |noqiflush()| routine is used, normal flush of input
AT&T and output ques associated with the INTR, QUIT and SUSP characters
AT&T will not be done.
AT&T */

void
noqiflush(void)
{
  cur_term->_prog_mode.c_lflag |= NOFLSH;
  (void) tcsetattr(cur_term->_outfd, TCSADRAIN, &cur_term->_prog_mode);
}
