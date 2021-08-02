#include "curses.h"
#include "term.h"
#include "screen.h"

/*AT&T
AT&T The |flushinp()| routine throws away any typeahead that has
AT&T been typed by the user and has not yet been read by the program.
AT&T
AT&T |flushinp()| always returns OK.
AT&T */

int
flushinp(void)
{
  if(_screen == 0) return(OK);

  (void)tcflush(fileno(_screen->_infd), TCIFLUSH);
  _screen->_chars_read = 0;
  return(OK);
}
