#include <stdio.h>
#include "term.h"

#ifdef putchar
#undef putchar		/* must use the library routine and not a macro!! */
#endif

/*AT&T
AT&T This routine writes a character to the terminal.
AT&T */

int
putp(char *str)
{
  return(tputs(str, 1, putchar));
}
