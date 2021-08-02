/*
 * This file contains definitions which may have to be altered to reflect
 * differences between systems.
 */

#ifdef QDOS
#define TERMDIR		"win1_SYS_terminfo"
#define DIR_SEPERATOR	"_"
#else
#define TERMDIR		"/usr/lib/terminfo"
#define DIR_SEPERATOR	"/"
#endif
