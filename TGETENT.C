#include "curses.h"
#include "term.h"

/*AT&T
AT&T Look up termcap entry for name.
AT&T The emulation ignores the buffer pointer bp.
AT&T */

int
tgetent(char *bp, char *name)
{
  int errret;
  bp = bp;
  (void)setupterm(name, 0, &errret);
  return(errret);
}
