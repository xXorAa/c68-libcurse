#include "curses.h"

extern int _filter;

/*AT&T
AT&T The filter routine, if used, is called before initscr() or newterm()
AT&T are called.  It makes curses think that there is a one-line screen,
AT&T curses does not use any terminal capabilities that assume that they
AT&T know on what line of the screen the cursor is positioned.
AT&T */

int
filter(void)
{
  _filter = TRUE;
  return(OK);
}
