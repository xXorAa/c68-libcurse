#include "curses.h"
#include "screen.h"

/*AT&T
AT&T The current label for label number labnum is returned,
AT&T in the same format as it was in when it was passed to slk_set();
AT&T that is, how it looked prior to being justified according to the
AT&T labfmt argument of slk_set().
AT&T */

char *
slk_label(int labnum)
{
  if(labnum<1 || labnum>8) return((char *)0);
  return(&_screen->_slk_labels[(labnum-1)*9]);
}
