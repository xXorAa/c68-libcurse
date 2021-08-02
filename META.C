#include "curses.h"
#include "term.h"

/*AT&T
AT&T Initially, whether the terminal returns 7 or 8 significant bits
AT&T on input depends on the control mode of the tty driver.
AT&T To force 8 bits to be returned, invoke meta(win,TRUE).
AT&T To force 7 bits to be returned, invoke meta(win,FALSE).
AT&T The window argument, win, is always ignored.
AT&T */

int
meta(WINDOW *win, bool bf)
{
  win = win;
  return putp(bf ? meta_on : meta_off);
}
