#include "curses.h"
#include "term.h"

#ifdef A_COLOR
/*AT&T
AT&T This routine allows users to find out what colours a given
AT&T colour-pair consists of.  It requires three arguments the
AT&T colour-pair number, and two addresses of shorts for storing
AT&T the foreground and the background colour numbers.  The value
AT&T of the first argument must be between 1 and COLOR_PAIRS-1.
AT&T The values that will be stored at the addresses pointed to by the
AT&T second and third arguments will be between 0 and COLORS-1.
AT&T The routine returns ERR if the colour-pair has not been
AT&T initialised, OK otherwise.
AT&T */

int
pair_content(int pair, short *fptr, short *bptr)
{
  PAIR *pptr;

  if(cur_term->_colour_pairs == 0 || fptr == 0 || bptr == 0 ||
     (pair<1 || pair>=COLOR_PAIRS))
    return(ERR);

  pptr = cur_term->_colour_pairs + pair;
  *fptr = pptr->fg;
  *bptr = pptr->bg;
  return(OK);
}
#endif
