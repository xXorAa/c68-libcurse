#include "curses.h"
#include "screen.h"

/*AT&T
AT&T This routine is used to switch between different terminals.
AT&T The screen reference new becomes the new current terminal.
AT&T A pointer to the screen of the previous terminal is returned
AT&T by the routine. This is the only routine which manipulates SCREEN
AT&T pointers; all other routines affect only the current terminal.
AT&T */

SCREEN *
set_term(SCREEN *new)
{
  SCREEN *old = _screen;
  _screen = new;
#ifdef A_ALTCHARSET
  _acs_ch = _screen->_acs_char;
#endif
  return(old);
}
