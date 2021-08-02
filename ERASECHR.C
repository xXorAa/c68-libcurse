#include <unistd.h>
#include <termios.h>
#include "curses.h"
#include "term.h"
#include "screen.h"

/*AT&T
AT&T The user's current line-kill character is returned.
AT&T */

char
erasechar(void)
{
  struct termios tty_state;

  if(cur_term == 0) return(ERR);
  if(tcgetattr(cur_term->_outfd, &tty_state) != 0) return(ERR);
  return(tty_state.c_cc[VERASE]);
}
