#include "curses.h"
#include "term.h"
#include "window.h"

/*AT&T
AT&T This routine controls whether carriage return is translated to
AT&T newline on input by wgetch().  Initially translation is done.
AT&T Note that translation by the tty driver is disabled in CBREAK mode.
AT&T */

int
nonl(void)
{
  if(cur_term == 0) return(ERR);
  cur_term->_flags &= ~F_NL;
  return(OK);
}
