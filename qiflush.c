#include <unistd.h>
#include <termios.h>
#include "curses.h"
#include "term.h"
#include "screen.h"

/*AT&T
AT&T When |qiflush()| is called, the ques will be flushed when the
AT&T control characters INTR, QUIT and SUSP are read.
AT&T */

void
qiflush(void)
{
  cur_term->_prog_mode.c_lflag &= ~NOFLSH;
  (void) tcsetattr(cur_term->_outfd, TCSADRAIN, &cur_term->_prog_mode);
}
