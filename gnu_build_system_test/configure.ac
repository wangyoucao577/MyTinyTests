#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([my_gnu_build_system_test], [0.1.0], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([config.h.in])

# Use automake to generate `Makefile.in` from `Makefile.am`
AM_INIT_AUTOMAKE

# generate config.h from config.h.in
AC_CONFIG_HEADERS([config.h])

# Checks for programs(compilers, etc).
AC_PROG_CC
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([sys/time.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
