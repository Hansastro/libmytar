AC_INIT([libmytar], [1.0], [hansastro@gmail.com])
#AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE()

AC_PROG_LIBTOOL
AC_PROG_CC

AC_CHECK_HEADERS([stdio.h], , AC_MSG_ERROR(*** Can't find header stdio.h))
AC_CHECK_HEADERS([time.h], , AC_MSG_ERROR(*** Can't find header time.h))
AC_CHECK_HEADERS([fcntl.h], , AC_MSG_ERROR(*** Can't find header fcntl.h))

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
AC_OUTPUT
