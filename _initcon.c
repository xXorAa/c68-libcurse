/*
 *          _ i n i t c o n 
 *
 *  Routine used when the functions defined in TERMIOS_H are
 *  are in use.   It initialises the 'termios' part of the
 *  Console driver in a manner suitable for use by the other
 *  routines defined in TERMIOS.
 *
 *  It is called from the end of the program initialisation code.
 *
 *  Amendment History
 *  ~~~~~~~~~~~~~~~~~
 *  15 Sep 92  DJW  first version.
 */

#define __LIBRARY__

#include <qdos.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>

extern chanid_t _conchan;

static  char lines[13] = "LINES=";
static  char cols[15] = "COLUMNS=";

void    _initcon()
{

    (_Chkufb(1))->ufbflg &= ~UFB_ND;        /* Clear No-Delay flag for stdout */

    /*
     *  If a console is in use, set the LINES and COLUMNS environment
     *  variables to the correct size.
     */
    if (_conchan ) {
        struct QLRECT rect[1];

        (void) sd_chenq (_conchan, 0, rect);
        (void) itoa (rect->q_height, &lines[6]);
        (void) putenv (lines);
        (void) itoa (rect->q_width, &cols[8]);
        (void) putenv (cols);
    }

    return;
}

