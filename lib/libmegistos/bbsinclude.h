/*****************************************************************************\
 **                                                                         **
 **  FILE:    bbsinclude.h                                                  **
 **  AUTHORS: Alexios                                                       **
 **  PURPOSE: Simplify portable inclusion of header files.                  **
 **  NOTES:                                                                 **
 **  LEGALESE:                                                              **
 **                                                                         **
 **  This program is free software; you  can redistribute it and/or modify  **
 **  it under the terms of the GNU  General Public License as published by  **
 **  the Free Software Foundation; either version 2 of the License, or (at  **
 **  your option) any later version.                                        **
 **                                                                         **
 **  This program is distributed  in the hope  that it will be useful, but  **
 **  WITHOUT    ANY WARRANTY;   without  even  the    implied warranty  of  **
 **  MERCHANTABILITY or  FITNESS FOR  A PARTICULAR  PURPOSE.   See the GNU  **
 **  General Public License for more details.                               **
 **                                                                         **
 **  You  should have received a copy   of the GNU  General Public License  **
 **  along with    this program;  if   not, write  to  the   Free Software  **
 **  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.6  2003/08/15 18:40:22  alexios
 * Reinstated a minor fix that got overwitten by CVS, and fixed another
 * stupid mistake.
 *
 * Revision 1.5  2003/08/15 18:23:17  alexios
 * Fixed syntax error (d'oh!).
 *
 * Revision 1.4  2003/08/15 18:11:49  alexios
 * Added a banner.
 *
 */


/* Start by loading up autoconf definitions */

#include "bbsconfig.h"


/* Always include standard string/memory headers
   and integer types. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef STDC_HEADERS
#  define WANT_STRING_H 1
#endif
#ifdef HAVE_STDINT_H
#  include <stdint.h>
#else
#  ifdef HAVE_SYS_INT_TYPES_H
#    include <sys/int_types.h>
#  endif
#endif



/* sys/types.h and friends */

#ifdef HAVE_SYS_TYPES_H
#  include <sys/types.h>
#endif
#ifdef HAVE_SYS_INT_TYPES_H
#  include <sys/int_types.h>
#endif


/* The dirent stuff */

#ifdef WANT_DIRENT_H
#  ifdef HAVE_DIRENT_H
#    include <dirent.h>
#    define NAMLEN(dirent) strlen((dirent)->d_name)
#  else
#    define dirent dirent
#    define NAMLEN(dirent) (dirent)->d_namlen
#    ifdef HAVE_SYS_NDIR_H
#      include <sys/ndir.h>
#    endif
#    ifdef HAVE_SYS_DIR_H
#      include <sys/dir.h>
#    endif
#    ifdef HAVE_NDIR_H
#      include <ndir.h>
#    endif
#  endif
#endif


/* The dynamic loader library stuff */

#ifdef WANT_DLFCN_H
#  ifdef HAVE_DLFCN_H
#    include <dlfcn.h>
#  endif
#endif


/* The wait() function calls */

#ifdef WANT_SYS_WAIT_H
#  define WANT_WAIT_H
#endif
#ifdef WANT_WAIT_H
#  ifdef HAVE_SYS_WAIT_H
#    include <sys/wait.h>
#  endif
#  ifndef WEXITSTATUS
#    define WEXITSTATUS(stat_val) ((unsigned)(stat_val)>>8)
#  endif
#  ifndef WIFEEXITED
#    define WIFEEXITED(stat_val) (((stat_val)&255)==0)
#  endif
#endif


/* string.h and friends */

#ifdef WANT_MEMORY_H
#  define WANT_STRING_H 1
#endif
#ifdef WANT_STRINGS_H
#  define WANT_STRING_H 1
#endif
#ifdef WANT_STRING_H
#  ifdef HAVE_STRING_H
#    include <string.h>
#  endif
#  ifdef HAVE_STRINGS_H
#    include <strings.h>
#  endif
#  ifdef HAVE_MEMORY_H
#    include <memory.h>
#  endif
#endif


/* Time */

#ifdef WANT_SYS_TIME_H
#  define WANT_TIME_H 1
#endif
#ifdef WANT_TIME_H
#  ifdef TIME_WITH_SYS_TIME
#    include <sys/time.h>
#    include <time.h>
#  else
#    ifdef HAVE_SYS_TIME_H
#      include <sys/time.h>
#    else
#      include <time.h>
#    endif
#  endif
#endif


/* SLang or Curses (have to cater for several broken setups, including
   mine :-) ) */

