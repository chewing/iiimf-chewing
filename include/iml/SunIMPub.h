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
#ifndef SUNIMPUB_H
#define SUNIMPUB_H

#ifdef __cplusplus
extern "C" {
#endif
extern iml_inst *iml_execute_iml_wrapper(
    iml_session_t *s,
    iml_inst **rrv
);
extern iml_if_t *if_OpenIF(
    const char *if_path,
    const char *if_name,
    const char *locale,
    Bool call_openif
);
extern void if_CloseIF(
    iml_if_t *iml_if,
    Bool call_closeif
);
extern Bool if_GetIFValues(iml_if_t *, IMArgList, int);
extern Bool if_SetIFValues(iml_if_t *, IMArgList, int);
extern iml_session_t *if_CreateSC(iml_if_t *, IMArgList, int);
extern Bool if_DestroySC(iml_session_t *);
extern Bool if_DestroySC_WithoutDesktopDestruction(iml_session_t *);
extern Bool if_GetSCValues(iml_session_t *, IMArgList, int);
extern Bool if_SetSCValues(iml_session_t *, IMArgList, int);
extern void if_SendEvent(iml_session_t *, IMInputEvent *);
extern IMText *if_ResetSC(iml_session_t *);
extern void if_SetSCFocus(iml_session_t *);
extern void if_UnsetSCFocus(iml_session_t *);
extern void sunim_slot_manager_init();

#ifdef	USE_XSUNIM_ADAPTER
extern void xsunim_slot_manager_init();
#endif /* USE_XSUNIM_ADAPTER */

extern iml_session_t *iml_construct_session(iml_desktop_t *, IMArgList, int);
extern iml_desktop_t *new_user(
    iml_if_t * If,
    const char *user_name,
    const char *host_name,
    const char *display_id
);
extern void del_user(
    iml_desktop_t * desktop
);
extern void add_session_to_desktop(
    iml_session_t *s
);

/****************************************
       IMLSubr.c
 ****************************************/
extern iml_inst* iml_duplicate_inst(
    iml_inst *pinst
);
extern void iml_delete_inst(
    iml_inst *pinst
);

extern int IMText_duplicate2(
    IMText *pdest, IMText *psrc
);
extern IMText* IMText_duplicate(
    IMText *psrc
);
extern void IMText_delete2(
    IMText *ptext
);
extern void IMText_delete(
    IMText *ptext
);

#ifdef __cplusplus
}
#endif

#endif /* SUNIMPUB_H */

/* Local Variables: */
/* c-file-style: "iiim-project" */
/* End: */
