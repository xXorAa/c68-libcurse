#include "curses.h"
#include "screen.h"

/*AT&T
AT&T All of the soft labels are forced to be output the next
AT&T time a slk_noutrefresh() is performed.
AT&T */

int
slk_touch(void)
{
  return(touchwin(_screen->_slkscr));
}

