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
#ifndef SUNIM_H
#define SUNIM_H

#include "IMArg.h"
#include "IMProtocolStruct.h"

typedef struct IMHRN_ {
    char *id;			/* id */
    UTFCHAR *name;		/* HRN */
}   IMHRN, *IMHRNList;

typedef IMHRN IMLEName;
typedef IMHRN IMLocale;

/*
 * IM_VK_ to check keycode of IMKeyListEvent
 */
#define	IM_SHIFT_MASK	(1 << 0)
#define	IM_CTRL_MASK	(1 << 1)
#define	IM_META_MASK	(1 << 2)
#define	IM_ALT_MASK	(1 << 3)
#define	IM_ALT_GRAPH_MASK	(1 << 5)
#define	IM_BUTTON1_MASK	(1 << 4)
#define	IM_BUTTON2_MASK	ALT_MASK
#define	IM_BUTTON3_MASK	META_MASK

#define IM_VK_ENTER          '\n'
#define IM_VK_BACK_SPACE     '\b'
#define IM_VK_TAB            '\t'
#define IM_VK_CANCEL         0x03
#define IM_VK_CLEAR          0x0C
#define IM_VK_SHIFT          0x10
#define IM_VK_CONTROL        0x11
#define IM_VK_ALT            0x12
#define IM_VK_PAUSE          0x13
#define IM_VK_CAPS_LOCK      0x14
#define IM_VK_ESCAPE         0x1B
#define IM_VK_SPACE          0x20
#define IM_VK_PAGE_UP        0x21
#define IM_VK_PAGE_DOWN      0x22
#define IM_VK_END            0x23
#define IM_VK_HOME           0x24
#define IM_VK_LEFT           0x25
#define IM_VK_UP             0x26
#define IM_VK_RIGHT          0x27
#define IM_VK_DOWN           0x28
#define IM_VK_COMMA          0x2C
#define IM_VK_MINUS          0x2D
#define IM_VK_PERIOD         0x2E
#define IM_VK_SLASH          0x2F
#define IM_VK_0              0x30
#define IM_VK_1              0x31
#define IM_VK_2              0x32
#define IM_VK_3              0x33
#define IM_VK_4              0x34
#define IM_VK_5              0x35
#define IM_VK_6              0x36
#define IM_VK_7              0x37
#define IM_VK_8              0x38
#define IM_VK_9              0x39
#define IM_VK_SEMICOLON      0x3B
#define IM_VK_EQUALS         0x3D
#define IM_VK_A              0x41
#define IM_VK_B              0x42
#define IM_VK_C              0x43
#define IM_VK_D              0x44
#define IM_VK_E              0x45
#define IM_VK_F              0x46
#define IM_VK_G              0x47
#define IM_VK_H              0x48
#define IM_VK_I              0x49
#define IM_VK_J              0x4A
#define IM_VK_K              0x4B
#define IM_VK_L              0x4C
#define IM_VK_M              0x4D
#define IM_VK_N              0x4E
#define IM_VK_O              0x4F
#define IM_VK_P              0x50
#define IM_VK_Q              0x51
#define IM_VK_R              0x52
#define IM_VK_S              0x53
#define IM_VK_T              0x54
#define IM_VK_U              0x55
#define IM_VK_V              0x56
#define IM_VK_W              0x57
#define IM_VK_X              0x58
#define IM_VK_Y              0x59
#define IM_VK_Z              0x5A
#define IM_VK_OPEN_BRACKET   0x5B
#define IM_VK_BACK_SLASH     0x5C
#define IM_VK_CLOSE_BRACKET  0x5D
#define IM_VK_NUMPAD0        0x60
#define IM_VK_NUMPAD1        0x61
#define IM_VK_NUMPAD2        0x62
#define IM_VK_NUMPAD3        0x63
#define IM_VK_NUMPAD4        0x64
#define IM_VK_NUMPAD5        0x65
#define IM_VK_NUMPAD6        0x66
#define IM_VK_NUMPAD7        0x67
#define IM_VK_NUMPAD8        0x68
#define IM_VK_NUMPAD9        0x69
#define IM_VK_MULTIPLY       0x6A
#define IM_VK_ADD            0x6B
#define IM_VK_SEPARATER      0x6C
#define IM_VK_SUBTRACT       0x6D
#define IM_VK_DECIMAL        0x6E
#define IM_VK_DIVIDE         0x6F
#define IM_VK_DELETE         0x7F /* ASCII DEL */
#define IM_VK_NUM_LOCK       0x90
#define IM_VK_SCROLL_LOCK    0x91
#define IM_VK_F1             0x70
#define IM_VK_F2             0x71
#define IM_VK_F3             0x72
#define IM_VK_F4             0x73
#define IM_VK_F5             0x74
#define IM_VK_F6             0x75
#define IM_VK_F7             0x76
#define IM_VK_F8             0x77
#define IM_VK_F9             0x78
#define IM_VK_F10            0x79
#define IM_VK_F11            0x7A
#define IM_VK_F12            0x7B
#define IM_VK_F13            0xF000
#define IM_VK_F14            0xF001
#define IM_VK_F15            0xF002
#define IM_VK_F16            0xF003
#define IM_VK_F17            0xF004
#define IM_VK_F18            0xF005
#define IM_VK_F19            0xF006
#define IM_VK_F20            0xF007
#define IM_VK_F21            0xF008
#define IM_VK_F22            0xF009
#define IM_VK_F23            0xF00A
#define IM_VK_F24            0xF00B
#define IM_VK_PRINTSCREEN    0x9A
#define IM_VK_INSERT         0x9B
#define IM_VK_HELP           0x9C
#define IM_VK_META           0x9D
#define IM_VK_BACK_QUOTE     0xC0
#define IM_VK_QUOTE          0xDE
#define IM_VK_KP_UP          0xE0
#define IM_VK_KP_DOWN        0xE1
#define IM_VK_KP_LEFT        0xE2
#define IM_VK_KP_RIGHT       0xE3
#define IM_VK_DEAD_GRAVE               0x80
#define IM_VK_DEAD_ACUTE               0x81
#define IM_VK_DEAD_CIRCUMFLEX          0x82
#define IM_VK_DEAD_TILDE               0x83
#define IM_VK_DEAD_MACRON              0x84
#define IM_VK_DEAD_BREVE               0x85
#define IM_VK_DEAD_ABOVEDOT            0x86
#define IM_VK_DEAD_DIAERESIS           0x87
#define IM_VK_DEAD_ABOVERING           0x88
#define IM_VK_DEAD_DOUBLEACUTE         0x89
#define IM_VK_DEAD_CARON               0x8a
#define IM_VK_DEAD_CEDILLA             0x8b
#define IM_VK_DEAD_OGONEK              0x8c
#define IM_VK_DEAD_IOTA                0x8d
#define IM_VK_DEAD_VOICED_SOUND        0x8e
#define IM_VK_DEAD_SEMIVOICED_SOUND    0x8f
#define IM_VK_AMPERSAND                0x96
#define IM_VK_ASTERISK                 0x97
#define IM_VK_QUOTEDBL                 0x98
#define IM_VK_LESS                     0x99
#define IM_VK_GREATER                  0xa0
#define IM_VK_BRACELEFT                0xa1
#define IM_VK_BRACERIGHT               0xa2
#define IM_VK_AT                       0x0200
#define IM_VK_COLON                    0x0201
#define IM_VK_CIRCUMFLEX               0x0202
#define IM_VK_DOLLAR                   0x0203
#define IM_VK_EURO_SIGN                0x0204
#define IM_VK_EXCLAMATION_MARK         0x0205
#define IM_VK_INVERTED_EXCLAMATION_MARK 0x0206
#define IM_VK_LEFT_PARENTHESIS         0x0207
#define IM_VK_NUMBER_SIGN              0x0208
#define IM_VK_PLUS                     0x0209
#define IM_VK_RIGHT_PARENTHESIS        0x020A
#define IM_VK_UNDERSCORE               0x020B
#define IM_VK_FINAL                    0x0018
#define IM_VK_CONVERT                  0x001C
#define IM_VK_NONCONVERT               0x001D
#define IM_VK_ACCEPT                   0x001E
#define IM_VK_MODECHANGE               0x001F
#define IM_VK_KANA                     0x0015
#define IM_VK_KANJI                    0x0019
#define IM_VK_ALPHANUMERIC             0x00F0
#define IM_VK_KATAKANA                 0x00F1
#define IM_VK_HIRAGANA                 0x00F2
#define IM_VK_FULL_WIDTH               0x00F3
#define IM_VK_HALF_WIDTH               0x00F4
#define IM_VK_ROMAN_CHARACTERS         0x00F5
#define IM_VK_ALL_CANDIDATES           0x0100
#define IM_VK_PREVIOUS_CANDIDATE       0x0101
#define IM_VK_CODE_INPUT               0x0102
#define IM_VK_JAPANESE_KATAKANA        0x0103
#define IM_VK_JAPANESE_HIRAGANA        0x0104
#define IM_VK_JAPANESE_ROMAN           0x0105
#define IM_VK_CUT                      0xFFD1
#define IM_VK_COPY                     0xFFCD
#define IM_VK_PASTE                    0xFFCF
#define IM_VK_UNDO                     0xFFCB
#define IM_VK_AGAIN                    0xFFC9
#define IM_VK_FIND                     0xFFD0
#define IM_VK_PROPS                    0xFFCA
#define IM_VK_STOP                     0xFFC8
#define IM_VK_COMPOSE                  0xFF20
#define IM_VK_ALT_GRAPH                0xFF7E
#define IM_VK_UNDEFINED      	    0x0

#include "SunIMMMan.h"
#include "SunIMProt.h"
#include "SunIMMthd.h"
#include "SunIMPriv.h"
#include "SunIMCore.h"
#include "SunIMPub.h"

#endif	/* SUNIM_H */
