#include "curses.h"
#include "term.h"

/*AT&T
AT&T Instantiate the parameters into the given capability.
AT&T The output from this routine is to be passed to tputs().
AT&T */

char *
tgoto(char *cap, int col, int row)
{
  return(tparm(cap, (long)row, (long)col));
}
