#include "curses.h"
#include "screen.h"

WINDOW *stdscr; /* default screen */
WINDOW *curscr; /* what is wanted on the screen */

MOUSE_STATUS Mouse_status;

int COLORS = 0;      /* number of colours supported */
int COLOR_PAIRS = 0; /* number of colour pairs supported */

int LINES = 0; /* Number of lines used on screen */
int COLS = 0;  /* Number of columns used on screen */

SCREEN *_screen = (SCREEN *)0;    /* currently active screen */
#ifdef A_ALTCHARSET
chtype *_acs_ch = (chtype *)0;    /* current Alternate Chars */
#endif

int _useenv = TRUE;  /* Whether to use LINES and COLUMNS */
int _filter = FALSE; /* Whether curses is a filter */
char _longname[128]; /* Verbose description of the current terminal */

static char *_version = "0.1.1 alpha";
