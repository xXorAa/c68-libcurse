#include "curses.h"
#include "privfunc.h"
#include "window.h"

/*AT&T
AT&T The |halfdelay()| routine is used for half-delay mode, which is similar
AT&T to |cbrak()| mode in that characters types by the user are immediately
AT&T available to the program.  However, after blocking for |tenths| tenths
AT&T of seconds, ERR is returned if nothing has been typed.  The value of
AT&T |tenths| must be a number between 1 and 255.  Use |nocbreak()| to
AT&T leave half-delay mode.
AT&T*/

int
halfdelay(int tenths)
{
  if(_termstate(1,tenths,0) == ERR) return(ERR);
  curscr->_vmin = 1;
  curscr->_vtime = tenths;
  return(OK);
}
