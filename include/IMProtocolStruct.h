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
#ifndef _improtocolstruct_hh
#define _improtocolstruct_hh

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef Bool
typedef enum {
  True=1, False=0
} Bool;
#endif

#define IMID int

typedef unsigned short UTFCHAR;

#define NoSymbol        0L
#define BufferOverflow         -1
#define LookupNone             1
#define LookupChars            2
#define LookupKeySym           3
#define LookupBoth             4

typedef enum {
  IM_DECORATION_FEEDBACK = 0,	/* IMNormal, IMReverse, IMUnderline */
  IM_FOREGROUND_RGB_FEEDBACK = 1,
  IM_BACKGROUND_RGB_FEEDBACK = 2,
  IM_UNDERLINE_RGB_FEEDBACK = 3
} IMFeedbackType;

typedef enum {
  IM_ANNOTATION_INPUT_STRING = 1,
  IM_ANNOTATION_READING = 2,
  IM_ANNOTATION_SPEECH = 3,
  IM_ANNOTATION_CLAUSE = 4,

  IM_ANNOTATION_FEEDBACK = 0x10,
  IM_ANNOTATION_CURRENT = 0x12,
  IM_ANNOTATION_CANDIDATES = 0x11,
  IM_ANNOTATION_SELECTED_CANDIDATES = 0x12
} IMAnnotationType;

typedef struct _IMAnnotationValue {
  int start_pos;
  int end_pos;
  int len;
  void *value;
} IMAnnotationValue;

#define IM_FEEDBACK_COUNT(feedbacks) feedbacks->count_feedbacks
#define IM_FEEDBACK_TYPE(feedback) feedback->type
#define IM_FEEDBACK_VALUE(feedback) feedback->value

#define IM_RGB_COLOR(RED,GREEN,BLUE)	(int)((RED<<16) + (GREEN<<8) + BLUE)
#define IM_RGB_COLOR_RED(COLOR)		(int)(COLOR>>16)
#define IM_RGB_COLOR_GREEN(COLOR)	(int)((COLOR>>8)&0x00ff)
#define IM_RGB_COLOR_BLUE(COLOR)	(int)(COLOR&0x0000ff)

typedef struct _IMFeedback {
  IMFeedbackType type;
  int   value;			/* depends on id-type */
} IMFeedback;

typedef struct _IMFeedbackList {
  unsigned int count_feedbacks;
  IMFeedback  *feedbacks;
} IMFeedbackList;

typedef struct _IMAnnotation {
  int type;  /* IMAnnotationType */
  int num_values;
  IMAnnotationValue   *values;
} IMAnnotation;

typedef enum {
  UTF16_CODESET = 0,
  JAEUC_CODESET = 1,
  JAPCK_CODESET = 2,
  ZHEUC_CODESET = 3,
  ZHGBK_CODESET = 4,
  TWEUC_CODESET = 5,
  TWBIG5_CODESET = 6,
  KOEUC_CODESET = 7,
  UTF8_CODESET = 8,
  UTF32_CODESET = 9
} IMEncoding;

/* 
 * Define the structure used to exchange text
*/
typedef struct _IMText {
  IMEncoding	  encoding;
  unsigned int	  char_length;
  union {
    UTFCHAR	  *utf_chars;	/* UTF16 */
    char	  *native_chars;/* non-UTF16  */
  } text;
  IMFeedbackList  *feedback;
  unsigned int    count_annotations;
  IMAnnotation	  *annotations;
} IMText;

/* Operation related Data structures */
typedef struct _IMOperation {
    unsigned int id;		/* operation id */
    int length;                 /* length of value */
    void *value;                /* contents, contents in ccdef case */
} IMOperation, *IMOperationList;

/*
 * Event Type
 */

typedef enum {
    IM_EventKeyList = 1,
    IM_EventString = 2,
    IM_EventText = 3,
    IM_EventAux = 4,
    IM_EventX = 100
} IM_Event_Type;

/*
 * a key event for IMKeyListEvent
 */

