#include <string.h>
#include "curses.h"
#include "term.h"

/*AT&T
AT&T Get the numeric entry for codename.
AT&T */

int
tgetnum(char *codename)
{
  char **p;
  for(p = numcodes; *p && strcmp(*p, codename); p++) {}
  return (*p ? *(&(cur_term->_numeric_starter)+(p-numcodes)+1) : -2);
}
