m4_define([package_version_major],[0])
m4_define([package_version_minor],[6])
m4_define([package_version_micro],[3])

m4_define([libubx_if_current], [7])  dnl inc if IF added, removed or changed
m4_define([libubx_if_revision], [3]) dnl always inc if src changed, zero if current is inc'ed
m4_define([libubx_if_age], [1])      dnl inc if API changes are backwards compatible, zero otherwise

AC_INIT([ubx], [package_version_major.package_version_minor.package_version_micro])
AM_INIT_AUTOMAKE([foreign -Wall])

# compilers
AC_PROG_CC
AC_PROG_CXX

PKG_PROG_PKG_CONFIG
PKG_INSTALLDIR

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Check if the `install` program is present
AC_PROG_INSTALL

m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT(disable-static)

AC_SUBST([UBX_VER], [package_version_major.package_version_minor])
AC_SUBST([UBX_LT_VER], [libubx_if_current:libubx_if_revision:libubx_if_age])
AC_SUBST([UBX_MODDIR], [$libdir/$PACKAGE/$UBX_VER])
AC_SUBST([UBX_CFLAGS], ["-Wall -Wextra -Werror"])
AC_SUBST([UBX_IF_CURRENT], [libubx_if_current])
AC_SUBST([UBX_IF_AGE], [libubx_if_age])

AC_ARG_ENABLE([timesrc-tsc],
  AS_HELP_STRING([--enable-timesrc-tsc], [use TSC as timesource instead of POSIX time]),
  [enable_timesrc_tsc=yes],
  [])

if test "x${enable_timesrc_tsc}" = xyes; then
  AC_DEFINE([TIMESRC_TSC], 1, [use TSC as timesource instead of POSIX time])
fi

# required for TSC only
AC_DEFINE([CPU_HZ], 1600000000, [cpu hz defined])

# check for pthreads
have_pthreads=no
AC_SEARCH_LIBS([pthread_create], [pthread], [have_pthreads=yes])
if test "x${have_pthreads}" = xyes; then
  AC_CHECK_HEADERS([pthread.h], [], [have_pthreads=no])
fi
if test "x${have_pthreads}" = xno; then
  echo "---------------------------------------"
  echo "Unable to find pthreads on this system."
  echo "---------------------------------------"
  exit 1
fi

PKG_CHECK_MODULES(LUAJIT, luajit >= 2.0.4)
PKG_CHECK_MODULES(LFDS, lfds6 >= 6.1.1)

AC_CHECK_HEADERS([uthash.h])

# files to generate via autotools
AC_CONFIG_FILES([Makefile
libubx/Makefile
libubx/ubx0.pc
std_blocks/Makefile
std_blocks/cppdemo/Makefile
std_blocks/hexdump/Makefile
std_blocks/lfds_buffers/Makefile
std_blocks/logging/Makefile
std_blocks/luablock/Makefile
std_blocks/mqueue/Makefile
std_blocks/ptrig/Makefile
std_blocks/trig/Makefile
std_blocks/random/Makefile
std_blocks/const/Makefile
std_blocks/ramp/Makefile
std_blocks/simple_fifo/Makefile
std_blocks/webif/Makefile
std_types/Makefile
std_types/stdtypes/Makefile
std_types/stattypes/Makefile
std_types/testtypes/Makefile
examples/Makefile
lua/Makefile
tools/Makefile
])

# generate
AC_OUTPUT
