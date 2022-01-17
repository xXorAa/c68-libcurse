#include <unistd.h>
#include <termios.h>
#include "curses.h"
#include "term.h"

/*AT&T
AT&T If this option is enabled, when an intrupt key is pressed on the
AT&T keyboard (interupt, break, quit), all output in the tty driver
AT&T queue will be flushed, giving the effect of faster response to
AT&T the interrup, but causing curses to have the wrong idea of what
AT&T is on the screen.
AT&T Disabling the option prevents the flush.
AT&T The default for the option is inherited from the tty driver settings.
AT&T The window argument is ignored.
AT&T */

int
intrflush(WINDOW *win, bool bf)
{
  if(cur_term == 0) return(ERR);
  if(bf)
    cur_term->_prog_mode.c_lflag &= ~NOFLSH;
  else
    cur_term->_prog_mode.c_lflag |= NOFLSH;
  if(tcsetattr(cur_term->_outfd,TCSADRAIN,&cur_term->_prog_mode) != 0) return(ERR);
  return(OK);
}
