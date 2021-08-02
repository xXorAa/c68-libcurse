#include "curses.h"
#include "screen.h"

/*AT&T
AT&T This routine corresponds to wattroff().
AT&T */

int
slk_attroff(chtype attr)
{
  return(wattroff(_screen->_slkscr,attr));
}