#ifdef WANT_CURSES_H
#  define WANT_NCURSES_H 1
#endif
#ifdef WANT_SLANG_H
#  define WANT_NCURSES_H 1
#endif
#ifdef WANT_NCURSES_H
#  ifdef HAVE_LIBSLANG
#    ifdef HAVE_SLANG_SLANG_H
#      include <slang/slang.h>
#    elif defined(HAVE_SLANG_H)
#      include <slang.h>
#    endif
#    ifdef HAVE_SLANG_SLCURSES_H
#      ifndef __SLCURSES_H
#        define __SLCURSES_H
#        include <slang/slcurses.h>
#      endif
#    elif defined(HAVE_SLCURSES_H
#      ifndef __SLCURSES_H
#        define __SLCURSES_H
#        include <slcurses.h>
#      endif
#    endif
#  elif defined(HAVE_LIBNCURSES)
#    ifdef HAVE_NCURSES_H
#      include <ncurses.h>
#    elif defined(HAVE_NCURSES_NCURSES_H)
#      include <ncurses/ncurses.h>
#    elif defined(HAVE_CURSES_NCURSES_H)
#      include <curses/ncurses.h>
#    endif
#  elif defined(HAVE_LIBCURSES)
#    ifdef HAVE_CURSES_H
#      include <curses.h>
#    elif defined(HAVE_CURSES/CURSES_H)
#      include <curses/curses.h>
#    elif defined(HAVE_NCURSES/CURSES_H)
#      include <ncurses/curses.h>
#    endif
#  endif
#endif


/* Signals */

#ifdef WANT_SYS_SIGNAL_H
#define WANT_SIGNAL_H 1
#endif
#ifdef WANT_SIGNAL_H
#  ifdef HAVE_SIGNAL_H
#    include <signal.h>
#  else
#    ifdef HAVE_SYS_SIGNAL_H
#      include <sys/signal.h>
#    endif
#  endif
#endif


/* IPC */

#ifdef WANT_SYS_IPC_H
#  ifdef HAVE_SYS_IPC_H
#    include <sys/ipc.h>
#  endif
#endif
#ifdef WANT_SYS_MSG_H
#  ifdef HAVE_SYS_MSG_H
#    include <sys/msg.h>
#    ifndef MSGMAX
#      define MSGMAX 2048
#    endif
#  endif
#endif
#ifdef WANT_SYS_SHM_H
#  ifdef HAVE_SYS_SHM_H
#    include <sys/shm.h>
#  endif
#endif



/* Other header files */

#ifdef WANT_UNISTD_H
#  ifdef HAVE_UNISTD_H
#    define __EXTENSIONS__ 1
#    include <unistd.h>
#  endif
#endif

#ifdef WANT_FCNTL_H
#  ifdef HAVE_FCNTL_H
#    include <fcntl.h>
#  endif
#endif

#ifdef WANT_LIMITS_H
#  ifdef HAVE_LIMITS_H
#    include <limits.h>
#  endif
#endif

#ifdef WANT_MALLOC_H
#  ifdef HAVE_MALLOC_H
#    include <malloc.h>
#  endif
#endif

#ifdef WANT_PATHS_H
#  ifdef HAVE_PATHS_H
#    include <paths.h>
#  endif
#endif

#ifdef WANT_SGTTY_H
#  ifdef HAVE_SGTTY_H
#    include <sgtty.h>
#  endif
#endif

#ifdef WANT_SYSLOG_H
#  ifdef HAVE_SYSLOG_H
#    include <syslog.h>
#  endif
#endif

#ifdef WANT_FILE_H
#  ifdef HAVE_FILE_H
#    include <file.h>
#  endif
#endif

#ifdef WANT_IOCTL_H
#  define WANT_SYS_IOCTL_H 1
#endif
#ifdef WANT_SYS_IOCTL_H
#  ifdef HAVE_SYS_IOCTL_H
#    include <sys/ioctl.h>
#  endif
#endif

#ifdef WANT_TERMIO_H
#  define WANT_TERMIOS_H 1
#endif
#ifdef WANT_TERMIOS_H
#  ifdef HAVE_TERMIOS_H
#    include <termios.h>
#  elif defined(HAVE_SYS_TERMIOS_H)
#    include <sys/termios.h>
#  elif defined(HAVE_TERMIO_H)
#    include <termio.h>
#  elif defined(HAVE_SYS_TERMIO_H)
#    inlcude <sys/termio.h>
#  endif
#endif

#ifdef WANT_STAT_H
#  define WANT_SYS_STAT_H
#endif
#ifdef WANT_SYS_STAT_H
#  ifdef HAVE_SYS_STAT_H
#    include <sys/stat.h>
#  endif
#endif

#ifdef WANT_PWD_H
#  ifdef HAVE_PWD_H
#    include <pwd.h>
#  endif
#endif

#ifdef WANT_LINUX_ERRNO_H
#  define WANT_ERRNO_H 1
#endif
#ifdef WANT_SYS_ERRNO_H
#  define WANT_ERRNO_H 1
#endif
#ifdef WANT_ERRNO_H
#  ifdef HAVE_ERRNO_H
#    include <errno.h>
#  else
#    ifdef HAVE_SYS_ERRNO_H
#      include <sys/errno.h>
#    endif
#  endif
#endif

