#include "curses.h"
#include "privfunc.h"
#include "window.h"

/*AT&T
AT&T The terminal is placed out of RAW mode.  RAW mode is similar to
AT&T CBREAK mode, in that characters typed are immediately passed
AT&T through to the user program:  however, in RAW mode, the interrupt,
AT&T quit, suspend and flow-control characters are passed through
AT&T uninterpreted, instead of generating a signal as they do in
AT&T CBREAK mode.  The behaviour of the BREAK key depends on other
AT&T bits in the tty driver that are not set by curses.
AT&T */

int
noraw(void)
{
  if(_termstate(-1,0,0) == ERR) return(ERR);
  curscr->_vmin = -1;
  curscr->_vtime = 0;
  return(OK);
}
