#ifndef PRIVFUNC_H
#define PRIVFUNC_H

#include <stdio.h>

#ifndef _TERM
#endif

#ifndef _SCREEN_H
typedef struct _key _KEYNODE;
#endif

extern void _scroll_update (void);
extern void _clr_update (void);
extern int _overlay_overwrite (WINDOW*,WINDOW*,bool);

extern SCREEN *_newterm (char*,FILE*,FILE*,int*);
extern WINDOW *_mallocwindow (int,int,bool);
extern void _setupsubarea (WINDOW*,WINDOW*,int,int,int);
extern int _getsy (void);
extern int _getsx (void);

extern int _getchar (void);
extern void _ungetchar (int);
extern int _keymap (WINDOW *, int);
extern _KEYNODE *_newkeys (void);

extern void _ripoff_init (void);
extern void _slk_init (void);

extern int _vsscanf (char*,char*,va_list);

extern int _termstate (int,int,int);
#endif
