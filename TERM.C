#include "curses.h"
#include "term.h"

TERMINAL *cur_term = (TERMINAL *)0;
struct termios _tty_state;
