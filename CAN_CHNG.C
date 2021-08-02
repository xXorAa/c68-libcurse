#include "curses.h"
#include "term.h"
/*AT&T
AT&T The can_change_color() routine requires no arguments.
AT&T It returns TRUE if the terminal supports colours and can
AT&T change their definitions; otherwise it returns FALSE.
AT&T */

bool
can_change_color(void)
{
  if(can_change) return(TRUE);
  return(FALSE);
}
