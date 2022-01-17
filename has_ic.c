#include "curses.h"
#include "term.h"

/*AT&T
AT&T TRUE if the terminal has insert- and delete-character capabilities.
AT&T */

int
has_ic(void)
{
  return(insert_character != (char *)0 && delete_character != (char *)0);
}
