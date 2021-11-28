# -*- autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libmegistos1], [1.0], [alexios@bedroomlan.org])

AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([bbs.h])
AC_CONFIG_HEADERS([autoconf.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lmegistos':
AC_CHECK_LIB([megistos], [bbs_init])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h libintl.h limits.h locale.h malloc.h memory.h netinet/in.h paths.h sgtty.h stdint.h stdlib.h string.h strings.h sys/ioctl.h sys/param.h sys/socket.h sys/time.h syslog.h termio.h termios.h unistd.h utime.h utmp.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_CHOWN
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_CHECK_FUNCS([atexit bzero gettimeofday memset select setlocale socket strchr strcspn strdup strerror strrchr strspn strstr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT