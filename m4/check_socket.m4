dnl system checking configure definitions for im-sdk
dnl               Author: MIYASHITA Hisashi<himi@li18nux.org>

dnl output:
dnl       HAVE_SOCKET
dnl       HAVE_GETADDRINFO
dnl       HAVE_GETHOSTBYADDR
dnl       SOCKET_LIBS
AC_DEFUN(IM_CHECK_SOCKET,
[
	socket_lib_flag=""
	nsl_lib_flag=""

dnl     candidates: socket, connect, getaddrinfo, accept, setsockopt, listen...
	AC_CHECK_FUNCS(socket, [ HAVE_SOCKET="yes" ])
	AC_CHECK_FUNCS(getaddrinfo, [ HAVE_GETADDRINFO="yes" ])
	AC_CHECK_FUNCS(gethostbyaddr, [ HAVE_GETHOSTBYADDR="yes" ])

	if test "X${HAVE_SOCKET}" != "Xyes"; then
		AC_CHECK_LIB(socket, socket,
                             [ socket_lib_flag="-lsocket";
                               HAVE_SOCKET="yes";
	                       AC_DEFINE(HAVE_SOCKET) ])
		AC_CHECK_LIB(socket, getaddrinfo,
                             [ socket_lib_flag="-lsocket";
                               HAVE_GETADDRINFO="yes";
	                       AC_DEFINE(HAVE_GETADDRINFO) ])
		AC_CHECK_LIB(socket, gethostbyaddr,
                             [ socket_lib_flag="-lsocket";
                               HAVE_GETHOSTBYADDR="yes";
	                       AC_DEFINE(HAVE_GETHOSTBYADDR) ])
	fi
	if test "X${HAVE_GETADDRINFO}" != "Xyes"; then
		AC_CHECK_LIB(nsl, getaddrinfo,
                             [ nsl_lib_flag="-lnsl";
                               HAVE_GETADDRINFO="yes";
	                       AC_DEFINE(HAVE_GETADDRINFO) ])
	fi
	if test "X${HAVE_GETHOSTBYADDR}" != "Xyes"; then
		AC_CHECK_LIB(nsl, gethostbyaddr,
                             [ nsl_lib_flag="-lnsl";
                               HAVE_GETHOSTBYADDR="yes";
	                       AC_DEFINE(HAVE_GETHOSTBYADDR) ])
	fi
	SOCKET_LIBS="${socket_lib_flag} ${nsl_lib_flag}"
	AC_SUBST(SOCKET_LIBS)
])
