#include <unistd.h>
#include "curses.h"
#include "term.h"
#include "window.h"
#include "screen.h"
#include "privfunc.h"

int
_termstate(int vmin, int vtime, int flag)
{
  struct termios tty;
  WINDOW *physcr;
  if(cur_term == 0) return(ERR);
  physcr = _screen->_physcr;
  if(vmin != physcr->_vmin || vtime != physcr->_vtime)
    {
    tty = cur_term->_prog_mode;
    if (vmin == -1) {
      /* canonical mode */
      tty.c_lflag |= ICANON;
      tty.c_iflag |= ICRNL;
      tty.c_cc[VEOF] = 4; /* ^D */
      tty.c_cc[VEOL] = 10; /* ^J */
    } else {
      /* non-canonical mode */
      tty.c_lflag &= flag ? ~ICANON : ~(ICANON | ISIG);
      tty.c_iflag &= ~ICRNL;
      tty.c_cc[VMIN] = vmin;
      tty.c_cc[VTIME] = vtime;
    }
    if (tcsetattr(fileno(_screen->_infd), TCSADRAIN, &tty) == -1) return(ERR);
    cur_term->_prog_mode = tty;
    physcr->_vmin = vmin;
    physcr->_vtime = vtime;
  }
  return(OK);
}
