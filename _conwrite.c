/*
 *					_ c o n w r i t e _ c
 *
 *	This routine is called from the 'write' call when data is
 *	to be translated.	 It implements the handling for the QL
 *	screen of the standard C escape sequences defined by a VT52
 *	style terminal.  This version is intended for use with the
 *	LIBCURSES_A library.
 *
 *	The idea of vectoring the call into this routine is that
 *	this makes it possible to replace this routine with a
 *	full terminal emulator if so desired.	 This can be done
 *	in a way that is transparent to user-level programs.
 *
 *	This routine only needs to handle escape sequences.   It can
 *	leave handling of standard strings to the calling routine
 *	by returning the appropriate values.
 *
 *	RETURN VALUES:
 *			+ve 	This many bytes (from the start of the data
 *					buffer passed can be output without doing
 *					any translation.
 *			  0 	Output finished.   Either all data has been
 *					processed or an error occured.
 *			-ve 	This many characters from the buffer have been
 *					consumed in "special" processing.
 *
 * Routine handles writing to all the different
 * types of device.
 *
 *	AMENDMENT HISTORY
 *	~~~~~~~~~~~~~~~~~
 *	16 Sep 92	DJW   - First version.	The version in the standard LIBC_A
 *						library was used as a model.
 *	15 Oct 92	DPW   - Fix for problem encountered when writing to the last
 *						position on the screen, when there should be an 
 *						automatic scroll takes place. This was preventing 
 *						ELVIS from correctly displaying lines of screen 
 *						width or more when scrolling through a file.
 *	 8 Jan 95	EAJ   - changed to take into account that io_sstrg now
 *						returns <0 if error, >=0 if OK.
 *						Also, added sd_donl() after call to io_sstrg(), since
 *						other escape sequences expect the cursor position to
 *						be correct: printing an entire line (without
 *						terminating LF) immediatly followed by the escape
 *						sequence to clear the line under and to the right
 *						of the cursor didn't work previously. This would
 *						lead to left-over charaters in Elvis when scrolling
 *						up or down. Elvis now works OK: printing one line,
 *						then clearing the following line.
 */

#define __LIBRARY__

#include <qdos.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <errno.h>

#define STATE_NORMAL	0			/* Default state - nothing outstanding */
#define STATE_ESC		1			/* ESC received */
#define STATE_POS		2
#define STATE_POS2		3

static timeout_t timeout;
static long param1;
static struct QLRECT cur;

#if 1
/* Macro version */
#define Get_Details(A) (void) sd_chenq (A->ufbfh, timeout, &cur)
#else
/* Function version */
static void Get_Details(uptr)
struct UFB * uptr;
{  (void) sd_chenq ( uptr->ufbfh, timeout, &cur ); }
#endif


