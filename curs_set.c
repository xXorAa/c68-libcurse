#include "curses.h"
#include "term.h"
#include "screen.h"

/*AT&T
AT&T The cursor state is set to invisible, normal, or very visible
AT&T for visibility set to 0, 1 or 2.  If the termial supports the
AT&T visibility requested, the previous cursor state is returned,
AT&T otherwise ERR is returned.
AT&T */

int
curs_set(int visibility)
{
  int prev_state;

  if((prev_state = _screen->_cursor_state) != visibility)
    {
    switch(visibility)
      {
    case 0 :
      if(cursor_invisible) (void)putp(cursor_invisible);
      else return(ERR);
      break;
    case 1 :
      if(cursor_normal) (void)putp(cursor_normal);
      else return(ERR);
      break;
    case 2 :
      if(cursor_visible) (void)putp(cursor_visible);
      else return(ERR);
      break;
    default : return(ERR);
      }
    _screen->_cursor_state = visibility;
    }
  return(prev_state);
}
