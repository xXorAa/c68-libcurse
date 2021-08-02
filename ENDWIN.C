#include <stdlib.h>
#include "curses.h"
#include "term.h"
#include "screen.h"
#include "window.h"

/*AT&T
AT&T A program should always call endwin() before exiting or escaping from
AT&T curses mode temporarily, to do a shell escape or system() call, for example.
AT&T This routine will remove tty modes, move the cursor to the lower left
AT&T corner of the screen and reset the terminal into the proper non-visual mode.
AT&T To resume after a termporary escape, call wrefresh() or doupdate().
AT&T */

int
endwin(void)
{
  WINDOW *physcr;

  if(_screen == 0) return(ERR);

  physcr = _screen->_physcr;
  (void) curs_set(1);
  (void) vidattr((chtype)A_NORMAL);
  physcr->_attr = A_NORMAL;
  (void) mvcur(physcr->_cury, physcr->_curx, physcr->_rows-1, 0);
  if(exit_ca_mode != 0) (void) putp(exit_ca_mode);
  if(keypad_local != 0) (void) putp(keypad_local);
  if(exit_insert_mode && physcr->_flags & F_INSERTED) (void) putp(exit_insert_mode);
  physcr->_flags &= ~(F_KEYPAD|F_INSERTED);
  (void) fflush(_screen->_outfd);
  (void) def_prog_mode();
  (void) reset_shell_mode();
  _screen->_state = SHELL_STATE;
  return(OK);
}
