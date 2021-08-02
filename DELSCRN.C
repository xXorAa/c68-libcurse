#include <stdlib.h>
#include "curses.h"
#include "screen.h"

/*AT&T
AT&T This routine frees the storage associated with the SCREEN
AT&T data structure.
AT*T */

void
delscreen(SCREEN *sp)
{
  (void) delwin(sp->_physcr);
  (void) delwin(sp->_slkscr);
  free((void *)sp->_keys);
  free((void *)sp->_slk_labels);
  free((void *)sp->_chars);
#ifdef A_ALTCHARSET
  free((void *)sp->_acs_char);
#endif
  free((void *)sp);
}
