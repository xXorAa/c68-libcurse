#include "curses.h"

extern int _useenv;

/*AT&T
AT&T The use_env() routine, if used, is called before initscr() or
AT&T newterm() are called.  When called with FALSE as an argument,
AT&T the values of lines and columns specified in the terminfo database
AT&T will be used, even if environment variables LINES and COLUMNS
AT&T (used by default) are set, or if curses is running in a window
AT&T (in which case default behaviour would be to use the window size
AT&T if LINES and COLUMNS are not set).
AT&T */

void
use_env(bool bf)
{
  _useenv = bf;
}

