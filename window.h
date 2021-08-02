#ifndef _WINDOW_H
#define _WINDOW_H

/* states into which the window can be set */

#define F_NORMAL   0x00000L /* no flags set */
#define F_DIRTY    0x00001L /* changes have been made to the window */
#define F_CLEAR    0x00002L /* screen to be redrawn when window refreshed */
#define F_PAD      0x00004L /* this is a pad */
#define F_LEAVE    0x00008L /* leave the cursor where it is */
#define F_ECHO     0x00010L /* character input is to be echoed to window */
#define F_ID       0x00020L /* use insert/delete line if possible */
#define F_IC       0x00040L /* use insert/delete character if possible */
#define F_KEYPAD   0x00080L /* check input for 'function' keys */
#define F_FLUSH    0x00100L /* flush the output on an interrupt */
#define F_META     0x00200L /* use 7 or 8 bits */
#define F_TIMEOUT  0x00400L /* use timer to differentiate sequences */
#define F_DELAY    0x00800L /* whether input is to be blocking */
#define F_NL       0x01000L /* map carriage return to newline */
#define F_IMMED    0x02000L /* immediate update any changes */
#define F_SYNC     0x04000L /* immediate update changes to ancestors */
#define F_SCROLL   0x08000L /* scroll the window */
#define F_INSERTED 0x10000L /* Insert/Delete line has been used in window */

typedef struct _line {
  int first;     /* position of first changes to a line*/
  int last;      /* position of last changes to a line */
  chtype *line;  /* the window lines contents */
  } _LINE;

/* Whether the line has been updated */
#define FIRST_NOT_CHANGED 32767
#define LAST_NOT_CHANGED  (-1)

struct _window {
  int _begy;               /* y co-ord of window start */
  int _begx;               /* x co-ord of window origin */
  int _rows;               /* number of rows in the window */
  int _cols;               /* number of columns in the window */
  int _nlines;             /* (PAD only) lines in pad */
  int _ncols;              /* (PAD only) columns in pad */
  int _cury;               /* y position of the window's cursor */
  int _curx;               /* x position of the window's cursor */
  int _top;                /* top of the scrolling region */
  int _bot;                /* bottom of the scroling region */
  int _children;           /* the number of children */
  int _vtime;              /* 1/10 second delay on input */
  int _vmin;               /* number of characters to read */
  chtype _attr;            /* window's current attributes */
  unsigned long _flags;    /* window flags (see above) */
  struct _window *_parent; /* parent window (if a child) */
  _LINE _lines[1];
  };
#endif
