/*
  EIMIL.h
*/

#ifndef _EIMIL_H_
#define _EIMIL_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <IMProtocolStruct.h>

#ifndef ASSERT
#ifdef DEBUG
#define ASSERT(X)					\
do {							\
    if (!(X)) {						\
	fprintf(stderr, "EIMIL ASSERT %s: %s (%s)",	\
		#X, __FILE__, __LINE__);		\
		abort();				\
    }							\
} while(0)
#else
#define ASSERT(X) ((void) 0)
#endif
#endif

typedef CARD32BIT UTF32;
typedef CARD16BIT UTF16;
typedef CARD8BIT UTF8;
typedef CARD32BIT EIMIL_TID;
typedef CARD32BIT EIMIL_SYMID;
typedef CARD8BIT Ebyte;
typedef void* EIMIL_handle;
#define EIMIL_VOID_HANDLE ((void*)0)

/*
  Constants.
 */

enum EIMIL_CATEGORY {
	EIMIL_CAT_VARIABLE,
	EIMIL_CAT_PROPERTY,
	EIMIL_CAT_FUNCTION,
	EIMIL_CAT_EXCEPTION,
	EIMIL_CAT_OPERATION,
	EIMIL_CAT_OPTIONAL
};

enum EIMIL_TYPE {
/* bitwise type flags.  */
	EIMIL_TYPE_INVALID = 0,
	EIMIL_TYPE_NONE = (1 << 0),
	EIMIL_TYPE_BOOL = (1 << 1),
	EIMIL_TYPE_NUMBER = (1 << 2),
	EIMIL_TYPE_CHAR = (1 << 3),
	EIMIL_TYPE_MTEXT = (1 << 4),
	EIMIL_TYPE_EVENT = (1 << 5),
	EIMIL_TYPE_PROP = (1 << 6),
/* special type attribute for unique objects.  */
	EIMIL_TYPE_NIL = (1 << 7),
	EIMIL_TYPE_T = -1,
	EIMIL_TYPE_FEEDBACK = -2,
	EIMIL_TYPE_CANDIDATES = -3,

	EIMIL_TYPE_CONST = (1 << 15),
	EIMIL_TYPE_ANY = (1 << 16),
	EIMIL_TYPE_OPTION1 = (1 << 17),
	EIMIL_TYPE_OPTION2 = (1 << 18)
};

enum EIMIL_SYMBOL_TYPE_ID {
	EIMIL_SYMBOL_ID_OPERATION = 1,

	EIMIL_SYMBOL_ID_VARIABLE_NUMBER = 2,
	EIMIL_SYMBOL_ID_VARIABLE_BOOL = 3,
	EIMIL_SYMBOL_ID_VARIABLE_CHAR = 4,
	EIMIL_SYMBOL_ID_VARIABLE_MTEXT = 5,
	EIMIL_SYMBOL_ID_VARIABLE_EVENT = 6,
	EIMIL_SYMBOL_ID_VARIABLE_PROP = 7,

	EIMIL_SYMBOL_ID_PROPERTY_MASK = 0x10,
	EIMIL_SYMBOL_ID_PROPERTY_NUMBER = (EIMIL_SYMBOL_ID_PROPERTY_MASK 
					   | EIMIL_SYMBOL_ID_VARIABLE_NUMBER),
	EIMIL_SYMBOL_ID_PROPERTY_BOOL = (EIMIL_SYMBOL_ID_PROPERTY_MASK
					 | EIMIL_SYMBOL_ID_VARIABLE_BOOL),
	EIMIL_SYMBOL_ID_PROPERTY_CHAR = (EIMIL_SYMBOL_ID_PROPERTY_MASK
					 | EIMIL_SYMBOL_ID_VARIABLE_CHAR),
	EIMIL_SYMBOL_ID_PROPERTY_MTEXT = (EIMIL_SYMBOL_ID_PROPERTY_MASK
					  | EIMIL_SYMBOL_ID_VARIABLE_MTEXT),

	EIMIL_SYMBOL_ID_EXCEPTION = 0x20,

	EIMIL_SYMBOL_ID_PRIVATE = 0x80,
	EIMIL_SYMBOL_ID_FUNCTION = 0x81
};

enum EIMIL_UNIVERSAL_SYMBOL_ID {
	EIMIL_SYMBOL_ID_NIL = (EIMIL_SYMBOL_ID_PRIVATE << 16) | 1,
	EIMIL_SYMBOL_ID_T = (EIMIL_SYMBOL_ID_PRIVATE << 16) | 2,
	EIMIL_SYMBOL_ID_FEEDBACK = (EIMIL_SYMBOL_ID_PRIVATE << 16) | 3,
	EIMIL_SYMBOL_ID_CANDIDATES = (EIMIL_SYMBOL_ID_PRIVATE << 16) | 4
};

/*
  value
*/

/*struct EIMIL_value;*/
typedef struct EIMIL_prop EIMIL_prop;
typedef struct EIMIL_mtext_props EIMIL_mtext_props;
typedef struct EIMIL_mtext EIMIL_mtext;
typedef struct EIMIL_event EIMIL_event;
typedef struct EIMIL_value EIMIL_value;
typedef struct EIMIL_exception EIMIL_exception;
typedef struct EIMIL_dependency EIMIL_dependency;
typedef struct EIMIL_operation EIMIL_operation;
typedef struct EIMIL_optional EIMIL_optional;
typedef union EIMIL_object EIMIL_object;

typedef struct EIMIL_function EIMIL_function;
typedef struct EIMIL_variable EIMIL_variable;
typedef struct EIMIL_tprop EIMIL_tprop;
typedef struct EIMIL_message EIMIL_message;
typedef struct EIMIL_symbol EIMIL_symbol;

struct EIMIL_prop {
    int st;
    int end;
    EIMIL_symbol *property_sym;
    EIMIL_mtext *target;
    enum EIMIL_TYPE type;
    int size;
    EIMIL_value **pvals;
};

struct EIMIL_mtext_props {
    int num;
    EIMIL_symbol *property_sym;
    EIMIL_value **pprops;
};

struct EIMIL_mtext {
    int len;
    UTF32 *ustr;
    int slotsnum;
    EIMIL_mtext_props *pslots;
    int UIdatap;
};

struct EIMIL_event {
    UTF8* type;
    EIMIL_value *pv_val;
    EIMIL_value *pv_mod;
    EIMIL_value *pv_char;
    EIMIL_value *pv_mtext;
};

struct EIMIL_value {
    int refcount;
    enum EIMIL_TYPE type;
    union {
	UTF32 ch;
	int bool_val;
	int number;
	EIMIL_prop prop;
	EIMIL_mtext mtext;
	EIMIL_event event;
    } v;
};

/*
  symbol
*/

struct EIMIL_function {
    enum EIMIL_TYPE type;
    void *def;
};

struct EIMIL_variable {
    enum EIMIL_TYPE type;
    int constp;
    EIMIL_value *pv;
};

struct EIMIL_tprop {
    enum EIMIL_TYPE type;
};

struct EIMIL_message {
    UTF32 *lang;
    UTF32 *msg;
};

struct EIMIL_exception {
    EIMIL_message *msgs;
};

struct EIMIL_dependency {
    int numdepends;
    EIMIL_symbol **depends;
    int numaffects;
    EIMIL_symbol **affects;
};

struct EIMIL_operation {
    int commitnotifyp;
    int numdepends;
    EIMIL_dependency *pdeps;
};

struct EIMIL_optional {
    int optnum1;
    int optnum2;
    void *optarg;
};

union EIMIL_object {
    EIMIL_function f;
    EIMIL_variable v;
    EIMIL_tprop p;
    EIMIL_exception e;
    EIMIL_operation o;
    EIMIL_optional opt;
};

struct EIMIL_symbol {
    enum EIMIL_CATEGORY cat;
    EIMIL_SYMID symbolid;
    int namelen;
    unsigned char *name;
    int publicp;
    EIMIL_object obj;
};

/*
  Handlers.
 */

enum EIMIL_UICHANGE_FLAGS {
	EIMIL_ENABLE_PREEDIT,
	EIMIL_DISABLE_PREEDIT,
	EIMIL_UPDATE_PREEDIT,

	EIMIL_ENABLE_LOOKUP_CHOICE = 0x100,
	EIMIL_DISABLE_LOOKUP_CHOICE,
	EIMIL_UPDATE_LOOKUP_CHOICE,

	EIMIL_COMMIT_STRING = 0x200
};

typedef int (*EIMIL_EVENT_PROC)(
    EIMIL_handle eh,
    EIMIL_event *pevent
);
typedef int (*EIMIL_UICHANGE_PROC)(
    EIMIL_handle eh,
    EIMIL_value *pval,
    int uichange_flags
);
typedef int (*EIMIL_OPISSUE_PROC)(
    EIMIL_handle eh,
    EIMIL_symbol *psym
);

/*
  Functions.
 */
#ifdef __cplusplus
extern "C" {
#endif

/* EIMIL */

extern EIMIL_symbol *pEIMIL_nil_sym, *pEIMIL_t_sym;
extern EIMIL_symbol *pEIMIL_feedback_sym;
extern EIMIL_symbol *pEIMIL_candidates_sym;

extern EIMIL_value* EIMIL_construct_number(
    int number
);
extern EIMIL_value* EIMIL_construct_bool(
    int bool_val
);
extern EIMIL_value* EIMIL_construct_char(
    UTF32 ch
);
extern EIMIL_value* EIMIL_construct_prop(
    EIMIL_symbol *psym
);
extern EIMIL_value* EIMIL_construct_prop2(
    enum EIMIL_TYPE type
);
extern EIMIL_value* EIMIL_construct_event(
    UTF8 *type,
    EIMIL_value *pv_val,
    EIMIL_value *pv_mod,
    EIMIL_value *pv_char,
    EIMIL_value *pv_mtext
);
extern int EIMIL_construct_events_from_IMInputEvent(
    IMInputEvent *pimev,
    EIMIL_value ***pppevs
);
extern IMInputEvent* EIMIL_convert_event_to_IMInputEvent(
    EIMIL_event *pev
);
extern int EIMIL_add_prop(
    EIMIL_prop *pprop,
    EIMIL_value *pv
);
extern int EIMIL_delete_prop(
    EIMIL_prop *pprop,
    int idx
);
extern EIMIL_value* EIMIL_copy_value(
    EIMIL_value *pv
);
extern int EIMIL_value_equal(
    EIMIL_value *pv1,
    EIMIL_value *pv2
);

extern int EIMIL_generate_diff(
    EIMIL_symbol *psym,
    EIMIL_value *pv2,
    IMDifferential *pdiff
);

extern int EIMIL_duplicate_handle(
    EIMIL_handle *peh,
    EIMIL_handle eh
);

extern int EIMIL_free_handle(
    EIMIL_handle eh
);

#if 0
extern EIMIL_symbol* EIMIL_intern(EIMIL_handle eh, char *name);
extern EIMIL_symbol* EIMIL_intern_soft(EIMIL_handle eh, char *name);
extern EIMIL_symbol* EIMIL_lookup_symbol(EIMIL_handle eh, CARD32BIT id);
#endif

extern int EIMIL_send_event(
    EIMIL_handle eh,
    EIMIL_value *pv_event
);

extern void EIMIL_destruct_value(EIMIL_value* pv);
extern void EIMIL_detach_prop_from_mtext(EIMIL_value *pv);

extern int EIMIL_initialize();

/* EIMILFile */

extern int EIMIL_register_class(
    unsigned char *classname,
    unsigned char *dirname
);
extern unsigned char* EIMIL_find_file(
    unsigned char *classname,
    unsigned char *name
);
extern int EIMIL_parse_file(
    EIMIL_handle *peh,
    unsigned char *filename
);

extern int EIMIL_enumerate_class(
    unsigned char *classname
);
extern int EIMIL_register_file(
    unsigned char *classname
);
extern int EIMIL_file_symbolid(
    unsigned char *classname,
    unsigned char *name
);

/* EIMILTextUtil */
extern int EIMIL_UTF32_string_len(
    const UTF32 *pstr
);
extern int EIMIL_UTF32_strcmp(
    const UTF32 *pstr1,
    const UTF32 *pstr2
);
extern int EIMIL_convert_UTF32char_to_UTF8(
    UTF32 ch,
    UTF8 *p
);
extern UTF8* EIMIL_convert_UTF32_to_UTF8(
    const UTF32 *putf32
);
extern int EIMIL_convert_UTF8_to_UTF32char(
    const UTF8 *p,
    UTF32 *pch
);
extern UTF32* EIMIL_convert_UTF8_to_UTF32(
    const UTF8 *putf8
);
extern int EIMIL_adjust_UTF16_pos_to_UTF32(
    int pos,
    const UTF32 *pbase,
    const UTF32 *pbaseend
);
extern int EIMIL_adjust_UTF32_pos_to_UTF16(
    int pos,
    const UTF32 *pbase,
    const UTF32 *pbaseend
);
extern int EIMIL_convert_UTF32_to_UTF16(
    const UTF32 *pu32,
    int u32len,
    UTF16 **ppu16,
    int *pu16len
);
extern int EIMIL_convert_UTF16_to_UTF32(
    const UTF16 *pu16,
    int u16len,
    UTF32 **ppu32,
    int *pu32len
);
extern EIMIL_value* EIMIL_construct_mtext_from_UTF8(
    const unsigned char *in
);
extern EIMIL_value* EIMIL_construct_mtext_from_UTF16(
    int len,
    const UTF16 *in
);
extern EIMIL_value* EIMIL_construct_mtext_from_UTF32(
    int len,
    const UTF32 *in
);
extern EIMIL_value* EIMIL_construct_mtext_from_UTF32_char(
    UTF32 in
);

extern EIMIL_value* EIMIL_mtext_concat(
    int num,
    EIMIL_value **pvs
);

extern EIMIL_value* EIMIL_mtext_substr(
    EIMIL_value *pv_mtext,
    int st,
    int end
);

extern EIMIL_value* EIMIL_get_prop_from_mtext(
    EIMIL_mtext *pm,
    EIMIL_symbol *property_sym,
    int pos
);

extern EIMIL_value* EIMIL_find_prop_from_mtext(
    EIMIL_mtext *pm,
    EIMIL_symbol *property_sym,
    int pos
);

extern EIMIL_mtext* EIMIL_add_prop_on_mtext(
    EIMIL_mtext *pm,
    EIMIL_value *pv,
    int st,
    int end
);
extern EIMIL_mtext* EIMIL_set_prop_on_mtext(
    EIMIL_mtext *pm,
    EIMIL_value *pv,
    int st,
    int end
);

extern int EIMIL_convert_mtext_to_IMText(
    IMText *pim,
    EIMIL_mtext *psrc
);
extern EIMIL_value* EIMIL_construct_mtext_from_IMText(
    IMText *pim
);
extern int EIMIL_sync_mtext(
    EIMIL_mtext *pm,
    IMDifferential *pdiff
);

/* EIMILJournal */
extern int EIMIL_journal_prev_val(
    EIMIL_handle eh,
    EIMIL_TID tid,
    EIMIL_symbol *psym,
    EIMIL_value **pv
);
extern int EIMIL_journal_record_change(
    EIMIL_handle eh,
    EIMIL_symbol *psym
);
extern int EIMIL_journal_set_point(
    EIMIL_handle eh,
    EIMIL_TID *ptid
);

		
#ifdef __cplusplus
}
#endif

#define EIMIL_ADDREF(v) (((v).refcount)++)
#define EIMIL_RMREF(v) \
((--((v).refcount) <= 0) ? (EIMIL_destruct_value(&(v)), 0) : 0)
#define EIMIL_RMREF_WITHOUT_DESTRUCTION(v) (--((v).refcount))
#define EIMIL_REFCHECK(v) \
((((v).refcount) <= 0) ? (EIMIL_destruct_value(&(v)), 0) : 0)
#define EIMIL_REFCHECK_GUARD(v, gv) \
do { \
    if (((v).refcount) <= 0) { \
	(gv).refcount++; \
	EIMIL_destruct_value(&(v)); \
	(gv).refcount--; \
    } \
} while(0)


#endif /* not _EIMIL_H_ */

/* Local Variables: */
/* c-file-style: "iiim-project" */
/* End: */