typedef struct _IMKeyEventStruct {
   int keyCode;
   int keyChar;
   int modifier;
   int time_stamp;
} IMKeyEventStruct, *IMKeyList;

/*
 * keylist event
 */
typedef struct _IMKeyListEvent {
    int type;
    int n_operation;
    IMOperationList operation_list;

    int n_key;
    IMKeyList keylist;
} IMKeyListEvent;

/*
 * Data structures for Preedit
*/

#define IMNormal               0
#define IMReverse              1
#define IMUnderline            2

typedef struct _IMPreeditDrawCallbackStruct {
  int caret;          /* Cursor offset within pre-edit string */
  int chg_first;      /* Starting change position */
  int chg_length;     /* Length of the change in character count */
  IMText *text;
} IMPreeditDrawCallbackStruct;

typedef enum {
  IMForwardChar, IMBackwardChar,
  IMForwardWord, IMBackwardWord,
  IMCaretUp, IMCaretDown,
  IMNextLine, IMPreviousLine,
  IMLineStart, IMLineEnd,
  IMAbsolutePosition,
  IMDontChange
} IMCaretDirection;

typedef enum {
  IMIsInvisible,     /* Disable caret feedback */
  IMIsPrimary,       /* UI defined caret feedback */
  IMIsSecondary      /* UI defined caret feedback */
} IMCaretStyle;

typedef struct _IMPreeditCaretCallbackStruct {
  int position;               /* Caret offset within pre-edit string */
  IMCaretDirection direction; /* Caret moves direction */
  IMCaretStyle style;         /* Feedback of the caret */
} IMPreeditCaretCallbackStruct;

struct IMPreeditStruct {
  union {
    int return_value;
    IMPreeditDrawCallbackStruct draw;
    IMPreeditCaretCallbackStruct caret;
  } todo;
};

/*
 * Data structures for Status 
*/ 
typedef struct _IMStatusDrawCallbackStruct {
  IMText *text;
} IMStatusDrawCallbackStruct;

struct IMStatusStruct {
  union {
    IMStatusDrawCallbackStruct draw;	/* StatusDraw */
  } todo;
};

/*
 * Data structures for Lookup
*/

#define IM_LUC_LABEL_NONE               0
#define IM_LUC_LABEL_NUMERIC            1
#define IM_LUC_LABEL_ALPHABETIC         2
#define IM_LUC_LABEL_ALPHA_UPPER        3

typedef enum {
  HasNotBeenNegotiated = 0,
  IMIsMaster = 1,
  CBIsMaster  = 2
} WhoIsMaster;
 
typedef enum {
  DrawUpHorizontally = 0,
  DrawUpVertically = 1
} DrawUpDirection;
 
typedef enum {
  IMOwnsLabel = 0 ,
  CBOwnsLabel = 1
} WhoOwnsLabel;

typedef struct _LayoutInfo {
  int choice_per_window;  /* Number of choices can be display
			   * in the region
			   */
  int nrows;
  int ncolumns;
  DrawUpDirection drawUpDirection ;
  WhoOwnsLabel whoOwnsLabel;      /* For callback to tell XIM
				   * whether it wants to control
				   * what label should be for the choices.
				   */
  int luc_is_rootwindow;
  int label_type;
  int root_width;
  int root_lines;
  int e_width_per_can;
  int max_width_per_car;
} LayoutInfo;

typedef struct _IMLookupStartCallbackStruct {
    IMKeyListEvent *event;
    WhoIsMaster whoIsMaster;    /* For callback to tell whether is
                                 * going to be a master */
    LayoutInfo *IMPreference;
    LayoutInfo *CBPreference;
}   IMLookupStartCallbackStruct;

typedef struct _IMChoiceObject {
  IMText *label;
  IMText *value;
} IMChoiceObject;

typedef struct _IMLookupDrawCallbackStruct {
  IMChoiceObject *choices;       /* the lookup choices */
  int n_choices;      /* Total number of lookup choices */
  int max_len;        /* Max number of characters per
		       * choice item
		       */
  int index_of_first_candidate ;
  int index_of_last_candidate ;
  int index_of_current_candidate ;
  IMText *title;
} IMLookupDrawCallbackStruct;

