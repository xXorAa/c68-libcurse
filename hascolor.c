#include "curses.h"

#ifdef A_COLOR
/*AT&T
AT&T This routine requires no arguments.  It returns TRUE if the
AT&T terminal can manipulate colors, FALSE otherwise.
AT&T This routine facilitates writing terminal-independent
AT&T programs.  For example, a programmer can use it to decide whether
AT&T to use a colour or some other video attribute.
AT&T */

bool
has_colors(void)
{
  return(COLORS && COLOR_PAIRS ? TRUE : FALSE);
}
#endif
