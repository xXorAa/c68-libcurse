#include "curses.h"
#include "screen.h"

/*AT&T
AT&T This routine corresponds to wattrset().
AT&T */

int
slk_attrset(chtype attr)
{
  return(wattrset(_screen->_slkscr,attr));
}
