/*
Copyright 1990-2001 Sun Microsystems, Inc. All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions: The above copyright notice and this
permission notice shall be included in all copies or substantial
portions of the Software.


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP OR SUN MICROSYSTEMS, INC. BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE EVEN IF
ADVISED IN ADVANCE OF THE POSSIBILITY OF SUCH DAMAGES.


Except as contained in this notice, the names of The Open Group and/or
Sun Microsystems, Inc. shall not be used in advertising or otherwise to
promote the sale, use or other dealings in this Software without prior
written authorization from The Open Group and/or Sun Microsystems,
Inc., as applicable.


X Window System is a trademark of The Open Group

OSF/1, OSF/Motif and Motif are registered trademarks, and OSF, the OSF
logo, LBX, X Window System, and Xinerama are trademarks of the Open
Group. All other trademarks and registered trademarks mentioned herein
are the property of their respective owners. No right, title or
interest in or to any trademark, service mark, logo or trade name of
Sun Microsystems, Inc. or its licensors is granted.

*/
#ifndef SUNIMCORE_H
#define SUNIMCORE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef ENABLE_EIMIL
#include <EIMIL.h>
#endif

typedef struct _iml_inst_mem_block_list	iml_inst_mem_block_list_t;
typedef struct _iml_inst_mem_elem_list	iml_inst_mem_elem_list_t;

typedef struct _iml_session {
  /* public */
    iml_if_t *If;			/* parent IF */
    iml_desktop_t *desktop;		/* parent desktop */
    void *specific_data;		/* specific data per session */
    int current_active_region;		/* check active region */
    int public_status;			/* check conversion on/off */

  /* private */
    IMPreeditDrawCallbackStruct PreEditTextInfo; /* preedit cache */
    int PreEditTextBufferSize;
    int PreEditAttrBufferSize;

    status_cache_t status_cache;		/* cache for status string */

    iml_inst_mem_block_list_t *mem_block_short_term_small;
    iml_inst_mem_elem_list_t *mem_elem_short_term;
    iml_inst_mem_elem_list_t *mem_elem_long_term;

    void *SessionContext;			/* reference for iml_execute() */

    struct _iml_session *next;			/* link */

#ifdef ENABLE_EIMIL
  // Note that this new member may brake ABI...
    EIMIL_handle eh;
#endif

}   iml_session_t;

#endif
