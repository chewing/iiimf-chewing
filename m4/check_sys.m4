dnl system checking configure definitions for im-sdk
dnl               Author: MIYASHITA Hisashi<himi@li18nux.org>

AC_DEFUN(IM_SYSTEM_AUTOHEADER,
[
AH_VERBATIM([ARCH], [/* architecture */
#ifndef ARCH
#define ARCH
#endif])
])

AC_DEFUN(IM_CHECK_SYSTEM,
[
dnl     This must be called beforehand!
dnl	AC_CANONICAL_TARGET
	ARCH="${host_cpu}"
	AC_DEFINE_UNQUOTED(ARCH, "\"${ARCH}\"")

## Checks for programs

	AC_PROG_CC
	AC_PROG_CXX
	AC_PROG_CPP
	AC_PROG_INSTALL
	AC_PROG_LN_S
	AC_PROG_MAKE_SET
	AC_PROG_RANLIB

## Checks for header files.

	AC_HEADER_DIRENT
	AC_HEADER_STDC
	AC_HEADER_SYS_WAIT
	AC_CHECK_HEADERS(fcntl.h limits.h malloc.h errno.h stddef.h string.h strings.h)
	AC_CHECK_HEADERS(sys/ioctl.h sys/time.h sys/param.h sys/systeminfo.h)
	AC_CHECK_HEADERS(syslog.h unistd.h)
	AC_CHECK_HEADERS(langinfo.h locale.h wchar.h)

## Checks for typedefs, structures, and compiler characteristics.

	AC_C_CONST
	AC_TYPE_PID_T
	AC_TYPE_SIZE_T
	AC_HEADER_TIME
	AC_STRUCT_TM
	AC_TYPE_UID_T

## Checks for library functions.

	AC_FUNC_ALLOCA
	AC_PROG_GCC_TRADITIONAL
	AC_FUNC_MEMCMP
	AC_FUNC_SETPGRP
	AC_FUNC_SETVBUF_REVERSED
	AC_TYPE_SIGNAL
	AC_FUNC_VPRINTF
	AC_FUNC_WAIT3
	AC_FUNC_MMAP
	AC_CHECK_FUNCS(gethostname gettimeofday sysinfo)
	AC_CHECK_FUNCS(mkdir putenv uname endpwent)
	AC_CHECK_FUNCS(memmove memset)
	AC_CHECK_FUNCS(nl_langinfo setlocale)
	AC_CHECK_FUNCS(strdup strerror strstr strchr strrchr strspn strtol)
	AC_CHECK_FUNCS(bcopy bzero bcmp index rindex fork fork1 signal)
	AC_CHECK_FUNCS(poll select)

## Checks the size of standard types
	AC_CHECK_SIZEOF(unsigned int)
	AC_CHECK_SIZEOF(unsigned long)
	AC_CHECK_SIZEOF(unsigned short)
	AC_CHECK_SIZEOF(unsigned char)

## Checks for thread library.
	AC_CHECK_LIB(pthread, pthread_create, [ HAVE_LIBPTHREAD="yes" ])
	AC_CHECK_LIB(thread, thr_create, [ HAVE_LIBUITHREAD="yes" ])
	if test "X${HAVE_LIBPTHREAD}" = "Xyes" ; then
		HAVE_THREAD="pthread"
	elif test "X${HAVE_LIBUITHREAD}" = "Xyes" ; then
		HAVE_THREAD="uithread"
	else
		HAVE_THREAD="no"
	fi
])

AC_DEFUN(IM_CHECK_DLOPEN,
[
	DLOPEN_CXX_CFLAGS=""
	AC_CHECK_HEADERS(dlfcn.h, [ HAVE_DLFCN_H="yes" ])
	AC_CHECK_LIB(dl, dlopen, [ HAVE_LIBDL="yes" ])
	if test "X${HAVE_DLFCN_H}" = "Xyes" -a "X${HAVE_LIBDL}" = "Xyes" ; then
		HAVE_DLOPEN="yes"
		DLOPEN_LIBS="-ldl"
	fi
])

AC_DEFUN(IM_CONSTRUCT_FLAGS,
[
	COMMON_CXX_CFLAGS="-I${srcdir} -I${IM_INCLUDEDIR} -DARCH=\\\"${ARCH}\\\" -DHAVE_CONFIG_H"
	COMMON_CFLAGS=""
	COMMON_CXXFLAGS=""

	DEBUG_CXX_CFLAGS="-DDEBUG"
	DEBUG_CFLAGS=""
	DEBUG_CXXFLAGS=""

	OPTIMIZE_CXX_CFLAGS="-O2"
	OPTIMIZE_CFLAGS=""
	OPTIMIZE_CXXFLAGS=""

	DISABLE_OPTIMIZE_CXX_CFLAGS="-O0"

	COMMON_LDFLAGS=""
	THREAD_LDFLAGS=""

	REQUIREDCPPLIB="-lc"

	AR=ar
	AR_FLAGS="rc"

	SHLIBCFLAGS=""
	SHLIBLDFLAGS=""

	case "${CC}:${CXX}" in
	    gcc*:g++* | gcc*:gcc*)
		DEBUG_CXX_CFLAGS="${DEBUG_CXX_CFLAGS} -ggdb"
		COMMON_CXXFLAGS="${COMMON_CXXFLAGS} -fexceptions"
		SHLIBCFLAGS='-fpic'
		SHLIBLDFLAGS='-shared'
		if test "X${with_defaultcxxlibs}" != "Xyes" ; then
#		    REQUIREDCPPLIB="-nodefaultlibs -lc";
		    CXX=${CC}
		fi
		;;
	    gcc*:*)
		DEBUG_CFLAGS="${DEBUG_CFLAGS} -ggdb"
		DEBUG_CXXFLAGS="${DEBUG_CXXFLAGS} -g"
		SHLIBCFLAGS='-fpic'
		SHLIBLDFLAGS='-shared'
		;;
	    *:g++* | *:gcc*)
		DEBUG_CXXFLAGS="${DEBUG_CXXFLAGS} -ggdb"
		DEBUG_CFLAGS="${DEBUG_CFLAGS} -g"
		COMMON_CXXFLAGS="${COMMON_CXXFLAGS} -fexceptions"
		SHLIBCFLAGS='-fpic'
		SHLIBLDFLAGS='-shared'
		if test "X${with_defaultcxxlibs}" != "Xyes" ; then
#		    REQUIREDCPPLIB="-nodefaultlibs -lc";
		    CXX=${CC}
		fi
		;;
	    *)
		DEBUG_CXX_CFLAGS="${DEBUG_CXX_CFLAGS} -g"
		;;
	esac

	case "${target}@${CC}:${CXX}%${LINKER}" in
	    *solaris*@cc:*)
		COMMON_CFLAGS="${COMMON_CFLAGS} -Xa"
		THREAD_CXX_CFLAGS="-mt"
		COMMON_LDFLAGS="${COMMON_LDFLAGS} -norunpath"
		SHLIBCFLAGS='-xF -Kpic'
		SHLIBLDFLAGS='-G -z text -z defs -M mapfile.$@'
		OPTIMIZE_CXX_CFLAGS="-O"
		DISABLE_OPTIMIZE_CXX_CFLAGS=""
		if test "X${with_defaultcxxlibs}" != "Xyes" ; then
		    REQUIREDCPPLIB="-nolib -lc";
		fi
		;;
	    *solaris*@gcc:*)
		SHLIBLDFLAGS='${SHLIBLDFLAGS} -Wl,-ztext -Wl,-zdefs -Wl,-Mmapfile.$@'
		;;
	esac	

# system dependent definitions

	case "${target}" in
	    *solaris*)
		COMMON_CXX_CFLAGS="${COMMON_CXX_CFLAGS} -DSunOS -Dsun -DSVR4"
	        COMMON_CXX_CFLAGS="${COMMON_CXX_CFLAGS} -D_XPG5"
		if test "X${enable_direct_xsunim}" = "Xyes" ; then
		    COMMON_CXX_CFLAGS="${COMMON_CXX_CFLAGS} -DUSE_XSUNIM"
		else
		    COMMON_CXX_CFLAGS="${COMMON_CXX_CFLAGS} -DUSE_XSUNIM_ADAPTER"
		fi
		if test "X${HAVE_LIBDOOR}" = "Xyes" ; then
		    COMMON_CXX_CFLAGS="${COMMON_CXX_CFLAGS} -DUSE_DOOR"
		    IPC_LIBS="-ldoor"
		fi
		;;
	    *cygwin*)
		COMMON_CXX_CFLAGS="${COMMON_CXX_CFLAGS} -DWIN32 -DCYGWIN_NT"
		;;
	    *linux*)
		COMMON_CXX_CFLAGS="${COMMON_CXX_CFLAGS} -DLinux"
		;;
	    *freebsd*)
		THREAD_LDFLAGS="-pthread"
		PTHREAD_LIBS=""
		;;
	esac