#ifdef WANT_GRP_H
#  ifdef HAVE_GRP_H
#    include <grp.h>
#  endif
#endif

#ifdef WANT_SYS_KD_H
#  ifdef HAVE_SYS_KD_H
#    include <sys/kd.h>
#  endif
#endif

#ifdef WANT_LINUX_VT_H
#  define WANT_SYS_VT_H 1
#endif
#ifdef WANT_SYS_VT_H
#  ifdef HAVE_SYS_VT_H
#    include <sys/vt.h>
#  endif
#endif

#ifdef WANT_LINUX_TTY_H
#  define WANT_SYS_TTY_H 1
#endif
#ifdef WANT_SYS_TTY_H
#  ifdef HAVE_SYS_TTY_H
#    include <sys/tty.h>
#  endif
#endif


#ifdef WANT_ZLIB_H
#  ifdef HAVE_ZLIB
#    ifdef HAVE_ZLIB_H
#      include <zlib.h>
#    else
#      ifdef HAVE_ZLIB_ZLIB_H
#        include <zlib/zlib.h>
#      endif
#    endif
#  endif
#endif

#ifdef WANT_VARARGS_H
#  ifdef HAVE_VARARGS_H
#    ifdef __sparc_v9__
#      undef __GCC_NEW_VARARGS__
#    endif
#    include <varargs.h>
#  elif defined(HAVE_SYS_VARARGS_H)
#    ifdef __sparc_v9__
#      undef __GCC_NEW_VARARGS__
#    endif
#    include <sys/varargs.h>
#  else
#    define WANT_STDARG_H
#  endif
#endif

#ifdef WANT_STDARG_H
#  ifdef HAVE_STDARG_H
#    include <stdarg.h>
#  endif
#endif

#ifdef WANT_GETOPT_H
#  ifdef HAVE_GETOPT_H
#    include <getopt.h>
#  endif
#endif

#ifdef WANT_SETJMP_H
#  ifdef HAVE_SETJMP_H
#    include <setjmp.h>
#  endif
#endif

#ifdef WANT_TELNET_H
#  define WANT_ARPA_TELNET_H 1
#endif
#ifdef WANT_ARPA_TELNET_H
#  ifdef HAVE_ARPA_TELNET_H
#    include <arpa/telnet.h>
#  else
#    ifdef HAVE_TELNET_H
#      include <telnet.h>
#    endif
#  endif
#endif

#ifdef WANT_UTIME_H
#  ifdef HAVE_UTIME_H
#    include <utime.h>
#  endif
#endif

#ifdef WANT_UTMP_H
#  ifdef HAVE_UTMP_H
#    include <utmp.h>
#  endif
#endif

#ifdef WANT_TERMCAP_H
#  ifdef HAVE_TERMCAP_H
#    include <termcap.h>
#  endif
#endif

#ifdef WANT_SYS_STREAM_H
#  ifdef HAVE_SYS_STREAM_H
#    include <sys/stream.h>
#  endif
#endif

#ifdef WANT_SYS_SEM_H
#  ifdef HAVE_SYS_SEM_H
#    include <sys/sem.h>
#  endif
#endif

#ifdef WANT_SYS_PARAM_H
#  ifdef HAVE_SYS_PARAM_H
#    include <sys/param.h>
#  endif
#endif

#ifdef WANT_SYS_FILIO_H
#  ifdef HAVE_SYS_FILIO_H
#    include <sys/filio.h>
#  endif
#endif

#ifdef WANT_NETINET_IN_H
#  ifdef HAVE_NETINET_IN_H
#    include <netinet/in.h>
#  endif
#endif

#ifdef WANT_RESOURCE_H
#  define WANT_SYS_RESOURCE_H 1
#endif
#ifdef WANT_SYS_RESOURCE_H
#  ifdef HAVE_SYS_RESOURCE_H
#    include <sys/resource.h>
#  endif
#endif

#ifdef WANT_SOCKET_H
#  define WANT_SYS_SOCKET_H 1
#endif
#ifdef WANT_SYS_SOCKET_H
#  ifdef HAVE_SYS_SOCKET_H
#    include <sys/socket.h>
#  endif
#endif

#ifdef WANT_SYS_UN_H
#  ifdef HAVE_SYS_UN_H
#    include <sys/un.h>
#  endif
#endif

#ifdef WANT_REGEX_H
#  ifdef HAVE_REGEX_H
#    include <regex.h>
#  else
#    ifdef HAVE_RX_H
#      include <rx.h>
#    endif
#  endif
#endif

#ifdef WANT_RPC_H
#  ifdef HAVE_RPC_H
#    include <rpc.h>
#  else
#    ifdef HAVE_RPC_RPC_H
#      include <rpc/rpc.h>
#    endif
#  endif
#endif
