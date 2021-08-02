#include "curses.h"
#include "term.h"
#include "window.h"

/*AT&T
AT&T This routine controls whether characters typed by the user are
AT&T echoed by wgetch() as they are typed.
AT&T Echoing by the tty driver is always disabled, but initially wgetch()
AT&T is in ECHO mode , so characters typed are echoed.
AT&T */

int
echo(void)
{
  if(cur_term == 0) return(ERR);
  cur_term->_flags |= F_ECHO;
  return(OK);
}
