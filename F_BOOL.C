#include "term.h"

#ifdef __STDC__
#define def(a,b,c) #a,
#else
#define def(a,b,c) "a",
#endif

char *boolfnames[] = {
#include "bool.cap"
(char *)0 };