# disable debug flags.
	if test "X${enable_debug}" = "Xyes" ; then
		if test "X${enable_optimize}" = "Xno" ; then
			DEBUG_CXX_CFLAGS="${DEBUG_CXX_CFLAGS} ${DISABLE_OPTIMIZE_CXX_CFLAGS}"
		fi
	else
		DEBUG_CXX_CFLAGS=""
		DEBUG_CFLAGS=""
		DEBUG_CXXFLAGS=""
	fi
	if test "X${enable_optimize}" = "Xyes" ; then
		COMMON_CXX_CFLAGS="${COMMON_CXX_CFLAGS} ${OPTIMIZE_CXX_CFLAGS}"
		COMMON_CFLAGS="${COMMON_CFLAGS} ${OPTIMIZE_CFLAGS}"
		COMMON_CXXFLAGS="${COMMON_CXXFLAGS} ${OPTIMIZE_CXXFLAGS}"
	fi

])

;;  output:
;;       THREAD_CXX_CFLAGS
;;       THREAD_LDFLAGS
;;       THREAD_LIBS
AC_DEFUN(IM_CONSTRUCT_THREAD_FLAGS,
[
	THREAD_CXX_CFLAGS=""
	THREAD_LDFLAGS=""
	THREAD_LIBS=""
	if test "X${HAVE_THREAD}" = "Xno" ; then
		AC_MSG_WARN("Have no thread system.")
	else
		if test "${HAVE_THREAD}" = "pthread" ; then
			THREAD_LIBS="-lpthread"
		    	THREAD_CXX_CFLAGS="${THREAD_CXX_CFLAGS} -D_POSIX_C_SOURCE=199506L"
		elif test "${HAVE_THREAD}" = "uithread" ; then
			THREAD_LIBS="-lthread"
			THREAD_CXX_CFLAGS="${THREAD_CXX_CFLAGS} -D_REENTRANT"
			THREAD_LIBS="-lthread"
		fi

	fi

# Check precisely.
	case "${target}@${CC}:${CXX}%${LINKER}" in
	    *solaris*@cc:*)
		THREAD_CXX_CFLAGS="-mt"
		;;
	    *freebsd*@gcc:*)
		THREAD_LDFLAGS="-pthread"
		THREAD_LIBS=""
		;;
	    *linux*)
		THREAD_CXX_CFLAGS="${THREAD_CXX_CFLAGS} -D_SVID_SOURCE -D_BSD_SOURCE"
		;;
	esac	
])

AC_DEFUN(IM_SYSTEM_SUBST,
[
# System Info.
	AC_SUBST(ARCH)

# Utilities
	AC_SUBST(CC)
	AC_SUBST(CXX)
	AC_SUBST(LINKER)
	AC_SUBST(AR)
	AC_SUBST(LN_S)
	AC_SUBST(MAKEDEPEND)

# Command Line Options
	AC_SUBST(LIBS)
	AC_SUBST(REQUIREDCPPLIB)
	AC_SUBST(CFLAGS)
	AC_SUBST(CXXFLAGS)
	AC_SUBST(LDFLAGS)
	AC_SUBST(AR_FLAGS)
	AC_SUBST(SHLIBCFLAGS)
	AC_SUBST(SHLIBLDFLAGS)

# Thread
	AC_SUBST(THREAD_CXX_CFLAGS)
	AC_SUBST(THREAD_LDFLAGS)
	AC_SUBST(THREAD_LIBS)

# DLOPEN
	AC_SUBST(DLOPEN_CXX_CFLAGS)
	AC_SUBST(DLOPEN_LIBS)
])

