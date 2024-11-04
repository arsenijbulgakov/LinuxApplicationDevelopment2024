#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [0.00], [arsenijbulgakov@yandex.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])


# Checks for programs.
AC_PROG_CC

# Checks for libraries.

AC_ARG_WITH([readline],
            [AS_HELP_STRING([--with-readline],
              [enable experimental support for readline])],
            [],
            [with_readline=no])
          
LIBREADLINE=
AS_IF([test "x$with_readline" != xno],
            [AC_CHECK_LIB([readline], [readline],
              [AC_SUBST([LIBREADLINE], ["-lreadline"])
               AC_DEFINE([USE_LIBREADLINE], [1],
                         [Define if you have libreadline])
              ])])

CFLAGS="$CFLAGS -I /usr/local/include"
LDFLAGS="$LDFLAGS -L /usr/local/lib $LIBREADLINE"

AC_CHECK_LIB([rhash],[rhash_msg],[],[AC_MSG_ERROR([rhash is needed])])

# Checks for header files.
AC_CHECK_HEADER([rhash.h], [], [AC_MSG_ERROR([Unable to find rhash.h])])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT