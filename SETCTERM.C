#include "curses.h"
#include "term.h"

/*AT&T
AT&T set_curterm() sets the variable cur_term to nterm,
AT&T and makes all of the terminfo boolean, numeric and string
AT&T variables use the values from nterm.
AT&T */

int
set_curterm(TERMINAL *nterm)
{
  cur_term = nterm;
  return(OK);
}
