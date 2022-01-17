#include "term.h"

/*AT&T
AT&T Similar to setupterm(), except that it is called after restoring
AT&T memory to a previous state; for example, after a call to scr_restore().
AT&T It assumes that the windows and the input and output options are the
AT&T same as when memory was saved, but the terminal type and baud rate
AT&T may be different.
AT&T */

int
restartterm(char *term, int fildes, int *errret)
{
  return(setupterm(term, fildes, errret));
}
