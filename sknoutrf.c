#include "curses.h"
#include "screen.h"

/*AT&T
AT&T This routine corresponds to the routine wnoutrefresh().
AT&T */

int
slk_noutrefresh(void)
{
  return(wnoutrefresh(_screen->_slkscr));
}
