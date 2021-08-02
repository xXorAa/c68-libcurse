/* 
 *      t e r m i o s
 *
 *  fake termios interface
 */

#define __LIBRARY__

#ifdef QDOS
#include <qdos.h>
#endif
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>

/*
 *  The speed get/set functions do not really have much meaning for
 *  console devices which is all that we currently support.
 *
 *  They will have more relevance if we later support a SER device
 *  for asynchronous connections.
 */

speed_t cfgetispeed(termios_p)
struct termios *termios_p;
{
    return termios_p->c_ispeed;
}

speed_t cfgetospeed(termios_p)
struct termios *termios_p;
{
    return termios_p->c_ospeed;
}

int cfsetispeed(termios_p, speed)
struct termios *termios_p;
speed_t speed;
{
    termios_p->c_ispeed = speed;
    return 0;
}

int cfsetospeed(termios_p, speed)
struct termios *termios_p;
speed_t speed;
{
    termios_p->c_ospeed = speed;
    return 0;
}

int tcgetattr(filedes, termios_p)
int filedes;
struct termios *termios_p;
{
    struct UFB *uptr;    

    if(!(uptr = _Chkufb(filedes))) {
        /* fd not valid */
        return -1;
    }

    switch (uptr->ufbtyp) {
    case D_CON:
            (void) memcpy (termios_p, &(uptr->ufbterm), sizeof (struct termios));
            break;
    default:
            errno = EACCES;
            return -1;
    }
    return 0;
}

int tcsetattr(filedes, opt_actions, termios_p)
int filedes;
int opt_actions;
struct termios *termios_p;
{
    struct UFB *uptr;    

    (void)opt_actions;      /* Dummy to stop compiler warning message */

    if(!(uptr = _Chkufb(filedes)))
        /* fd not valid */
        return -1;

    /* Posix 1003.1-1988 page 135 says:
     * Attempts to set unsupported baud rates shall be ignored, and it is
     * implementation-defined whether an error is returned by any or all of
     * cfsetispeed(), cfsetospeed(), or tcsetattr(). This refers both to
     * changes to baud rates not supported by the hardware, and to changes
     * setting the input and output baud rates to different values if the
     * hardware does not support it.
     * Ignoring means not to change the existing settings, doesn't it?
     */
    if ((termios_p->c_ispeed != 0 && termios_p->c_ispeed != termios_p->c_ospeed))
    {
        errno = EINVAL;
        return  -1;
    }
    switch (uptr->ufbtyp) {
        case D_CON:
                break;
        case D_AUX:
                mt_baud (termios_p->c_ispeed);
                break;
        default:
                break;
    }
    mt_baud (termios_p->c_ispeed);

    /* I don't know what should happen with requests that are not supported by
     * old Minix drivers and therefore cannot be emulated.
     * Returning an error may confuse the application (the values aren't really
     * invalid or unsupported by the hardware, they just couldn't be satisfied
     * by the driver). Not returning an error might be even worse because the
     * driver will act different to what the application requires it to act
     * after sucessfully setting the attributes as specified.
     * Settings that cannot be emulated fully include:
     *   c_ospeed != 110 && c_cflag & CSTOPB
     *   c_ospeed == 110 && ! c_cflag & CSTOPB
     *   (c_cc[VMIN] != 1 || c_cc[VTIME] != 0) && ! c_lflag & ICANON
     *   c_lflag & ICANON && ! c_lflag & ISIG
     * For the moment I just ignore these conflicts.
     */

    (void) memcpy (&(uptr->ufbterm), termios_p, sizeof(struct termios) );
    return (0);
}

int tcflush(filedes, queue_selector)
int filedes;
int queue_selector;
{
    (void) filedes;                 /* Dummies to stop warning from compiler */
    (void) queue_selector;

    return (0);
}

