#include <string.h>
#include "curses.h"
#include "term.h"

/*AT&T
AT&T Return the string for codename,  If area is not NULL, then also
AT&T store it in the buffer pointed to by area and advance area.
AT&T tputs () should be used to output the returned string.
AT&T */

char *
tgetstr(char *codename, char **area)
{
  char **p, **pptr, *s;

  for(p = strcodes; *p && strcmp(*p, codename); p++) {}

  pptr = &cur_term->_string_starter;
  s = (*p ? *(pptr + (p-strcodes) + 1) : (char *) 0);
  if(s && area) {(void)strcpy(*area, s); *area += strlen(s);}
  return(s);
}
