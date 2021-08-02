#include "curses.h"
#include "window.h"

/*AT&T
AT&T With the immedok routine, if enabled (bf is TRUE), any change in
AT&T the window image, such as the ones caused by waddch(), wclrobot(),
AT&T wscrl, etc., automatically cause a call to wrefresh().
AT&T However, it may degrade performance considerably, due to repeated
AT&T calls to wrefresh().  It is disabled by default.
AT&T */

void
immedok(WINDOW *win, bool bf)
{
  if(win == 0) return;
  if(bf) win->_flags |= F_IMMED;
  else win->_flags &= ~F_IMMED;
}
