#include <string.h>
#include "term.h"

/*AT&T
AT&T The value (char *) -1 is returned if capname is not a string capability.
AT&T A null value is returned if capname is not defined for this terminal.
AT&T */

char *
tigetstr(char *capname)
{
  char **p;
  for(p = strnames; *p && strcmp (*p, capname); p++) {}
  return(*p ? *(&(cur_term->_string_starter)+(p-strnames)+1) : (char*)(-1));
}
