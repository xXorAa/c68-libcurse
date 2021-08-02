#include "term.h"

#ifdef __STDC__
#define def(a,b,c) #b,
#else
#define def(a,b,c) "b",
#endif

char *strnames [] = {
#include "str.cap"
(char *)0};
