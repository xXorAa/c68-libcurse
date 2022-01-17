#include <string.h>
#include "curses.h"
#include "term.h"

/*AT&T
AT&T Get the boolean entry for codename.
AT&T */

int
tgetflag(char *codename)
{
  char **p;
  for(p = boolcodes; *p && strcmp(*p, codename); p++) {}
  return (*p ? *(&(cur_term->_bool_starter)+(p-boolcodes)+1) : -1);
}
