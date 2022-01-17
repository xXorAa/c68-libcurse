#include "curses.h"
#include "term.h"

/*AT&T
AT&T The beep() routine is used to signal the terminal user.  The
AT&T routine sounds the audible alarm on the terminal, if possible,
AT&T if that is not possible, it flashes the screen (visible bell),
AT&T if that is possible.  If neither signal is possible, nothing happens.
AT&T */

int
beep(void)
{
  if(bell) return putp(bell);
  else if(flash_screen) return putp(flash_screen);
  return(OK);
}
