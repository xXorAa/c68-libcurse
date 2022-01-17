#include "curses.h"
#include "term.h"
#include "window.h"
#include "privfunc.h"

/*
AT&T A character is read from the terminal associated with the window.
AT&T In NODELAY mode, if there is no input waiting, the value ERR is
AT&T returned.  In DELAY mode, the program will hang until the system
AT&T passes text through to the program.  Depending on the setting of
AT&T cbreak(), this will be after one characters (CBREAK mode), or after
AT&T the first newline (NOCBREAK mode).
AT&T In HALF-DELAY mode, the program will hang until a character is typed
AT&T or the specified timeout has been reached.  Unless noecho() has been
AT&T set, the character will also be echoed into the designated window.
AT&T
AT&T When wgetch() is called, before getting a character, it will call
AT&T wrefresh() if anything in the window has changed (for example, the
AT&T cursor has moved or text changed).
AT&T
AT&T When using wgetch() do not set both NOCBREAK mode (nocbreak())
AT&T and ECHO mode (echo()) at the same time.
AT&T depending on the state of the tty driver when each character is
AT&T typed, the program may produce undesired results.
AT&T
AT&T If wgetch() encounters a ^D, it is returned (unlike stdio routines,
AT&T which would return a null string and have a return code of -1).
AT&T
AT&T If keypad(win,TRUE) has been called, and a function key is pressed,
AT&T the token for that function key will be returned instead of the
AT&T raw characters.
*/

int
wgetch(WINDOW *win)
{
  int vtime, vmin;
  int ch;

  if(win == 0) return(ERR);

  if((win->_flags & (F_PAD|F_DIRTY)) == F_DIRTY) (void) wrefresh(win);

  if((vtime = win->_vtime) < 0) vtime = curscr->_vtime;
  if((vmin = win->_vmin) < 0) vmin = curscr->_vmin;
  if(_termstate(vmin, vtime, 0) == ERR) return(ERR);

  ch = _getchar();

  if((ch == '\r') && (cur_term->_flags & F_NL)) ch = '\n';
  if(win->_flags & F_KEYPAD) ch = _keymap(win, ch);

  if((cur_term->_flags & F_ECHO) && (ch < KEY_MIN)) (void) wechochar(win, (chtype)ch);

  return(ch);
}
