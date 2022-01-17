#include "term.h"

#ifdef __STDC__
#define def(a,b,c) #a,
#else
#define def(a,b,c) "a",
#endif

char *strfnames [] = {
#include"str.cap"
(char *)0};
