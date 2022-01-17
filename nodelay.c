#include "curses.h"
#include "window.h"

/*AT&T
AT&T The |nodelay()| option causes |getch()| to be a non-blocking call.
AT&T If no input is ready, |getch()| return ERR.  If disabled (|bf| is
AT&T FALSE), |getch()| waits until a key is pressed.
AT&T*/

int
nodelay(WINDOW *win, bool bf)
{
  win->_vmin = 1;
  win->_vtime = (bf)?0:255;
  return(OK);
}
