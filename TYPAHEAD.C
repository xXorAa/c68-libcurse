#include "curses.h"
#include "screen.h"

/*AT&T
AT&T Curses does "line-breakout optimisation" by looking for typeahead
AT&T periodically while updating the screen.
AT&T If input is found, and it is coming from a tty, the current update
AT&T will be postponed until wrefresh() or doupdate() is called again.
AT&T This allows faster response to commands typed in advance.
AT&T Normally, the file descriptor for the input FILE pointer passed
AT&T to newterm() , or stdin in the case that initscr() was used, will
AT&T be used to do this typeahead checking.
AT&T The typeahead() routine specifies that the file descriptor fildes
AT&T is to be used to check for typeahead instead.
AT&T If fildes is -1, then no typeahead checking will be done.
AT&T
AT&T Note that fildes is a file descriptor, not a <stdio.h> FILE pointer.
AT&T */

int
typeahead(int fildes)
{
  if(_screen == 0) return(ERR);
  _screen->_typeahead = fildes;
  return(OK);
}