typedef enum {
  LookupIndex=0,
  LookupPage=1
} IMLookupProcessOperationType;

typedef enum {
  LookupNextPage=1,
  LookupPrevPage=2,
  LookupFirstPage=3,
  LookupLastPage=4
} IMLookupProcessPageOperationType;

typedef struct _IMLookupProcessCallbackStruct {
  IMLookupProcessOperationType type;
                                /* Index(#0) index_of_choice_selected */
                                /* Page(#1)  page_operation_id */
  union {
    int index_of_choice_selected;/* Set by callback for the
				  * selected choice.
				  * IM_UNKNOW_KEYSYM and
				  * IM_UNDETERMINED are
				  * also possible value.
				  */
    IMLookupProcessPageOperationType page_operation_id;
  } value;
} IMLookupProcessCallbackStruct;

/*
 * Values for IMLookupProcessCallbackStruct.index_of_choice_selected
 */
#define         IM_UNKNOWN_KEYSYM       0x77777777
#define         IM_UNDETERMINED 0x77777776
#define         IM_UNKNOWN_CONTROL      0x77777775


struct IMLookupStruct {
  union {
    IMLookupStartCallbackStruct start;	/* LookupStart */
    IMLookupDrawCallbackStruct draw;	/* LookupDraw */
    IMLookupProcessCallbackStruct process;	/* LookupProcess */
  } todo;
};

/*
 * Data structures for Auxiliary 
*/
typedef struct _IMAuxBasicCallbackStruct {
  char *aux_name;
  int  aux_index;	/* do not use in 2.0 */
} IMAuxBasicCallbackStruct, IMAuxStartCallbackStruct, IMAuxDoneCallbackStruct;

typedef struct _IMAuxDrawCallbackStruct {
  char *aux_name;
  int  aux_index;	/* do not use in 2.0 */
  int  count_integer_values;
  int  *integer_values;
  int  count_string_values;
  IMText *string_values;
} IMAuxDrawCallbackStruct;

struct IMAuxStruct {
  union {
    IMAuxStartCallbackStruct start; /* AuxStart */
    IMAuxDrawCallbackStruct draw;   /* AuxDraw  */
    IMAuxDoneCallbackStruct done;   /* AuxDone  */
  } todo;
};

/*
 * Object Downloading
 */

typedef enum {
    IM_GUI_OBJECT = 0,
    IM_LWE_OBJECT = 1,
    IM_SYNTAX_RULE_OBJECT = 2,
    IM_MANAGER_RULE_OBJECT = 3,
    IM_PRELOADING_LWE_OBJECT = 4
}   IMObjectCategory;

typedef enum {
    IM_DOWNLOADINGOBJECT_JARGUI_TYPE = 0x1031,
    IM_DOWNLOADINGOBJECT_JARLWE_TYPE = 0x1032,
    IM_DOWNLOADINGOBJECT_CCDEF_TYPE = 0x1030,
    IM_DOWNLOADINGOBJECT_EIMIL_TYPE = 0x1030,

    IM_DOWNLOADINGOBJECT_BINGUI_TYPE = 0x1033,
    IM_DOWNLOADINGOBJECT_BINLWE_TYPE = 0x1034,

    IM_DOWNLOADINGOBJECT_SGUI_TYPE = 0x1035,
    IM_DOWNLOADINGOBJECT_SLWE_TYPE = 0x1036
}   IMObjectType;

typedef struct _IMObjectDescriptorStruct {
    char *leid;                 /* id for LE, `sampleja' */
    IMObjectType type;
    unsigned int id;		/* assigined dynamically by LELookup */
    unsigned int size;		/* object size */

    char **class_names;		/* only for JARFILE_OBJECT */
    unsigned int count_names;	/* count of class names */
				/* only for CCDEF */
    UTFCHAR *name;          	/* HRN */
    int name_length;		/* HRN len in UTF16-char unit */
    char *domain;               /* reversed domain */
    char *path;			/* path for object */
    char *scope;		/* usability id or `generic' */

				/* only for CCDEF */
    char *signature;		/* Object signature */
    char *basepath;		/* base path for include tag */
    char *encoding;		/* encoding of CCDEF */
} IMObjectDescriptorStruct;

