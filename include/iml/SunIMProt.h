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
#ifndef SUNIMPROT_H
#define SUNIMPROT_H

#ifndef Private
#define Private static
#define Public	/**/
#endif	/* Private */

/*
 * This is for public_status in iml_session_t/status in IC. Used by
 * IML_SET_STATUS/IML_GET_STATUS
 */
typedef int iml_status_t;

#define IMLSTATUS_Henkan_Mode                 0x00000001
#define IMLSTATUS_Mode_switch                 0x00000002
#define IMLSTATUS_Backfront                   0x00000004	/* if 1, backend */
#define IMLSTATUS_Backfront_Recommendation    0x00000008	/* if 1, backend */

/* ------------------------------------------------------------ */

/*
 * IML to IMM opcode
 */
typedef unsigned int IMM_Opcode;

#define IMM_NOP                  0	/* Nop */

#define IMM_RESET                1	/* Reset the IC */

#define IMM_COMMIT               2	/* Returning a committed
					 * string */

#define IMM_SET_STATUS           3	/* iml status i.e.ConvOn/off
					 * kana etc.. */

#define IMM_PREEDIT_START        4	/* Call the preedit_start
					 * callback */

#define IMM_PREEDIT_DRAW         5	/* Call the preedit_draw
					 * callback */

#define IMM_PREEDIT_CARET        6	/* Call the preedit_caret
					 * callback */

#define IMM_PREEDIT_DONE         7	/* Call the preedit_done call
					 * back */

#define IMM_LOOKUP_START         8	/* Call the lookup_start
					 * callback */

#define IMM_LOOKUP_DRAW          9	/* Call the lookup_draw
					 * callback */

#define IMM_LOOKUP_PROCESS      10	/* Call the lookup_process
					 * callback */

#define IMM_LOOKUP_DONE         11	/* Call the lookup_done
					 * callback */

#define IMM_KEY_INFO            12	/* Return the key that
					 * corresponds to */
/* specified function */
/* operand : keymaps_t */
#define IMM_PUT_QUEUE           13	/* Put the string back to X
					 * queue */

#define IMM_STATUS_START        14	/* Call the status_start
					 * callback */

#define IMM_STATUS_DRAW         15	/* Call the status_draw
					 * callback */

#define IMM_STATUS_DONE         16	/* Call the status_done
					 * callback */

#define IMM_KEYPRESS            17	/* Return X event to the
					 * client */

#define IMM_RESET_RETURN        18	/* same as commit */

#define IMM_AUX_START_2		20	/* Call the aux_start
					 * callback */

#define IMM_AUX_DRAW_2		21	/* Call the aux_draw callback */

#define IMM_AUX_DONE_2		22	/* Call the aux_done callback */

#define IMM_OBJECTDOWNLOADING	23	/* Call the aux_done callback */

#define MAX_IMM_OPCODE          24	/* maximam opcode value */

#define IMM_CB_RESULT_REQUIRED  0x10000000

/*
 * iml_inst structure
 */
typedef struct _iml_inst {
    struct _iml_inst *next;
    int size_of_operand;
    IMM_Opcode opcode;
    char *operand;
}   iml_inst;

#endif /* SUNIMPROT_H */
