#include "curses.h"
#include "screen.h"

#ifdef A_ALTCHARSET

chtype _acs[256] = {
        (chtype) ' ',           /* 00 */
        (chtype) ' ',           /* 01 */
        (chtype) ' ',           /* 02 */
        (chtype) ' ',           /* 03 */
        (chtype) ' ',           /* 04 */
        (chtype) ' ',           /* 05 */
        (chtype) ' ',           /* 06 */
        (chtype) ' ',           /* 07 */
        (chtype) ' ',           /* 08 */
        (chtype) ' ',           /* 09 */
        (chtype) ' ',           /* 0a */
        (chtype) ' ',           /* 0b */
        (chtype) ' ',           /* 0c */
        (chtype) ' ',           /* 0d */
        (chtype) ' ',           /* 0e */
        (chtype) ' ',           /* 0f */
        (chtype) ' ',           /* 10 */
        (chtype) ' ',           /* 11 */
        (chtype) ' ',           /* 12 */
        (chtype) ' ',           /* 13 */
        (chtype) ' ',           /* 14 */
        (chtype) ' ',           /* 15 */
        (chtype) ' ',           /* 16 */
        (chtype) ' ',           /* 17 */
        (chtype) ' ',           /* 18 */
        (chtype) ' ',           /* 19 */
        (chtype) ' ',           /* 1a */
        (chtype) ' ',           /* 1b */
        (chtype) ' ',           /* 1c */
        (chtype) ' ',           /* 1d */
        (chtype) ' ',           /* 1e */
        (chtype) ' ',           /* 1f */
        (chtype) ' ',           /* 20 */
        (chtype) ' ',           /* 21 */
        (chtype) ' ',           /* 22 */
        (chtype) ' ',           /* 23 */
        (chtype) ' ',           /* 24 */
        (chtype) ' ',           /* 25 */
        (chtype) ' ',           /* 26 */
        (chtype) ' ',           /* 27 */
        (chtype) ' ',           /* 28 */
        (chtype) ' ',           /* 29 */
        (chtype) ' ',           /* 2a */
        (chtype) '>',           /* 2b */        /* right pointing arrow */
        (chtype) '<',           /* 2c */        /* left pointing arrow */
        (chtype) '^',           /* 2d */        /* up pointing arrow */
        (chtype) 'V',           /* 2e */        /* down pointing arrow */
        (chtype) ' ',           /* 2f */
        (chtype) '#',           /* 30 */        /* solid square block */
        (chtype) ' ',           /* 31 */        /* lantern square */
        (chtype) ' ',           /* 32 */
        (chtype) ' ',           /* 33 */
        (chtype) ' ',           /* 34 */
        (chtype) ' ',           /* 35 */
        (chtype) ' ',           /* 36 */
        (chtype) ' ',           /* 37 */
        (chtype) ' ',           /* 38 */
        (chtype) ' ',           /* 39 */
        (chtype) ' ',           /* 3a */
        (chtype) ' ',           /* 3b */
        (chtype) ' ',           /* 3c */
        (chtype) ' ',           /* 3d */
        (chtype) ' ',           /* 3e */
        (chtype) ' ',           /* 3f */
        (chtype) ' ',           /* 40 */
        (chtype) ' ',           /* 41 */
        (chtype) ' ',           /* 42 */
        (chtype) ' ',           /* 43 */
        (chtype) ' ',           /* 44 */
        (chtype) ' ',           /* 45 */
        (chtype) ' ',           /* 46 */
        (chtype) ' ',           /* 47 */
        (chtype) ' ',           /* 48 */
        (chtype) ' ',           /* 49 */
        (chtype) ' ',           /* 4a */
        (chtype) ' ',           /* 4b */
        (chtype) ' ',           /* 4c */
        (chtype) ' ',           /* 4d */
        (chtype) ' ',           /* 4e */
        (chtype) ' ',           /* 4f */
        (chtype) ' ',           /* 50 */
        (chtype) ' ',           /* 51 */
        (chtype) ' ',           /* 52 */
        (chtype) ' ',           /* 53 */
        (chtype) ' ',           /* 54 */
        (chtype) ' ',           /* 55 */
        (chtype) ' ',           /* 56 */
        (chtype) ' ',           /* 57 */
        (chtype) ' ',           /* 58 */
        (chtype) ' ',           /* 59 */
        (chtype) ' ',           /* 5a */
        (chtype) ' ',           /* 5b */
        (chtype) ' ',           /* 5c */
        (chtype) ' ',           /* 5d */
        (chtype) ' ',           /* 5e */
        (chtype) ' ',           /* 5f */
        (chtype) '+',           /* 60 */        /* diamond */
        (chtype) ':',           /* 61 */        /* checker board (stipple) */
        (chtype) ' ',           /* 62 */
        (chtype) ' ',           /* 63 */
        (chtype) ' ',           /* 64 */
        (chtype) ' ',           /* 65 */
        (chtype) ' ',           /* 66 */        /* degree symbol */
        (chtype) '\'',          /* 67 */        /* plus/minus */
        (chtype) '#',           /* 68 */        /* board of squares */
        (chtype) ' ',           /* 69 */
        (chtype) '+',           /* 6a */        /* lower right corner */
        (chtype) '+',           /* 6b */        /* upper right corner */
        (chtype) '+',           /* 6c */        /* upper left corner */
        (chtype) '+',           /* 6d */        /* lower left corner */
        (chtype) '+',           /* 6e */        /* plus */
        (chtype) '-',           /* 6f */        /* scan line 1 */
        (chtype) ' ',           /* 70 */
        (chtype) '-',           /* 71 */        /* horizontal line */
        (chtype) ' ',           /* 72 */
        (chtype) '_',           /* 73 */        /* scan line 9 */
        (chtype) '+',           /* 74 */        /* left tee */
        (chtype) '+',           /* 75 */        /* right tee */
        (chtype) '+',           /* 76 */        /* bottom tee */
        (chtype) '+',           /* 77 */        /* top tee */
        (chtype) '|',           /* 78 */        /* vertical line */
        (chtype) ' ',           /* 79 */
        (chtype) ' ',           /* 7a */
        (chtype) ' ',           /* 7b */
        (chtype) ' ',           /* 7c */
        (chtype) ' ',           /* 7d */
        (chtype) ' ',           /* 7e */
        (chtype) ' ',           /* 7f */
        (chtype) ' ',           /* 70 */
        (chtype) ' ',           /* 81 */
        (chtype) ' ',           /* 82 */
        (chtype) ' ',           /* 83 */
        (chtype) ' ',           /* 84 */
        (chtype) ' ',           /* 85 */
        (chtype) ' ',           /* 86 */
        (chtype) ' ',           /* 87 */
        (chtype) ' ',           /* 88 */
        (chtype) ' ',           /* 89 */
        (chtype) ' ',           /* 8a */
        (chtype) ' ',           /* 8b */
        (chtype) ' ',           /* 8c */
        (chtype) ' ',           /* 8d */
        (chtype) ' ',           /* 8e */
        (chtype) ' ',           /* 8f */
        (chtype) ' ',           /* 90 */
        (chtype) ' ',           /* 91 */
        (chtype) ' ',           /* 92 */
        (chtype) ' ',           /* 93 */
        (chtype) ' ',           /* 94 */
        (chtype) ' ',           /* 95 */
        (chtype) ' ',           /* 96 */
        (chtype) ' ',           /* 97 */
        (chtype) ' ',           /* 98 */
        (chtype) ' ',           /* 99 */
        (chtype) ' ',           /* 9a */
        (chtype) ' ',           /* 9b */
        (chtype) ' ',           /* 9c */
        (chtype) ' ',           /* 9d */
        (chtype) ' ',           /* 9e */
        (chtype) ' ',           /* 9f */
        (chtype) ' ',           /* a0 */
        (chtype) ' ',           /* a1 */
        (chtype) ' ',           /* a2 */
        (chtype) ' ',           /* a3 */
        (chtype) ' ',           /* a4 */
        (chtype) ' ',           /* a5 */
        (chtype) ' ',           /* a6 */
        (chtype) ' ',           /* a7 */
        (chtype) ' ',           /* a8 */
        (chtype) ' ',           /* a9 */
        (chtype) ' ',           /* aa */
        (chtype) ' ',           /* ab */
        (chtype) ' ',           /* ac */
        (chtype) ' ',           /* ad */
        (chtype) ' ',           /* ae */
        (chtype) ' ',           /* af */
        (chtype) ' ',           /* b0 */
        (chtype) ' ',           /* b1 */
        (chtype) ' ',           /* b2 */
        (chtype) ' ',           /* b3 */
        (chtype) ' ',           /* b4 */
        (chtype) ' ',           /* b5 */
        (chtype) ' ',           /* b6 */
        (chtype) ' ',           /* b7 */
        (chtype) ' ',           /* b8 */
        (chtype) ' ',           /* b9 */
        (chtype) ' ',           /* ba */
        (chtype) ' ',           /* bb */
        (chtype) ' ',           /* bc */
        (chtype) ' ',           /* bd */
        (chtype) ' ',           /* be */
        (chtype) ' ',           /* bf */
        (chtype) ' ',           /* c0 */
        (chtype) ' ',           /* c1 */
        (chtype) ' ',           /* c2 */
        (chtype) ' ',           /* c3 */
        (chtype) ' ',           /* c4 */
        (chtype) ' ',           /* c5 */
        (chtype) ' ',           /* c6 */
        (chtype) ' ',           /* c7 */
        (chtype) ' ',           /* c8 */
        (chtype) ' ',           /* c9 */
        (chtype) ' ',           /* ca */
        (chtype) ' ',           /* cb */
        (chtype) ' ',           /* cc */
        (chtype) ' ',           /* cd */
        (chtype) ' ',           /* ce */
        (chtype) ' ',           /* cf */
        (chtype) ' ',           /* d0 */
        (chtype) ' ',           /* d1 */
        (chtype) ' ',           /* d2 */
        (chtype) ' ',           /* d3 */
        (chtype) ' ',           /* d4 */
        (chtype) ' ',           /* d5 */
        (chtype) ' ',           /* d6 */
        (chtype) ' ',           /* d7 */
        (chtype) ' ',           /* d8 */
        (chtype) ' ',           /* d9 */
        (chtype) ' ',           /* da */
        (chtype) ' ',           /* db */
        (chtype) ' ',           /* dc */
        (chtype) ' ',           /* dd */
        (chtype) ' ',           /* de */
        (chtype) ' ',           /* df */
        (chtype) ' ',           /* e0 */
        (chtype) ' ',           /* e1 */
        (chtype) ' ',           /* e2 */
        (chtype) ' ',           /* e3 */
        (chtype) ' ',           /* e4 */
        (chtype) ' ',           /* e5 */
        (chtype) ' ',           /* e6 */
        (chtype) ' ',           /* e7 */
        (chtype) ' ',           /* e8 */
        (chtype) ' ',           /* e9 */
        (chtype) ' ',           /* ea */
        (chtype) ' ',           /* eb */
        (chtype) ' ',           /* ec */
        (chtype) ' ',           /* ed */
        (chtype) ' ',           /* ee */
        (chtype) ' ',           /* ef */
        (chtype) ' ',           /* f0 */
        (chtype) ' ',           /* f1 */
        (chtype) ' ',           /* f2 */
        (chtype) ' ',           /* f3 */
        (chtype) ' ',           /* f4 */
        (chtype) ' ',           /* f5 */
        (chtype) ' ',           /* f6 */
        (chtype) ' ',           /* f7 */
        (chtype) ' ',           /* f8 */
        (chtype) ' ',           /* f9 */
        (chtype) ' ',           /* fa */
        (chtype) ' ',           /* fb */
        (chtype) ' ',           /* fc */
        (chtype) ' ',           /* fd */
        (chtype) ' ',           /* fe */
        (chtype) ' ',           /* ff */
        } ;

#endif
