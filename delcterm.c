#include <stdlib.h>
#include "curses.h"
#include "term.h"

/*AT&T
AT&T oterm is of type TERMINAL *.  del_curterm() frees the space
AT&T pointed to by oterm and makes it available for further use.
AT&T If oterm is the same as cur_term, then references to any of
AT&T the terminfo boolean, numeric and string variables thereafter
AT&T may refer to invalid memory locations until another setupterm()
AT&T has been called.
AT&T */

int
del_curterm(TERMINAL *oterm)
{
  free((void *)oterm->_termdesc);
  /* free string table */
  free((void *)oterm->_string_starter);
  free((void *)oterm);
  return(OK);
}

