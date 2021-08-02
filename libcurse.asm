*   This is a dummy file to insert at the start of a library to
*   get a comment into it.   It also means that examination of the
*   binary program can tell what versions of the libraries were used.
*
*   It is assembled with the Quanta QMAC assembler as this is the only
*   QL assembler that I know of that supports all of the following:
*       a)  Allows comments to be inserted into the SROFF output
*       b)  Allows long label names with all characters significant
*       c)  Allows leading underscores in names.
*
*   AMENDMENT HISTORY
*   ~~~~~~~~~~~~~~~~~
*   30 Mar 94   DJW   - Added 2 underscores to name
*
*   16 Sep 94   DJW   - Removed udnerscores from name again.  This makes
*                       this variable invisible at the C level.
*
*   16 May 98   DJW   - Version updated to 4.24
*   01 Aug 98   DJW   - Version updated to 4.24d
*   31 Oct 98   DJW   - Version updated to 4.24f

    SECTION TEXT

    COMMENT C68 libcurses_a v4.24f

    XDEF    LIBCURSES_VER
LIBCURSES_VER:  dc.b    'C68 libcurses_a v4.24f',0

    XREF    __initcon
    XREF    __conread
    XREF    __conwrite
    XREF    __condetails

    dc.l    __initcon-*
    dc.l    __conread-*
    dc.l    __conwrite-*
    dc.l    __condetails-*
    END

