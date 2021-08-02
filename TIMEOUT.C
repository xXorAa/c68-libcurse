#include "curses.h"

/*AT&T
AT&T The |timeout()| routine sets blocking or non-blocking read for a
AT&T given window.  If |delay| is negative, blocking read is used (i.e.
AT&T waits indefinitely for input).  If |delay| is zero, then
AT&T non-blocking read is used (i.e. read returns ERR if no input is
AT&T waiting).. If |delay| is positive, then read blocks for |delay|
AT&T milliseconds, and return ERR if there is still no input.  Hence
AT&T this routine provides the same functionality as |nodelay()|, plus
AT&T the additional capability of being able to block for only |delay|
AT&T milliseconds (where |delay| is positive).
AT&T*/

void
timeout(int delay)
{
  wtimeout(stdscr,delay);
}
