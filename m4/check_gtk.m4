dnl configure script for checking GTK environment.
dnl               Author: MIYASHITA Hisashi<himi@li18nux.org>

dnl output:
dnl      HAVE_GTK
AC_DEFUN(IM_CHECK_GTK,
[
	AC_CHECK_HEADER(gtk.h, [ HAVE_GTK="yes" ])
	AC_CHECK_LIB(gtk, gtk_init, [ HAVE_LIBGTK="yes" ], , -lgdk)
	if test "X${HAVE_GTK}" = "Xyes" -a "X${HAVE_LIBGTK}" = "Xyes" ; then
		HAVE_GTK="yes"
	fi
])

dnl output:
dnl      GTK2_VERSION, GTK2_LIBDIR
AC_DEFUN(IM_CHECK_GTK2_VERSION,
[
	AC_PATH_PROG(pkg_config_prog, pkg-config, no)
	if test "X$pkg_config_prog" = "Xno" ; then
		GTK2_VERSION="none";
	else
		GTK2_VERSION=`$pkg_config_prog --modversion gtk+-2.0`
		GTK2_BINARY_VERSION=`$pkg_config_prog --variable=gtk_binary_version gtk+-2.0`
		GTK2_LIBDIR=`$pkg_config_prog --variable=libdir gtk+-2.0`
	fi
])
