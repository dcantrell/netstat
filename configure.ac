AC_PREREQ([2.69])
AC_INIT([netstat], [1.0], [david.l.cantrell@gmail.com])
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

# Localization support is optional.
AC_ARG_ENABLE(i18n,
    AC_HELP_STRING([--enable-i18n],
                   [install translations for strings and man pages (default is no)]),
    [i18n=$enableval],
    [i18n=no])

# SELinux support is conditional and requires libraries.
AC_ARG_ENABLE(selinux,
    AC_HELP_STRING([--enable-selinux],
                   [enable SELinux support (default is no)]),
    [selinux=$enableval],
    [selinux=no])
if test x$selinux = xyes ; then
    AC_CHECK_LIB([selinux], [matchpathcon], [],
        [AC_MSG_FAILURE([*** libselinux not usable.])])
    AC_CHECK_LIB([selinux], [lsetfilecon], [],
        [AC_MSG_FAILURE([*** libselinux not usable.])])

    selinux_libs="-lselinux -laudit"
    AC_SUBST(SELINUX_CFLAGS, [-DUSESELINUX=1])
    AC_SUBST(SELINUX_LIBS, [$selinux_libs])
fi

# IPv6 support (and SIT) is not required
AC_ARG_ENABLE([ipv6],
    AC_HELP_STRING([--enable-ipv6],
                   [enable IPv6 and SIT support (default is no)]),
    [ipv6=$enableval],
    [ipv6=no])

# Bluetooth support requires additional libraries.
AC_ARG_ENABLE([bluetooth],
    AC_HELP_STRING([--enable-bluetooth],
                   [enable Bluetooth support (default is no)]),
    [bluetooth=$enableval],
    [bluetooth=no])

# Set conditional variables for Makefile.am files based on
# the --enable-* values.
AM_CONDITIONAL([ENABLE_I18N], [test x$i18n = xyes])
AM_CONDITIONAL([ENABLE_SELINUX], [test x$selinux = xyes])
AM_CONDITIONAL([ENABLE_IPV6], [test x$ipv6 = xyes])
AM_CONDITIONAL([ENABLE_BLUETOOTH], [test x$bluetooth = xyes])

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
                 man/Makefile
                 man/de_DE/Makefile
                 man/en_US/Makefile
                 man/fr_FR/Makefile
                 man/pt_BR/Makefile
                 po/Makefile])

AC_OUTPUT
