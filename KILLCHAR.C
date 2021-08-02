#include <unistd.h>
#include <termios.h>
#include "curses.h"
#include "term.h"
#include "screen.h"

/*AT&T
AT&T The user's current line-kill character is returned.
AT&T */

char
killchar(void)
{
  struct termios tty_state;

  if(_screen == 0) return(ERR);
  if(tcgetattr((int)fileno(_screen->_infd), &tty_state) != 0) return(ERR);
  return(tty_state.c_cc[VKILL]);
}
