#include "curses.h"
#include "term.h"

/*AT&T
AT&T TRUE if the terminal has insert- and delete-line capabilities,
AT&T or can simulate them using scrolling regions.
AT&T This might be used to check to see if it would be appropriate
AT&T top turn on physical scrolling using scrollok() or idlok().
AT&T */

int
has_il(void)
{
  return(insert_line != (char *)0 && delete_line != (char *)0);
}

