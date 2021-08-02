#include "curses.h"
#include "privfunc.h"
#include "window.h"

/*AT&T
AT&T The terminal is placed into CBREAK mode.  CBREAK mode is similar
AT&T to RAW mode, in that characters typed are immediately passed through
AT&T to the user program:  however, in CBREAK mode, the interrupt, quit,
AT&T suspend and flow-control characters are not passed through
AT&T uninterpreted, instead they  generate a signal.
AT&T */

int
cbreak(void)
{
  if(_termstate(1,0,0) == ERR) return(ERR);
  curscr->_vmin = 1;
  curscr->_vtime = 0;
  return(OK);
}
