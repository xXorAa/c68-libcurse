#include <string.h>
#include <stdlib.h>
#ifdef ARCH
#include "unistd.h"
#endif
#include "curses.h"
#include "term.h"
#include "screen.h"
#include "privfunc.h"

extern int _useenv;
extern int _filter;
extern char _longname[];

/*
Returns the number of bytes in a string - this is concidered to
be the 'cost' of outputing the string.
*/

static int
cost(char *str)
{
  return(str ? strlen(str) : 0);
}

/*AT&T
AT&T A program that outputs to more than one terminal must use newterm()
AT&T for each terminal instead of initscr().  A program that wants an
AT&T indication of error conditions, so that it may continue to run in a
AT&T line-oriented mode if the terminal cannot support a screen-oriented
AT&T program, must also use this routine. newterm() should be called once
AT&T for each terminal.  It returns a variable of type SCREEN* that should
AT&T be saved as a reference to that terminal.  The arguments are the type
AT&T of the terminal to be used in place of the environment variable TERM;
AT&T outfd, a stdio file pointer for output to the terminal;
AT&T and infd, another file pointer for input from the terminal.
AT&T When it is done running, the program must also call endwin() for each
AT&T terminal being used.  If newterm() is called more than once for the
AT&T same terminal, the first terminal referred to must be the last one
AT&T for which endwin() is called.
AT&T */

SCREEN *
_newterm(char *type, FILE *outfd, FILE *infd, int *errret)
{
  SCREEN *screen;
  char *sptr;
  struct termios tty_state;

  if((screen = (SCREEN *)malloc(sizeof(SCREEN))) == 0) return((SCREEN *)0);

  if(setupterm(type, (int)fileno(outfd), errret) == ERR) return((SCREEN *)0);

  /* remove any capabilities which rely on which line the cursor
     is currently on if this is to be a filter */
  if(_filter)
    {
    cursor_down =
    cursor_up =
    cursor_address =
    parm_up_cursor =
    parm_down_cursor =
    row_address =
    cursor_to_ll =
    cursor_home = (char *)0;
    }


  LINES = (_useenv && (sptr=getenv("LINES")) != 0) ? atoi (sptr) : lines;
  COLS = (_useenv && (sptr=getenv("COLUMNS")) != 0) ? atoi (sptr) : columns;

  screen->_state = CURSES_NOT_INITIALISED;
  screen->_outfd = outfd;
  screen->_infd  = infd;
  screen->_terminal = cur_term;
  screen->_chars = (char *) malloc((size_t)INPUT_BUFFER_LEN);
  screen->_chars_read = 0;
  screen->_stdtop = 0;
  screen->_stdbot = LINES - 1;
  screen->_keys = _newkeys();

  (void) def_shell_mode();

  if (tcgetattr((int)fileno(screen->_infd), &tty_state) == 0)
    {
    tty_state.c_lflag &= ~(ECHO|ECHOE|ECHONL|ECHOK);
    (void) tcsetattr((int)fileno(screen->_infd), TCSADRAIN, &tty_state);
    }

#ifdef A_ALTCHARSET
  /* must now set up the alternate character set */
  screen->_acs_char = (chtype *)malloc((size_t)sizeof(chtype) * 256);
  (void)memcpy(screen->_acs_char, _acs, (size_t)sizeof(chtype) * 256);
  if(acs_chars)
    {
    unsigned char *s;
    for(s = (unsigned char *)acs_chars; *s && *(s+1); s += 2)
      screen->_acs_char[*s] = (chtype) *(s+1);
    }
#endif

  (void)set_term(screen);
  (void)echo();

  /* now calculate the cost of using some of the strings used by the
     screen handling routines */

  cost_clr_bol        = cost(clr_bol);
  cost_clr_eol        = cost(clr_eol);
  cost_clr_eos        = cost(clr_eos);
  cost_cursor_address = cost(tparm(cursor_address,(long)LINES,(long)COLS));
  cost_cursor_down    = cost(cursor_down);
  cost_cursor_left    = cost(cursor_left);
  cost_cursor_right   = cost(cursor_right);
  cost_cursor_up      = cost(cursor_up);

  screen->_physcr = newwin(LINES, COLS, 0, 0);
  curscr = newwin(LINES, COLS, 0, 0);
  _slk_init();
  _ripoff_init();
  stdscr = newwin(LINES, COLS, 0, 0);

  /* and set up the longname */
  for (sptr=cur_term->_termdesc+strlen(cur_term->_termdesc); *(--sptr)!='|';) {}
  (void)strcpy(_longname, ++sptr);

  return(screen);
}

SCREEN *
newterm(char *type, FILE *outfd, FILE *infd)
{
  int err;
  return(_newterm(type, outfd, infd, &err));
}
