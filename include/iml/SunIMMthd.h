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
#ifndef  SUNIMMTHD_H
#define  SUNIMMTHD_H

#include "IMProtocolStruct.h"

#if defined(sun)
#include <thread.h>
#elif defined(WIN32)
#include <windows.h>
#else
#include <pthread.h>
#endif

#ifdef ENABLE_EIMIL
#include <EIMIL.h>
#endif


typedef struct _iml_session *iml_session;
typedef struct _iml_if_t *iml_if;
typedef struct _iml_aux *iml_aux;

typedef iml_session iml_session_list;

typedef struct _iml_desktop_t {
  /* public */
    iml_if If;				/* parent IF */

    char *user_name;			/* user info */
    char *host_name;			/* user info */
    char *display_id;			/* user info */

    void *specific_data;		/* specific data for desktop */

    iml_session_list session_list;
    int session_count;

  /* private */
    struct _iml_desktop_t *next;	/* link */
}   iml_desktop_t;

typedef iml_desktop_t *iml_desktop_list;

typedef struct _iml_methods {
    iml_inst *(*iml_make_preedit_start_inst) (iml_session);
    iml_inst *(*iml_make_preedit_draw_inst) (iml_session, IMText *);
    iml_inst *(*iml_make_preedit_draw_with_chgpos_inst) (iml_session, IMText *, int, int, int);
    iml_inst *(*iml_make_preedit_erase_inst) (iml_session);
    iml_inst *(*iml_make_preedit_caret_inst) (iml_session, int);
    iml_inst *(*iml_make_preedit_done_inst) (iml_session);

    iml_inst *(*iml_make_status_start_inst) (iml_session);
    iml_inst *(*iml_make_status_draw_inst) (iml_session, IMText *);
    iml_inst *(*iml_make_status_done_inst) (iml_session);

    iml_inst *(*iml_make_lookup_start_inst) (iml_session, IMLookupStartCallbackStruct *);
    iml_inst *(*iml_make_lookup_draw_inst) (iml_session, IMLookupDrawCallbackStruct *);
    iml_inst *(*iml_make_lookup_done_inst) (iml_session);

    iml_inst *(*iml_make_start_conversion_inst) (iml_session);
    iml_inst *(*iml_make_end_conversion_inst) (iml_session);

    iml_inst *(*iml_make_commit_inst) (iml_session, IMText *);
    iml_inst *(*iml_make_keypress_inst) (iml_session, IMKeyEventStruct *);

    iml_inst *(*iml_make_aux_start_inst) (iml_session, IMAuxStartCallbackStruct *);
    iml_inst *(*iml_make_aux_draw_inst) (iml_session, IMAuxDrawCallbackStruct *);
    iml_inst *(*iml_make_aux_done_inst) (iml_session, IMAuxDoneCallbackStruct *);
    void *(*iml_new) (iml_session, int);
    void *(*iml_new2) (iml_session, int);
    void *(*iml_delete) (iml_session);
    void *(*iml_delete2) (iml_session);

    iml_inst *(*iml_link_inst_tail) (iml_inst **, iml_inst *);
    iml_inst *(*iml_execute) (iml_session, iml_inst **);

}   iml_methods_t;

typedef struct _if_methods {
    Bool(*if_OpenIF) (iml_if);
    Bool(*if_CloseIF) (iml_if);
    Bool(*if_GetIFValues) (iml_if, IMArgList, int);
    Bool(*if_SetIFValues) (iml_if, IMArgList, int);

    Bool(*if_OpenDesktop) (iml_desktop_t *, IMArgList, int);
    Bool(*if_CloseDesktop) (iml_desktop_t *);

    Bool(*if_CreateSC) (iml_session, IMArgList, int);
    Bool(*if_DestroySC) (iml_session);
    Bool(*if_GetSCValues) (iml_session, IMArgList, int);
    Bool(*if_SetSCValues) (iml_session, IMArgList, int);

    IMText *(*if_ResetSC) (iml_session);

    void (*if_SetSCFocus) (iml_session);
    void (*if_UnsetSCFocus) (iml_session);

    void (*if_SendEvent) (iml_session, IMInputEvent *);
}   if_methods_t;

/*
 * Per interface data structure
 */
typedef struct _iml_if_t {
  /* public */
    char *if_name;				/* id */
    char *if_version;				/* version */
    char *locale;				/* locale */

    iml_methods_t *m;				/* link for iml methods */

    iml_desktop_list desktop_list;		/* list for child desktop */
    int desktop_count;

    char *ifpath_name;				/* location of if module */

  /* private */
    if_methods_t *ifm;

    void *dl_module;

    IMLEName *lename;
    IMLocale *locale_list;
    IMObjectDescriptorStruct *object_list;

    Bool xsunim;
    Bool need_thread_lock;
#ifdef	USE_SUNIM_ADAPTER
    Bool need_adapter;
#endif	/* USE_SUNIM_ADAPTER */

#ifdef ENABLE_EIMIL
    EIMIL_handle eh;
#endif
}   iml_if_t;

typedef enum {
    IF_VERSION = 1,
    IF_METHOD_TABLE,
    IF_LE_NAME,
    IF_SUPPORTED_LOCALES,
    IF_SUPPORTED_OBJECTS,
#ifdef	USE_SUNIM_ADAPTER
    IF_NEED_THREAD_LOCK,
    IF_HAVE_LOCALE_DEPENDENCY,
#else	/* USE_SUNIM_ADAPTER */
    IF_NEED_THREAD_LOCK,
#endif	/* USE_SUNIM_ADAPTER */

    /* EIMIL extension */
    IF_EIMIL_HANDLE = 0x100

}   IF_Attribute;

typedef enum {
    SC_REALIZE = 1,
    SC_TRIGGER_ON_NOTIFY,
    SC_TRIGGER_OFF_NOTIFY,
    SC_SUPPORTED_CHARACTER_SUBSETS,

    SC_PREFERED_OBJECTS = 64,
    SC_SUPPORTED_CLASSES = 65,
    SC_LOOKUP_NROWS = 100,		/* for compatibility purpose */
    SC_LOOKUP_NCOLS,			/* for compatibility purpose */
    SC_LOOKUP_LABELTYPE			/* for compatibility purpose */
}   SC_Attribute;

typedef enum {
    UI_USER_NAME = 1,
    UI_HOST_NAME,
    UI_DISPLAY_ID,
    UI_PROTOCOL_TYPE,
    UI_CLIENT_TYPE,
    UI_OS_NAME,
    UI_OS_ARCH,
    UI_OS_VERSION,
    UI_XSERVER_VENDOR,
    UI_AUTH_PASSWD
}   UI_Attribute;

#define	MAX_UI_ATTRIBUTE	UI_AUTH_PASSWD

#define UI_PROTOCOL_TYPE_IIIMP	"IIIMP"
#define UI_PROTOCOL_TYPE_XIMP	"XIMP"
#define UI_PROTOCOL_TYPE_XIMCP	"XIMCP"

#define UI_CLIENT_TYPE_JAVA	"JAVA"
#define UI_CLIENT_TYPE_X	"X"
#define UI_CLIENT_TYPE_UNKNOWN	"Unknown"

#endif				/* SUNIMMTHD_H */
