#include "curses.h"

/*AT&T
AT&T The soft labels are restored to the screen after a slk_clear().
AT&T */

int
slk_restore(void)
{
  if(slk_touch()==ERR) return(ERR);
  return(slk_refresh());
}
