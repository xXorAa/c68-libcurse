#   Makefile to build curses library using C68 on QDOS

CFLAGS = -Qwarn=5 -Qmaxerr=5 -c -O
CPP =	cpp
SED =	sed
CPFLAGS =
LDFLAGS = -lcurses -bufl50K -bufp100K
RM  = rm -f
I = WIN1_SYS_INCLUDE_

PROGS = infocmp tput tic

OBJS =  ACS_o       ADDCHNS_o   ADDCH_o     ADDNSTR_o   ADDSTR_o \
        ATTROFF_o   ATTRON_o    ATTRSET_o \
        BAUDRATE_o  BEEP_o      BKGDSET_o   BKGD_o      BOOL_o \
        BORDER_o    BOX_o \
        CAN_CHNG_o  CBREAK_o    CLEAROK_o   CLEAR_o     CLR2BOT_o \
        CLR2EOL_o   CLRUPDAT_o  COL_CONT_o  COPYWIN_o   CURS_SET_o \
        C_BOOL_o    C_NUM_o     C_STRING_o \
        DATA_o      DEFPROG_o   DEFSHELL_o  DELAYOP_o   DELCH_o \
        DELCTERM_o  DELLN_o     DELSCRN_o   DELWIN_o    DERWIN_o \
        DOUPDATE_o  DUPWIN_o \
        ECHOCHAR_o  ECHO_o      ENDWIN_o    ERASECHR_o  ERASE_o \
        FILTER_o    FLASH_o     FLUSHINP_o  FUNC_KEY_o  F_BOOL_o \
        F_NUM_o     F_STRING_o \
        GETCHAR_o   GETCH_o     GETSTR_o    GETSYX_o    GETWIN_o \
        GETYX_o \
        HALFDLAY_o  HASCOLOR_o  HAS_IC_o    HAS_IL_o    HLINE_o \
        IDCOK_o     IDLOK_o     ID_LN_o     IMMEDOK_o   INCHNSTR_o \
        INCHSTR_o   INCH_o      INITCOLR_o  INITPAIR_o  INITSCR_o \
        INNSTR_o    INSCH_o     INSLN_o     INSNSTR_o   INSSTR_o \
        INSTR_o     INTRFLSH_o  ISENDWIN_o  IS_LNTCH_o  IS_WNTCH_o \
        KEYNAME_o   KEYPAD_o    KILLCHAR_o \
        LEAVEOK_o   LONGNAME_o \
        MADDCHNS_o  MADDNSTR_o  MALOCWIN_o  META_o      MOVE_o \
        MVADDCH_o   MVADDSTR_o  MVCUR_o     MVDELCH_o   MVDERWIN_o \
        MVGETCH_o   MVGETSTR_o  MVINCHNS_o  MVINCHS_o   MVINCH_o \
        MVINNSTR_o  MVINSCH_o   MVINSNS_o   MVINSSTR_o  MVINSTR_o \
        MVPRINTW_o  MVSCANW_o   MVWADDCH_o  MVWDELCH_o  MVWGETCH_o \
        MVWINCH_o   MVWINSCH_o  MVWINSNS_o  MVWINSTR_o  MVWIN_o \
        MVWSCANW_o  MWADCHNS_o  MWADDNST_o  MWADDSTR_o  MWGETSTR_o \
        MWINCHNS_o  MWINCHS_o   MWINNSTR_o  MWINSSTR_o  MWPRINTW_o \
        NAPMS_o     NEWKEYS_o   NEWPAD_o    NEWTERM_o   NEWWIN_o \
        NL_o        NOCBREAK_o  NODELAY_o   NOECHO_o    NONL_o \
        NOQIFLSH_o  NORAW_o     NOTIMOUT_o  NUM_o \
        OVERLAY_o   OVERLYWR_o  OVERWRIT_o \
        PAIRCONT_o  PECHOCHR_o  PNOUTREF_o  PREFRESH_o  PRINTW_o \
        PUTP_o      PUTWIN_o \
        QIFLUSH_o \
        RAW_o       REDRAWWN_o  REFRESH_o   RESETTY_o   RIPOFFLN_o \
        RSETPROG_o  RSETSHEL_o  RSTRTTRM_o \
        SAVETTY_o   SCANW_o     SCRL_o      SCROLLOK_o  SCROLL_o \
        SCROLUPD_o  SCR_DUMP_o  SCR_INIT_o  SCR_REST_o  SCR_SET_o \
        SETCTERM_o  SETSCRG_o   SETSYX_o    SETUPTRM_o  SET_TERM_o \
        SKATROFF_o  SKATRON_o   SKATRSET_o  SKCLEAR_o   SKINIT_o \
        SKLABEL_o   SKNOUTRF_o  SKREFRSH_o  SKRESTOR_o  SKSET_o \
        SKTOUCH_o   STANDEND_o  STANDOUT_o  STARTCOL_o  STRING_o \
        SUBAREA_o   SUBPAD_o    SUBWIN_o    SYNCOK_o \
        TERMATTR_o  TERMNAME_o  TERMSTAT_o  TERM_o      TGETENT_o \
        TGETFLAG_o  TGETNUM_o   TGETSTR_o   TGOTO_o     TIGETFLG_o \
        TIGETNUM_o  TIGETSTR_o  TIMEOUT_o   TOUCHLN_o   TOUCHWIN_o \
        TPARM_o     TPUTS_o     TYPAHEAD_o \
        UNCTRL_o    UNGETCHR_o  UNGETCH_o   UNTOCHWN_o  USE_ENV_o \
        VIDATTR_o   VIDPUTS_o   VLINE_o     VSSCANF_o   VWPRINTW_o \
        VWSCANW_o \
        WADDCHNS_o  WADDCH_o    WADDNSTR_o  WADDSTR_o   WATTROFF_o \
        WATTRON_o   WATTRSET_o  WBKGDSET_o  WBKGD_o     WBORDER_o \
        WCLEAR_o    WCLR2BOT_o  WCLR2EOL_o  WCSYNCUP_o  WDELCH_o \
        WDELLN_o    WECHOCHR_o  WERASE_o    WGETCH_o    WGETNSTR_o \
        WGETSTR_o   WHLINE_o    WID_LN_o    WINCHNS_o   WINCHSTR_o \
        WINCH_o     WINNSTR_o   WINSCH_o    WINSLN_o    WINSNSTR_o \
        WINSSTR_o   WINSTR_o    WMOVE_o     WNOUTREF_o  WPRINTW_o \
        WREDRAWL_o  WREFRESH_o  WSCANW_o    WSCRL_o     WSETSCRG_o \
        WSTNDEND_o  WSTNDOUT_o  WSYNCDWN_o  WSYNCUP_o   WTIMEOUT_o \
        WTOUCHLN_o  WVLINE_o

