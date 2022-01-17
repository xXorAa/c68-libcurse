#include "curses.h"
#include "window.h"

/*AT&T
AT&T This routine enables curses to obtain information from the keypad
AT&T of the user's terminal.  If enabled, the user can press a function
AT&T key (such as an arrow key) and wgetch() will return a single value
AT&T representing the function key, as in KEY_LEFT.
AT&T If disabled, curses will not treat function keys specially, and the
AT&T program would have to interpret the escape sequences itself.
AT&T If the keypad in the terminal can be turned on (made to transmit),
AT&T calling keypad(win,TRUE) will turn it on.
AT&T */

int
keypad(WINDOW *win, bool bf)
{
  if(win == 0) return(ERR);
  if(bf) win->_flags |= F_KEYPAD;
  else win->_flags &= ~F_KEYPAD;
  return(OK);
}