static
long	termios_conwrite (uptr, buf, len)
struct UFB * uptr;
char *buf;
size_t len;
{
	int 	mode, strip, ink, scroll_size, to_write;
	chanid_t  chid	  = uptr->ufbfh;

	timeout = _GetTimeout(uptr);

	_oserr = 0; 			/* ensure this is clear in case we do not change it */
	switch (uptr->ufbst) {
	case STATE_NORMAL:
			if ((to_write = strcspn ((char *)buf, "\x1b\n\b\r\f\a\t")) != 0) {
				div_t line_info;
				/*
				 *	Getting here means we have some
				 *	ordinary text to output.
				 */
				if(to_write > len) to_write = len;
				/*
				 *	We should really check for a length of greater than 32K-1
				 *	here, but since this is unlikely for screen output, we 
				 *	will not bother
				 */ 
				Get_Details(uptr);
				line_info = div(( cur.q_x + 
					  (_oserr =io_sstrg(chid, timeout, buf, (short)to_write))),
						 (int) cur.q_width);
				if( _oserr < 0 ) {      /* EAJ, jan 1995: io_sstrg returns qdos error or number of chars written !  */
					errno = EOSERR;
					return(0);
				}
				if (((line_info.quot + cur.q_y) >= cur.q_height)
				&&	(line_info.rem == 0) )
					(void) sd_scrol(chid, timeout, -10);
				(void) sd_donl(chid, timeout);
				return(-(to_write));
			} 
			/*
			 *	We get here whenever one of the characters for
			 *	which we wish to take special action is found
			 */
			switch (*buf) {
			case '\b':	/* backspace */
						/* (from Peter Sulzer) */
					(void) sd_pcol( chid, timeout );
					break;
			case '\r':	/* carriage return */
					(void) sd_tab( chid, timeout, 0 );
					break;
			case '\n':	/* Newline */
					Get_Details(uptr);
					if (cur.q_y < cur.q_height - 1) {
						goto CURSOR_DOWN;
					}
					(void) sd_scrol(chid, timeout, -10);
					break;
			case '\a':	/* bell */
					(void) beep( 500, 50 );
					break;
			case '\f':	/* form feed */
					(void) sd_clear( chid, timeout );
					break;
			case '\t':	/* tabulator */
					 /* (using a hint from Hans Lub) */
					Get_Details(uptr);
					(void) sd_tab ( chid, timeout, cur.q_x + 8 - (cur.q_x % 8) );
					return (-1);
			case '\x1b': /* ESC */
					uptr->ufbst = STATE_ESC;
					return (-1);
			default:
					return (1);
			}

	case STATE_ESC:
			switch (*buf) {
			case 'A':	/* Cursor up */
					Get_Details(uptr);
CURSOR_UP:
					if (cur.q_y > 0) {
						(void) sd_prow(chid, timeout);
					}
					break;
			case 'B':	/* Cursor Down */
					Get_Details(uptr);
					if (cur.q_y < cur.q_height - 1) {
CURSOR_DOWN:
						(void) sd_nrow(chid, timeout);
					}
					break;
			case 'C':	/* Cursor Right */
					Get_Details(uptr);
					if (cur.q_x < cur.q_width - 1) {
						(void) sd_ncol( chid, timeout);
					}
					break;
			case 'D':	/* Cursor left */
					Get_Details(uptr);
					if (cur.q_x) {
						(void) sd_pcol(chid, timeout);
					}
					break;
			case 'E':	/* Clear screen (and home cursor) */
					(void) sd_clear (chid, timeout);
					break;
			case 'H':	/* Home cursor */
					(void) sd_pos (chid, timeout, 0, 0);
					break;
			case 'I':	/* Cursor up - scroll if at top */
					Get_Details(uptr);
					if (cur.q_y) {
						goto CURSOR_UP;
					} 
					goto INSERT_LINE;
			case 'J':	/* Erase to end of screen (including cursor) */
					(void) sd_clrbt(chid, timeout);
					/* FALLTHRU */
			case 'K':	/* Clear to End-of-Line (Including cursor) */
					(void) sd_clrrt(chid, timeout);
					break;
			case 'L':	/* Insert line (current one down) cursor at start */
INSERT_LINE:
					scroll_size = 10;
					goto INSERT_DELETE_LINE;
			case 'M':	/* Delete line */
					scroll_size = -10;
INSERT_DELETE_LINE:
					Get_Details(uptr);
					if (cur.q_y == 0) {
						(void) sd_scrol(chid, timeout, scroll_size);
					} else {
						(void) sd_prow (chid, timeout);
						(void) sd_scrbt (chid, timeout, scroll_size);
						(void) sd_nrow (chid, timeout);
					}
					break;
			case 'Y':	/* Cursor position */
					uptr->ufbst = STATE_POS;
					return (-1);
			case 'l':	/* Insert character */
					scroll_size = 6;
					goto INSERT_DELETE_CHARACTER;
			case 'm':	/* Delete character */
					scroll_size = -6;
INSERT_DELETE_CHARACTER:
					(void) sd_panrt (chid, timeout, scroll_size);
					break;
			case 'p':	/* Reverse video */
					strip = _condetails.ink;
					ink  = _condetails.paper;
					goto SET_STRIP_INK;
			case 'q':	/* Normal video */
					strip = _condetails.paper;
					ink   = _condetails.ink;
SET_STRIP_INK:
					(void) sd_setst (chid, timeout, strip);
					(void) sd_setin (chid, timeout, ink);
					break;
			case 'r':	/* Start underline mode */
					mode = 1;
					goto SET_UNDERLINE_MODE;
			case 's':	/* End underline mode */
					mode = 0;
SET_UNDERLINE_MODE:
					(void) sd_setul (chid, timeout, mode);
					break;
			}
			break;

	case STATE_POS:
			param1 = *buf - ' ';
			uptr->ufbst = STATE_POS2;
			return (-1L);

	case STATE_POS2:
			(void) sd_pos (chid, timeout, *buf-' ',param1);
			break;
	}

	uptr->ufbst = STATE_NORMAL;
	return (-1);
}

/*===================================================================
 *		Default vector points to this routine
 *------------------------------------------------------------------*/
int 	(*_conwrite)() = termios_conwrite;