IOSOBJ =    _condetail_o    _conread_o      _conwrite_o      _initcon_o \
            libcurse_o      qltermios_o

.SUFFIXES : _x _s _asm _o _rel _hdr _h

all:		libcurses_a
#		@for i in $(SUBDIRS);\
#		do \
#			echo "../libcurses.a: started in $$i ... `date`";\
#			cd $$i; $(MAKE) ../libcurses.a; cd ..;\
#			echo "../libcurses.a: completed in $$i ... `date`";\
#		done

libcurses_a : ${OBJS} ${IOSOBJ} ${PRGS} slblist wlist
    slb -crv libcurses_a libcurse_o
    slb -crvk -mslblist libcurses_a

wlist : slblist
        @slb -v -Wwlist -mslblist

ylist : slblist
        @slb -v -Yylist -mslblist

slblist :   $(OBJS} ${IOSOBJ}
        @slb %200000 =20000 -v -Lslblist_tmp ${OBJS} ${IOSOBJ}
        tsort slblist_tmp >slblist
        @rm -fv libcurses_a slblist_tmp wlist ylist

testprog :  testprog_o
        ${CC} -otestprog testprog_o ${LDFLAGS}

_x_o:
    cpp -A ${CPPFLAGS} $*_x $*_s
    ${AS} ${ASFLAGS} $*_s
    ${RM} $*_s

_x_s:
    cpp -A -dAS68 ${CPPFLAGS} $*_x $*_s

_c_o:
    ${CC} ${CFLAGS} $<

_s_o:
    ${AS} ${ASFLAGS} $<

_asm_o :
    qmac $*_asm -ERRORS $*_list -BIN $*_o -NOWINDS

_hdr_h :
    packhdr $*_hdr $*_h

clean : 
    @${RM} ${OBJS} ${IOSOBJ} ${PRGS}

#compile :	term.h
#		@for i in $(SUBDIRS);\
#		do \
#			echo "$@: started in $$i ... `date`";\
#			cd $$i; $(MAKE) $@; cd ..;\
#			echo "$@: completed in $$i ... `date`";\
#		done

#depend clean:	term.h
#		@for i in $(SUBDIRS);\
#		do \
#			echo "$@: started in $$i ... `date`";\
#			cd $$i; $(MAKE) $@; cd ..;\
#			echo "$@: completed in $$i ... `date`";\
#		done

#clobber:
#		@for i in $(SUBDIRS);\
#		do \
#			echo "$@: started in $$i ... `date`";\
#			cd $$i; $(MAKE) $@; cd ..;\
#			echo "$@: completed in $$i ... `date`";\
#		done
#		rm -f libcurses.a

#install:	libcurses.a
#		install libcurses.a
#		install curses.h /usr/include
#		install term.h /usr/include
#		install unctrl.h /usr/include

term.h:		term.basic bool.cap numeric.cap str.cap
		$(CPP) $(CPFLAGS) term.basic | \
			$(SED) -e "/^\# [0-9]*/d" -e "/^\$$/d" -e "s/!!/_/" >term.h

#---------------------------- Header File Dependencies ---------------------

${OBJS} : ${I}termios_h

_hdr_h:
    packhdr $*_hdr $*_h

# ${I}termios_hdr : termios_h
#    cp termios_h ${I}termios_hdr
