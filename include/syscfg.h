#ifndef IM_SDK_SYSCFG_H_
#define IM_SDK_SYSCFG_H_

/***************************************
                 alloca
 ***************************************/

/* system dependent alloca definitions */
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#elif defined(__GNUC__)
#define alloca __builtin_alloca
#elif defined __DECC
#include <alloca.h>
#pragma intrinsic(alloca)
#elif defined(_AIX)
#pragma alloca
#elif ! defined (alloca)
void *alloca ();
#endif

/***************************************
             non-ANSI functions.
 ***************************************/

/* check functions. */

#ifndef HAVE_BCOPY
#define bcopy(src, dest, size) memcpy((dest), (src), (size))
#endif

#ifndef HAVE_BZERO
#define bzero(p, size) memset((p), 0, (size))
#endif

#ifndef HAVE_BCMP
#define bcmp(p1, p2, size) memcmp((p1), (p2), (size))
#endif

#ifndef HAVE_INDEX
#define index(s, c) strchr((s), (c))
#endif

#ifndef HAVE_RINDEX
#define rindex(s, c) strrchr((s), (c))
#endif

/***************************************
               ASSERTION
 ***************************************/

#ifndef ASSERT
#ifdef DEBUG
#define ASSERT(X)				\
do {						\
    if (!(X)) {					\
	fprintf(stderr, "ASSERT %s: %s (%d)\n",	\
		#X, __FILE__, __LINE__);	\
		abort();			\
    }						\
} while(0)
#else
#define ASSERT(X) ((void) 0)
#endif
#endif

#define ERROR_INTERNAL(X)				\
do {							\
    fprintf(stderr, "Internal error %s: %s (%d)\n",	\
	    #X, __FILE__, __LINE__);			\
	    abort();					\
} while(0)

/***************************************
            INTEGER TYPES
 ***************************************/

#define DEFINED_INTEGER_TYPES

#if SIZEOF_UNSIGNED_INT == 1
typedef unsigned int CARD8BIT;
#elif SIZEOF_UNSIGNED_LONG == 1
typedef unsigned long CARD8BIT;
#elif SIZEOF_UNSIGNED_SHORT == 1
typedef unsigned short CARD8BIT;
#elif SIZEOF_UNSIGNED_CHAR == 1
typedef unsigned char CARD8BIT;
#else
#error "Fail to find a 8-bit sized integer type."
#endif

#if SIZEOF_UNSIGNED_INT == 2
typedef unsigned int CARD16BIT;
#elif SIZEOF_UNSIGNED_LONG == 2
typedef unsigned long CARD16BIT;
#elif SIZEOF_UNSIGNED_SHORT == 2
typedef unsigned short CARD16BIT;
#elif SIZEOF_UNSIGNED_CHAR == 2
typedef unsigned char CARD16BIT;
#else
#error "Fail to find a 16-bit sized integer type."
#endif

#if SIZEOF_UNSIGNED_INT == 4
typedef unsigned int CARD32BIT;
#elif SIZEOF_UNSIGNED_LONG == 4
typedef unsigned long CARD32BIT;
#elif SIZEOF_UNSIGNED_SHORT == 4
typedef unsigned short CARD32BIT;
#elif SIZEOF_UNSIGNED_CHAR == 4
typedef unsigned char CARD32BIT;
#else
#error "Fail to find a 32-bit sized integer type."
#endif

/***************************************
            ENDS HERE
 ***************************************/

#endif /* IM_SDK_SYSCFG_H_ */
