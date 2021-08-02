#include "curses.h"
#include "term.h"

/*
AT&T Output a string that puts the terminal in the video attribute
AT&T mode attr, which is any combination of the attributes.
AT&T
If a capability does not exist in the terminfo database then it will
try to substitute an atribute which is close.
*/

int
vidputs(chtype attr, int (*putch)(int))
{
  chtype fake_attr;
  chtype supported_attr;

  if(cur_term->_attr == attr) return(OK); /* already correctly set */

  supported_attr = cur_term->_supported_attr;

#ifdef A_COLOR
  /* check for attributes that must not be used if colour is being used. */

  if(cur_term->_colour_pairs && no_color_video > 0)
    supported_attr &= ~(no_color_video + A_STANDOUT - 1);
#endif

  /* We may be requesting some attributes which are not supported
     in the terminfo database - in this case we may be able to use
     a close alternative. */

  if((fake_attr = (~supported_attr) & attr) != (chtype)0)
    {
    if(fake_attr & A_BOLD)
      {
      if(supported_attr & A_REVERSE) attr |= A_REVERSE;
      else if (supported_attr & A_STANDOUT) attr |= A_STANDOUT;
      }
    if(fake_attr & A_STANDOUT)
      {
      if(supported_attr & A_REVERSE) attr |= A_REVERSE;
      else if (supported_attr & A_BOLD) attr |= A_BOLD;
      }
    if(fake_attr & A_REVERSE)
      {
      if(supported_attr & A_STANDOUT) attr |= A_STANDOUT;
      else if(supported_attr & A_BOLD) attr |= A_BOLD;
      }
    }

  /* now make sure that from now on only supported attributes are used */
#ifdef A_COLOR
  attr &= supported_attr | A_COLOR;
#endif

  if(attr == cur_term->_attr)
    return(OK);  /* after faked attributes we have a match */

#ifdef A_COLOR
  if((attr & A_ATTRIBUTES & (~A_COLOR)) !=
     (cur_term->_attr & A_ATTRIBUTES & (~A_COLOR)))
#else
  if((attr & A_ATTRIBUTES) != (cur_term->_attr & A_ATTRIBUTES))
#endif
    {
    if(set_attributes)
      /* must use set_attributes if it is defined in
         preference to setting the attributes individually
         because it is allowable for the individual
         settings to turn off other attributes. Hopefully
         set_attributes handles multiple settings OK. */
  
      (void)tputs(tparm(set_attributes,
                  (long)attr & A_STANDOUT,
                  (long)attr & A_UNDERLINE,
                  (long)attr & A_REVERSE,
                  (long)attr & A_BLINK,
                  (long)attr & A_DIM,
                  (long)attr & A_BOLD,
                  (long)attr & A_INVIS,
                  (long)attr & A_PROTECT,
#ifdef A_ALTCHARSET
                  (long)attr & A_ALTCHARSET
#else
                  (long)A_NORMAL
#endif
        ),1,putch) ;
    else
      {
      /* required attributes = attr */
      /* current attributes = cur_term->_attr */
#ifdef A_COLOR
      chtype off_attr, set_attr = cur_term->_attr & (~A_COLOR);
#else
      chtype off_attr, set_attr = cur_term->_attr;
#endif

      /* turn off any attributes not required */
      off_attr = set_attr & (~attr);
      if(off_attr)
        {
        /* can we turn off all attributes */
        if(exit_attribute_mode)
          {
          (void)tputs(tparm(exit_attribute_mode),1,putch);
          off_attr = A_ATTRIBUTES & (~A_COLOR);
          }
        else
          {
          if((off_attr&A_STANDOUT) && exit_standout_mode)
            (void)tputs(exit_standout_mode,1,putch);
          if((off_attr&A_UNDERLINE) && exit_underline_mode)
            (void)tputs(exit_underline_mode,1,putch);
          if((off_attr&A_ALTCHARSET) && exit_alt_charset_mode)
            (void)tputs(exit_alt_charset_mode,1,putch);
          }
        set_attr &= ~off_attr;
        }

      set_attr = attr & (~set_attr);
      if(set_attr & A_STANDOUT) (void)tputs(enter_standout_mode,1,putch);
      if(set_attr & A_UNDERLINE) (void)tputs(enter_underline_mode,1,putch);
      if(set_attr & A_REVERSE) (void)tputs(enter_reverse_mode,1,putch);
      if(set_attr & A_BLINK) (void)tputs(enter_blink_mode,1,putch);
      if(set_attr & A_DIM) (void)tputs(enter_dim_mode,1,putch);
      if(set_attr & A_BOLD) (void)tputs(enter_bold_mode,1,putch);
      if(set_attr & A_PROTECT) (void)tputs(enter_protected_mode,1,putch);
#ifdef A_ALTCHARSET
      if(set_attr & A_ALTCHARSET)
        (void)tputs(enter_alt_charset_mode,1,putch);
#endif
      }
    }
  
#ifdef A_COLOR
  /* Phew!! We have the attributes set/unset, now lets get the colours
     sorted out. */

  if((cur_term->_attr & A_COLOR) != (attr & A_COLOR))
    {
    short pair;
    short fg;    /* foreground colour */
    short bg;    /* background colour */
    short cur_pair;
    short cur_bg;  /* current background colour */
    short cur_fg;  /* current foreground colour */

    if((pair = (short)PAIR_NUMBER(attr)) != 0)
      {
      if(pair_content(pair, &fg, &bg) == OK)
        {
        /* the colour pair has been correctly set up */
        if(set_color_pair) (void)tputs(tparm(set_color_pair,(long)pair),1,putch);
        else
          {
          if((cur_pair = (short) PAIR_NUMBER (cur_term->_attr)) != 0)
            (void)pair_content(cur_pair, &cur_fg, &cur_bg);
          else
            cur_fg = cur_bg = -1;
    
          if(bg != cur_bg)
            {
            if(set_a_background)
              (void)tputs(tparm(set_a_background, (long)bg),1,putch);
            else if(set_background)
              (void)tputs(tparm(set_background, (long)bg),1,putch);
            }
    
          if(fg != cur_fg)
            {
            if(set_a_foreground)
              (void)tputs(tparm(set_a_foreground, (long)fg),1,putch);
            else if(set_foreground)
              (void)tputs(tparm(set_foreground, (long)fg),1,putch);
            }
          }
        }
      }
    else
      (void)tputs(tparm(orig_pair),1,putch);
    }
#endif

  cur_term->_attr = attr;
  return(OK);
}
