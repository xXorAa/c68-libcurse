#include "curses.h"
#include "privfunc.h"

int
_overlay_overwrite(WINDOW *srcwin, WINDOW *dstwin, bool ovrlay)
{
  int src_begx, src_endx;
  int src_begy, src_endy;
  int dst_begx, dst_endx;
  int dst_begy, dst_endy;
  int begx, endx;
  int begy, endy;

  if(srcwin == 0 || dstwin == 0) return(ERR);

/*IMB check to see if we can replace the following with direct accesses*/
  getmaxyx(srcwin, src_endy, src_endx);
  getbegyx(srcwin, src_begy, src_begx);
  getmaxyx(dstwin, dst_endy, dst_endx);
  getbegyx(dstwin, dst_begy, dst_begx);

  src_endy += src_begy;
  src_endx += src_begx;
  dst_endy += dst_begy;
  dst_endx += dst_begx;

  begy = src_begy > dst_begy ? src_begy : dst_begy;
  begx = src_begx > dst_begx ? src_begx : dst_begx;
  endy = src_endy < dst_endy ? src_endy : dst_endy;
  endx = src_endx < dst_endx ? src_endx : dst_endx;

  if ((begx < endx) && (begy < endy))
    {
    /* windows overlap */

    src_begy = begy - src_begy;
    src_begx = begx - src_begx;
    dst_begy = begy - dst_begy;
    dst_begx = begx - dst_begx;
    dst_endy = dst_begy + endy - begy;
    dst_endx = dst_begx + endx - begx;

    return copywin(srcwin, dstwin, src_begy, src_begx,
            dst_begy, dst_begx, dst_endy, dst_endx, (int)ovrlay);
    }
  return(OK);
}
