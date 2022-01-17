#include <string.h>
#include "term.h"

/*AT&T
AT&T The value -2 is returned if capname is not a numeric capability.
AT&T The value -1 is returned if capname is not defined for the terminal.
AT&T */

int
tigetnum(char *capname)
{
  char **p;
  for(p = numnames; *p && strcmp(*p, capname); p++) {}
  return(*p ? *(&(cur_term->_numeric_starter)+(p-numnames)+1) : -2);
}
