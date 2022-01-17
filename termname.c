#include "curses.h"
#include "term.h"

/*AT&T
AT&T The termname() routine returns the value of the environment
AT&T variable TERM (truncated to 14 characters).
AT&T */

char *
termname(void)
{
  return(&cur_term->termname[0]);
}
