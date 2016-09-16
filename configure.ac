AC_PREREQ([2.69])
AC_INIT([netstat], [3.0], [david.l.cantrell@gmail.com])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([src/netstat.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

LT_INIT

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h paths.h stdlib.h \
                  string.h strings.h sys/ioctl.h sys/param.h sys/socket.h \
                  unistd.h],
                 [],
                 [AC_MSG_FAILURE([*** Header file $ac_header not found.])],
                 [])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([setlocale strchr strcspn strrchr strspn strstr strtoul \
                strtoull],
               [],
               [AC_MSG_FAILURE([*** Required function $ac_func not found.])])

# Filter CFLAGS (remove duplicate flags)
cflags_filter() {
    have=
    first=1
    for flag in $* ; do
        if test -z "`echo $have | grep -- $flag`" ; then
            if test x$first = x1 ; then
                first=2
            else
                echo -n " "
            fi
            echo -n $flag
            have="$have $flag"
        fi
    done
}
CFLAGS="$(cflags_filter $CFLAGS)"

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 po/Makefile])
AC_OUTPUT