/*
 * string event
 */
typedef struct _IMStringEvent {
    int type;
    int n_operation;
    IMOperationList operation_list;
    UTFCHAR *string;
} IMStringEvent;

/*
 * text event
 */
typedef struct _IMTextEvent {
    int type;
    int n_operation;
    IMOperationList operation_list;
    IMText *text;
} IMTextEvent;

/*
 * event for Auxiliary
 */
typedef struct _IMAuxEvent {
    int type;
    IMAuxDrawCallbackStruct *aux;
} IMAuxEvent;

/*
 * event for X, only for XSunIM's if_FilterEvent()
 */
typedef struct _IMXEvent {
    int type;
    void *xevent;
} IMXEvent;

/*
 * IMInputEvent
 */
typedef union IMInputEvent_ {
    int type;
    IMKeyListEvent keylist;
    IMTextEvent text;
    IMStringEvent string;
    IMAuxEvent aux;
    IMXEvent xevent;
} IMInputEvent;

/*
 * IC & IM ATTRIBID
 */

enum IM_ATTRIBID {
  INPUTMETHOD_LIST = 0x1001,
  OBJECT_DESCRIPTER_LIST = 0x1010,
  CLIENT_DESCRIPTER = 0x1011,
  CCDEF = 0x1030,
  GUI_OBJECT = 0x1031,
  LWE_OBJECT = 0x1032
};

enum IC_ATTRIBID {
  IC_INPUT_LANGUAGE = 1,
  IC_CHARACTER_SUBSETS = 2,
  IC_INPUT_METHOD = 3,
  IC_PREFERED_OBJECT = 4,
  IC_SUPPORTED_CLASSES = 5
};


/*
 * Data structures for sync up.
*/

typedef struct IMTransaction {
  CARD32BIT opid;
  CARD32BIT trid;
} IMTransaction;

#define IM_TRANSACTION_NOP_ID 0
#define IM_DIFFERENTIAL_FLAG_NILP(dflag) ((dflag) & 0x1)

typedef struct IMDifferential {
    CARD32BIT symid;
    int nil;
    int number;
    int bool_val;
    CARD32BIT ch;
    IMInputEvent ev;
    int chg_first;
    int chg_len;
    IMText text;
} IMDifferential;

#define SYMBOLID_TYPE(symid) (((symid) >> 16) & 0xFF)

enum IM_SYMBOL_TYPE {
  IM_SYMBOL_ATTRIBID = 0,

  IM_SYMBOL_VARIABLE_NUMBER = 1,
  IM_SYMBOL_VARIABLE_BOOL = 2,
  IM_SYMBOL_VARIABLE_CHAR = 3,
  IM_SYMBOL_VARIABLE_MTEXT = 4,
  IM_SYMBOL_VARIABLE_EVENT = 5,

  IM_SYMBOL_PROPERTY_MASK = 0x10,
  IM_SYMBOL_PROPERTY_NUMBER = IM_SYMBOL_PROPERTY_MASK | IM_SYMBOL_VARIABLE_NUMBER,
  IM_SYMBOL_PROPERTY_BOOL = IM_SYMBOL_PROPERTY_MASK | IM_SYMBOL_VARIABLE_BOOL,
  IM_SYMBOL_PROPERTY_CHAR = IM_SYMBOL_PROPERTY_MASK | IM_SYMBOL_VARIABLE_CHAR,
  IM_SYMBOL_PROPERTY_MTEXT = IM_SYMBOL_PROPERTY_MASK | IM_SYMBOL_VARIABLE_MTEXT,

  IM_SYMBOL_OPERATION = 0x20
};

typedef struct IMProp {
  int type;
  int count;
  union vals {
    IMText *mtexts;
    int *numbers;
    int *bools;
    CARD32BIT *chars;
  } vals;
} IMProp;

typedef struct IMSymbol {
  char *symname;
  CARD32BIT symid;
} IMSymbol;

#endif
