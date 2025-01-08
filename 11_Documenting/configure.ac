#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([guess_number], [0.0], [arsenijbulgakov@yandex.ru], [guess_number])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN([guess_number])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)
AC_CONFIG_SRCDIR([src/guess_number.c])
AC_CONFIG_HEADERS([config.h])
AC_SUBST(GETTEXT_PACKAGE, "$PACKAGE")
ALL_LINGUAS="ru"

# Checks for programs.
AC_PROG_CC
IT_PROG_INTLTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile po/Makefile.in src/Makefile Doxyfile])

AC_OUTPUT