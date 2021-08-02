#include <stdio.h>
#include "term.h"

#ifdef putchar
#undef putchar		/* must use the library routine not a macro */
#endif

/*AT&T
AT&T This routine is similar to vidputs() but characters are
AT&T passed through putchar().
AT&T */

int
vidattr(chtype attr)
{
  return(vidputs(attr , putchar));
}
