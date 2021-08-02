#ifndef _SCREEN_H
#define _SCREEN_H

#define INPUT_BUFFER_LEN 10

#define cost_clr_eol        _screen->_cost_clr_eol
#define cost_clr_bol        _screen->_cost_clr_bol
#define cost_clr_eos        _screen->_cost_clr_eos
#define cost_cursor_address _screen->_cost_cursor_address
#define cost_cursor_down    _screen->_cost_cursor_down
#define cost_cursor_home    _screen->_cost_cursor_home
#define cost_cursor_left    _screen->_cost_cursor_left
#define cost_cursor_right   _screen->_cost_cursor_right
#define cost_cursor_up      _screen->_cost_cursor_up

/* States that curses can be in */

#define CURSES_NOT_INITIALISED 0
#define CURSES_STATE           1
#define SHELL_STATE            2

/* color stuff */

#define DEFAULT_PAIR  (-1)

/* data structure used to create a binary tree for parsing of the
   function keys */

typedef struct _key {
  struct _key *right;
  struct _key *left;
  int val;
  int ch;
  } _KEYNODE;

#ifndef _TERM
typedef struct _terminal TERMINAL;
#endif

struct _scrn {
  FILE     *_outfd;       /* output stream */
  FILE     *_infd;        /* input stream */
  WINDOW   *_physcr;      /* physical screen map */
  int      _stdtop;       /* top line of standard window after ripoffs */
  int      _stdbot;       /* bottom line after ripoffs */
  TERMINAL *_terminal;    /* terminal description and state */
  int      _typeahead;    /* file handle to check for typeahead */
  int      _delay;        /* default delay for windows */
  int      _flags;        /* default flags for windows */
  char     _state;        /* whether in curses mode */
  char     _cursor_state; /* state of cursor */
  WINDOW   *_slkscr;      /* slk window */
  char     *_slk_labels;  /* the contents of the slk keys */
  int      _slkfmt;       /* layout of slk labels */
  _KEYNODE *_keys;        /* function key binary tree */
  int      _chars_read;   /* number of characters read */
  char     *_chars;       /* characters already read */
#ifdef A_ALTCHARSET
  chtype   *_acs_char;    /* alternate character set */
#endif

  /* cost of terminfo strings */
  short _cost_clr_bol;
  short _cost_clr_eol;
  short _cost_clr_eos;
  short _cost_cursor_address;
  short _cost_cursor_down;
  short _cost_cursor_left;
  short _cost_cursor_right;
  short _cost_cursor_up;
  };

extern SCREEN *_screen;

#ifdef A_ALTCHARSET
extern chtype _acs[];
#endif

extern int _useenv;
extern int _filter;
extern char _longname[];

#endif
