dnl common configuration for im-sdk
dnl               Author: MIYASHITA Hisashi<himi@li18nux.org>

AC_DEFUN(IM_INIT,
[
	TOPDIR="$1"
	IM_ACDIR="$1/acfiles"

	PACKAGE="im-sdk"
	VERSION="11.0"

	IMDIR="/usr/lib/im"
	IMBINDIR=${IMDIR}
	IM_LEIFDIR="${IMDIR}/leif"
	IM_LOCALEDIR="${IMDIR}/locale"
	IM_TOPDIR='$(top_srcdir)'/${TOPDIR}
	IM_INCLUDEDIR="${IM_TOPDIR}/include"
	IM_LIBDIR="${IM_TOPDIR}/lib"
	CSCONV_DIR="${IM_LIBDIR}/CSConv"

	AC_ARG_ENABLE(debug,
	[  --enable-debug, Enable debug mode],
	[ enable_debug="yes"; ],
	[ enable_debug="no"; ])
	AC_ARG_ENABLE(optimize,
	[  --enable-optimize, Enable optimization],
	[ enable_optimize="yes"; ],
	[ enable_optimize="no"; ])

dnl Notice that AC_CANONICAL_TARGET must be called
dnl before AM_INIT_AUTOMAKE and IM_CHECK_SYSTEM!!!
	AC_CANONICAL_TARGET
])

AC_DEFUN(IM_SUBST,
[
	AC_SUBST(PACKAGE)
	AC_SUBST(VERSION)
	AC_SUBST(IMDIR)
	AC_SUBST(IMBINDIR)
	AC_SUBST(IM_LEIFDIR)
	AC_SUBST(IM_LOCALEDIR)
	AC_SUBST(IM_TOPDIR)
	AC_SUBST(IM_INCLUDEDIR)
	AC_SUBST(IM_LIBDIR)
	AC_SUBST(IM_ACDIR)
	AC_SUBST(CSCONV_DIR)
])

AC_DEFUN(IM_ADD_TARGET,
[
	if test "X${$2}" = "Xyes" ; then
		$1="${$1} $3"
	fi
])
