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

#ifndef SUNIMPRIV_H
#define SUNIMPRIV_H

#ifndef BUFSIZE
#undef BUFSIZE
#define BUFSIZE 256
#endif /* BUFSIZE */
#define SLOTMINSIZE 64
#define Private static

typedef struct {
    IMText *text;
} status_cache_t ;

/*
 * several buffer size definitions
 */
#define DEFAULTPreEditTextBufferSize 512
#define DEFAULTPreEditAttrBufferSize 512
#define DEFAULTStatusCacheSize 512
#define DEFAULTXLookupStringBufferSize 512
#define LOCALENAMELEN 64
#define DEFAULTFeedbackSize	5

/*
 * for the active_regions (just for double check)
 */
#define PREEDIT_IS_ACTIVE	0x00000001
#define STATUS_IS_ACTIVE	0x00000002
#define LOOKUP_IS_ACTIVE	0x00000004
#define AUX_IS_ACTIVE		0x00000008

/*
 * for the current_active_regions
 */
#define PREEDIT PREEDIT_IS_ACTIVE
#define STATUS  STATUS_IS_ACTIVE	
#define LOOKUP  LOOKUP_IS_ACTIVE
#define AUX     AUX_IS_ACTIVE

#define IS_REGION_ACTIVE(s, x)   (s->current_active_region & (x))
#define ACTIVATE_REGION(s, x)    (s->current_active_region |= (x))
#define INACTIVATE_REGION(s, x) (s->current_active_region &= ~(x))

#endif  /* SUNIMPRIV_H */
