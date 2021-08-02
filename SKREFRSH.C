#include "curses.h"

/*AT&T
AT&T This routine corresponds to the routine wrefresh().
AT&T */

int
slk_refresh(void)
{
  if(slk_noutrefresh() == ERR) return(ERR);
  return(doupdate());
}
