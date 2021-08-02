/*
 *                  _ c o n r e a d _ c
 *
 *  This routine is called from the 'read' call.  It handles
 *  input from the console/screen device.
 *
 *  This is the LIBCURSES_A version of this routine that
 *  supports a more complete emulation than that included
 *  in the standard LIBC_A library.
 *
 *  The idea of vectoring the call into this routine is that
 *  this makes it possible to replace this routine with a
 *  full terminal emulator if so desired.    This can be done
 *  in a way that is transparent to user-level programs.
 *
 *
 *  RETURN VALUES:
 *          0/+ve   This many bytes (from the start of the data
 *                  buffer passed) have been read
 *                  any translation.
 *          -1      Error occurred.
 *
 *
 *  AMENDMENT HISTORY
 *  ~~~~~~~~~~~~~~~~~
 *  19 Sep 92   DJW   - Original version (to support a CURSES library).
 *
 *  13 Apr 94   EAJ   - Changed to use _readkbd vector.
 *
 *  20 Nov 95   DJW   - Changed to use the 'termios' structure in the UFB
 *                      rather than assume a global one.
 *
 *  01 Aug 98   DJW   - Special keys (cursor up, etc) changed to return
 *                      symbolic values as defined in curses.h rather than
 *                      the raw QDOS key codes.
 *                      (problem reported by Jonathan Hudson)
 */

#define __LIBRARY__

#include <qdos.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

static
int     curses_default_conread _LIB_F3_ (struct UFB *,      uptr, \
                                         unsigned char *,   buf, \
                                         size_t,            len)
{
    unsigned char    *ptr, *bufend;
    long    delay;
    chanid_t    chid    = uptr->ufbfh;
    timeout_t   timeout = _GetTimeout(uptr);

    /*
     *  Ensure that a cursor is enabled
     */
    (void) sd_cure( chid, timeout);
    /*
     *  If we are doing non-canonical input, then we need
     *  to work out the delay/length values to use
     */
    if ((uptr->ufbterm.c_lflag & ICANON) != 0)
    {
       delay = -1;
    }
    else
    {
        delay = (uptr->ufbterm.c_cc[VTIME]+4)/5;
        if (uptr->ufbterm.c_cc[VMIN] == 0)
        {
            if (delay != 0)
            {
                len = 1;
            }
        }
        else
        {
            len = uptr->ufbterm.c_cc[VMIN];
            if (delay == 0)
            {
                 delay = -1;
            }
        }
    }

    /*
     *  We now enter the read loop !
     */
    for( ptr=buf, bufend=buf+len ; ptr < bufend ; ptr++)
    {
        switch (_oserr=(*_readkbd)( chid, delay, (char *)ptr))
        {
            case 0:
                break;
            default:
                errno = EOSERR;
                goto DO_EXIT;
        }
        /*
         *  The following apply in all modes
         *  We really need to write the code to
         *  fill in the gaps!
         */
        if (*ptr == uptr->ufbterm.c_cc[VSTART])
        {

                    /* Non yet implemented !! */

        }
        else if (*ptr == uptr->ufbterm.c_cc[VSTOP])
        {

                    /* Non yet implemented !! */

        }
        else if (*ptr == uptr->ufbterm.c_cc[VSUSP])
        {

                    /* Non yet implemented !! */

        }
        else if (*ptr == uptr->ufbterm.c_cc[VINTR])
        {

                    /* Non yet implemented !! */

        }
        else if (*ptr == uptr->ufbterm.c_cc[VQUIT])
        {

                    /* Non yet implemented !! */

        }
        else if (uptr->ufbterm.c_lflag & ICANON)
        {
            /*
             *  The following apply in ICANON mode
             */
            if (*ptr == uptr->ufbterm.c_cc[VEOF])
            {
                /*
                 *  Simulate EOF
                 */
                uptr->ufbst |= UFB_EOF;
                _oserr = ERR_EF;
                ptr = buf;
                goto DO_EXIT;
            }
            else if (*ptr == uptr->ufbterm.c_cc[VERASE])
            {
                /*
                 *  Erase character - as long as flags set
                 */
                if ((ptr != buf)  && (uptr->ufbterm.c_lflag & ECHOE))
                {
                    (void) sd_pcol (chid, timeout);
                    (void) io_sbyte(chid, timeout, ' ');
                    (void) sd_pcol (chid, timeout);
                    ptr-=2;          /* Ignore this char + deleted char */
                }
                continue;
            }
            else if (*ptr == '\n')
            {
                /*
                 *  If flags set, force echo of NL
                 */
                if (uptr->ufbterm.c_lflag & (ECHONL | ECHO))
                {
                    (void) io_sbyte (chid, timeout, '\n');
                }
                ptr++;
                goto DO_EXIT;
            }
        }
        else
        {
            /*
             *  The following apply in 'NOT ICANON' mode
             */
                    /* Non yet implemented !! */
        }
        /*
         *  If we get here, then we have to make
         *  a decision on echo.
         */
        if (uptr->ufbterm.c_lflag & ECHO)
        {
            (void) io_sbyte (chid, timeout, *ptr);
            continue;
        }
    }   /* End of for loop */
    /*
     *  Suppress cursor when finished
     */
DO_EXIT:
    (void) sd_curs( chid, timeout);
    return ((int)(ptr - buf));
}


/*===================================================================
 *      Default vector points to this routine
 *------------------------------------------------------------------*/
int     (*_conread)() = curses_default_conread;

