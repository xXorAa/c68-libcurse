#include <string.h>
#include "term.h"

/*AT&T
AT&T The value of -1 is returned if capname is not a boolean capability.
AT&T The value 0 is returned if capname is not defined for this terminal.
AT&T */

int
tigetflag(char *capname)
{
  char **p;
  for(p = boolnames; *p && strcmp(*p, capname); p++) {}
  return(*p ? *(&(cur_term->_bool_starter)+(p-boolnames)+1) : -1);
}
