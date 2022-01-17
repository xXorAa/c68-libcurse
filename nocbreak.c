#include "curses.h"
#include "privfunc.h"
#include "window.h"

/*AT&T
AT&T This routine puts the terminal into NOCBREAK mode.  In NOCBREAK
AT&T mode, the tty driver will buffer characters typed until a newline
AT&T or carriage returns is typed. Interrupt and flow-control characters
AT&T are unaffected by this mode.
AT&T */

int
nocbreak(void)
{
  if(_termstate(-1,0,0) == ERR) return(ERR);
  curscr->_vmin = -1;
  curscr->_vtime = 0;
  return(OK);
}
