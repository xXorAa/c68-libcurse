#include "curses.h"
#include "term.h"


/*AT&T
AT&T The flash() routine is used to signal the terminal user.  The routine
AT&T flashes the screen (visible bell), and if that is not possible,
AT&T sounds the audible alarm on the terminal, if possible.
AT&T If neither signal is possible, nothing happens.
AT&T */

int
flash (void)
{
  if(flash_screen) return putp(flash_screen);
  else if(bell) return putp(bell);
  return(OK);
}
