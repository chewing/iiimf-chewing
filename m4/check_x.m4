dnl configure script for checking X environment.
dnl               Author: MIYASHITA Hisashi<himi@li18nux.org>

dnl output:
dnl      HAVE_X
dnl      X_LIBS
dnl      X_CFLAGS
AC_DEFUN(IM_CHECK_X,
[
	AC_PATH_XTRA
	if test "X${no_x}" = "Xyes" ; then
		HAVE_X="no"
	else
		HAVE_X="yes"
	fi
	X_LIBS="${X_PRE_LIBS} ${X_LIBS} -lX11 ${X_EXTRA_LIBS}"
	X_PRIVATEINC="${IM_INCLUDEDIR}/X11/xc"
])

dnl output:
dnl      XLIB_HAS_XUTF8
AC_DEFUN(IM_CHECK_XUTF8API,
[
	ldflags_backup="${LDFLAGS}"
	LDFLAGS="${LDFLAGS} ${X_LIBS}"
	AC_MSG_CHECKING([Xutf8* APIs])
	AC_CHECK_LIB(X11, Xutf8LookupString,
	             [ XLIB_HAS_XUTF8="yes" ],
                     [ XLIB_HAS_XUTF8="no" ])

	if test "X${XLIB_HAS_XUTF8}" = "Xyes" ; then
		X_PRIVATEINC="${IM_INCLUDEDIR}/X11/XFree86"
	else
		X_PRIVATEINC="${IM_INCLUDEDIR}/X11/xc"
	fi
	
	LDFLAGS="${ldflags_backup}"
])

dnl output:
dnl       HAVE_MOTIF
AC_DEFUN(IM_CHECK_MOTIF,
[
	HAVE_MOTIF="no"
	if test "X${HAVE_X}" = "Xyes" ; then
		cflags_backup="${CFLAGS}"
		CFLAGS="${CFLAGS} ${X_CFLAGS}"
		AC_CHECK_HEADER(Xm/Xm.h, [ HAVE_MOTIF="yes" ], , [#include <X11/Xlib.h>])
		AC_CHECK_LIB(Xm, XmStringDraw, [ HAVE_LIBMOTIF="yes" ], , [${X_LIBS} -lXt])
		if test "X${HAVE_MOTIF}" = "Xyes" -a "X${HAVE_LIBMOTIF}" = "Xyes" ; then
			HAVE_MOTIF="yes"
			
		fi
		CFLAGS="${cflags_backup}"
	fi
])

dnl output:
dnl      HAVE_XICCALLBACK
AC_DEFUN(IM_TEST_XICCALLBACK,
[
	cflags_backup="${CFLAGS}"
	CFLAGS="${CFLAGS} ${X_CFLAGS}"
	AC_MSG_CHECKING([for XICCallback])
	AC_TRY_COMPILE([#include <X11/Xlib.h>],
        	       [XICCallback *callback;],
                        has_xiccallback=yes, has_xiccallback=no)
	if test $has_xiccallback = yes; then
		HAVE_XICCALLBACK="yes"
    		AC_MSG_RESULT([yes, found in X11/Xlib.h])
	else
		AC_HEADER_EGREP(XICCallback, X11/Xlib.h, has_xiccallback=yes)
		if test $has_xiccallback = yes; then
			HAVE_XICCALLBACK="yes"
			AC_MSG_RESULT([yes, found in X11/Xlib.h])
		else
			HAVE_XICCALLBACK="no"
			AC_MSG_RESULT(no)
		fi
	fi
	CFLAGS="${cflags_backup}"
])

AC_DEFUN(IM_X_SUBST,
[
	AC_SUBST(X_PRIVATEINC)
	AC_SUBST(X_LIBS)
	AC_SUBST(X_CFLAGS)
])