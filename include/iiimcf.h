/*
  iiimcf.h
*/
#ifndef _IIIMCF_H_
#define _IIIMCF_H_
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <iiimp.h>

/*
  constants
*/

enum IIIMCF_VERSION_ITEMS {
	IIIMCF_LIBRARY_VERSION = (1 << 0),
	IIIMCF_PROTOCOL_VERSION = (1 << 1)
};
enum IIIMCF_VERSION_CATEGORIES {
	IIIMCF_MAJOR_VERSION = (1 << 8),
	IIIMCF_MINOR_VERSION = (1 << 9)
};

enum IIIMCF_UISTATE {
	IIIMCF_STATE_PREEDIT_CHANGED = (1 << 0),
	IIIMCF_STATE_LOOKUP_CHOICE_CHANGED = (1 << 1),
	IIIMCF_STATE_STATUS_CHANGED = (1 << 2),
	IIIMCF_STATE_COMMIT_REQUIRED = (1 << 3),
	IIIMCF_STATE_PENDING_EVENT = (1 << 4),
	IIIMCF_STATE_CONVERSION_MODE_CHANGED = (1 << 5),
	/* 5 - 15 are reserved.  */
	IIIMCF_STATE_INVALIDATED = (1 << 16)
};

enum IIIMCF_LOOKUP_CHOICE_DIRECTION {
	IIIMCF_LOOKUP_CHOICE_HORIZONTAL_DIRECTION = 0,
	IIIMCF_LOOKUP_CHOICE_VERTICAL_DIRECTION = 1
};

enum IIIMCF_LOOKUP_CHOICE_ITEM_FLAGS {
	IIIMCF_LOOKUP_CHOICE_ITEM_ENABLED = (1 << 0),
	IIIMCF_LOOKUP_CHOICE_SELECTED_ITEM = (1 << 1)
};

enum IIIMCF_ATTRS {
	IIIMCF_ATTR_SERVER_ADDRESS = 1,
	IIIMCF_ATTR_SERVER_SERVICE,
	IIIMCF_ATTR_USERNAME,
	IIIMCF_ATTR_PASSWORD,
	IIIMCF_ATTR_CLIENT_TYPE,
	IIIMCF_ATTR_DISABLE_AUTOMATIC_RESTORATION,
	IIIMCF_ATTR_CLIENT_X_DISPLAY_NAME,
	IIIMCF_ATTR_CLIENT_X_SERVER_VENDOR,

	IIIMCF_ATTR_INPUT_LANGUAGE = 0x1000,
	IIIMCF_ATTR_INPUT_METHOD,
	IIIMCF_ATTR_DISABLE_AUTOMATIC_TRIGGER_NOTIFY,
	IIIMCF_ATTR_INPUT_METHOD_NAME,

	/* for private use area. */
	IIIMCF_ATTR_PRIVATE_START = 0x10000
};

enum IIIMCF_EVENT_TYPES {
	IIIMCF_EVENT_TYPE_DESTROY = -2,
	IIIMCF_EVENT_TYPE_RESET = -1,

	IIIMCF_EVENT_TYPE_EVENTLIKE = 1,
	IIIMCF_EVENT_TYPE_KEYEVENT = 1,
	IIIMCF_EVENT_TYPE_KEYEVENT_END = 0x0FFF,
	
	IIIMCF_EVENT_TYPE_TRIGGER_NOTIFY_START = 0x1000,
	IIIMCF_EVENT_TYPE_TRIGGER_NOTIFY = 0x1000,
	IIIMCF_EVENT_TYPE_TRIGGER_NOTIFY_END = 0x1FFF,
	IIIMCF_EVENT_TYPE_OPERATION = 0x2000,
	IIIMCF_EVENT_TYPE_SETICFOCUS = 0x3000,
	IIIMCF_EVENT_TYPE_UNSETICFOCUS = 0x3001,
	IIIMCF_EVENT_TYPE_EVENTLIKE_END = 0x3FFF,

	IIIMCF_EVENT_TYPE_UI = 0x8000,

	IIIMCF_EVENT_TYPE_UI_PREEDIT = 0x9000,
	IIIMCF_EVENT_TYPE_UI_PREEDIT_START,
	IIIMCF_EVENT_TYPE_UI_PREEDIT_CHANGE,
	IIIMCF_EVENT_TYPE_UI_PREEDIT_DONE,
	IIIMCF_EVENT_TYPE_UI_PREEDIT_END = 0x9FFF,
	
	IIIMCF_EVENT_TYPE_UI_LOOKUP_CHOICE = 0xA000,
	IIIMCF_EVENT_TYPE_UI_LOOKUP_CHOICE_START,
	IIIMCF_EVENT_TYPE_UI_LOOKUP_CHOICE_CHANGE,
	IIIMCF_EVENT_TYPE_UI_LOOKUP_CHOICE_DONE,
	IIIMCF_EVENT_TYPE_UI_LOOKUP_CHOICE_END = 0xAFFF,

	IIIMCF_EVENT_TYPE_UI_STATUS = 0xB000,
	IIIMCF_EVENT_TYPE_UI_STATUS_START,
	IIIMCF_EVENT_TYPE_UI_STATUS_CHANGE,
	IIIMCF_EVENT_TYPE_UI_STATUS_DONE,
	IIIMCF_EVENT_TYPE_UI_STATUS_END = 0xBFFF,

	IIIMCF_EVENT_TYPE_UI_COMMIT = 0xC000,
	IIIMCF_EVENT_TYPE_UI_COMMIT_END = 0xCFFF,

	IIIMCF_EVENT_TYPE_UI_END = 0xFFFF,

	IIIMCF_EVENT_TYPE_AUX = 0x80000,
	IIIMCF_EVENT_TYPE_AUX_START,
	IIIMCF_EVENT_TYPE_AUX_DRAW,
	IIIMCF_EVENT_TYPE_AUX_SETVALUES,
	IIIMCF_EVENT_TYPE_AUX_DONE,
	IIIMCF_EVENT_TYPE_AUX_END = 0x8FFFF
};
typedef enum IIIMCF_EVENT_TYPES IIIMCF_event_type;
#define IIIMCF_IS_EVENT_TYPE_BROADCAST(type) ((type) < 0)

/*
  typedefs & structures
*/

/* opaque object type */
#if 1
typedef struct IIIMCF_handle_rec* IIIMCF_handle;
typedef struct IIIMCF_attr_rec* IIIMCF_attr;
typedef struct IIIMCF_context_rec* IIIMCF_context;
typedef struct IIIMCF_text_rec* IIIMCF_text;
/* typedef struct IIIMCF_text_property_value_rec* IIIMCF_text_property_value; */
typedef struct IIIMCF_lookup_choice_rec* IIIMCF_lookup_choice;
typedef struct IIIMCF_language_rec* IIIMCF_language;
typedef struct IIIMCF_input_method_rec* IIIMCF_input_method;
typedef struct IIIMCF_event_rec* IIIMCF_event;
typedef struct IIIMCF_component_rec* IIIMCF_component;
typedef struct IIIMCF_downloaded_object_rec* IIIMCF_downloaded_object;
#else
/* In case that a compiler does not accept the above declaration
   without proper definition (normally that does not happen),
   use the following declarations instead.  */
typedef void* IIIMCF_handle;
typedef void* IIIMCF_attr;
typedef void* IIIMCF_context;
typedef void* IIIMCF_text;
typedef void* IIIMCF_text_property_value;
typedef void* IIIMCF_lookup_choice;
typedef void* IIIMCF_language;
typedef void* IIIMCF_input_method;
typedef void* IIIMCF_event;
typedef void* IIIMCF_component;
typedef void* IIIMCF_downloaded_object;
#endif

/* special attr */
#define IIIMCF_ATTR_NULL ((IIIMCF_attr) (NULL))

/* transparent object typedefs & structures */

/* object descriptor */
typedef struct {
    int category;
    size_t size;
    int predefined_id;
    int dynamic_id;
    const IIIMP_card16 *domain;
    const IIIMP_card16 *hrn;
    const IIIMP_card16 *signature;
    const IIIMP_card16 *user;
} IIIMCF_object_descriptor;

/* keyevent */
typedef struct IIIMCF_keyevent IIIMCF_keyevent;
struct IIIMCF_keyevent {
    IIIMP_int32 keycode;
    IIIMP_int32 keychar;
    IIIMP_int32 modifier;
    IIIMP_int32 time_stamp;
};

/* component interface */
typedef IIIMF_status
(*IIIMCF_component_interface)(
    IIIMCF_context context,
    IIIMCF_event event,
    IIIMCF_component current,
    IIIMCF_component parent
);

#define IIIMCF_ROOT_COMPONENT ((IIIMCF_component) NULL)

/*
  Functions 
*/
#ifdef __cplusplus
extern "C" {
#endif

/* Initialization & finalization */

extern IIIMF_status iiimcf_initialize(
    IIIMCF_attr attr
);
extern IIIMF_status iiimcf_finalize();

/* create & destroy handle */

extern IIIMF_status iiimcf_create_handle(
    IIIMCF_attr attr,
    IIIMCF_handle *phandle
);
extern IIIMF_status iiimcf_destroy_handle(
    IIIMCF_handle handle
);

/* create & destroy context */

extern IIIMF_status iiimcf_create_context(
    IIIMCF_handle handle,
    IIIMCF_attr attr,
    IIIMCF_context *pcontext
);
extern IIIMF_status iiimcf_destroy_context(
    IIIMCF_context context
);

/* reset context */

extern IIIMF_status iiimcf_reset_context(
    IIIMCF_context context
);

/* data manipulation */
/* attribute */

extern IIIMF_status iiimcf_create_attr(
    IIIMCF_attr *pattr
);
extern IIIMF_status iiimcf_destroy_attr(
    IIIMCF_attr attr
);

extern IIIMF_status iiimcf_attr_put_string_value(
    IIIMCF_attr attr,
    int property,
    const char *str
);
extern IIIMF_status iiimcf_attr_get_string_value(
    IIIMCF_attr attr,
    int property,
    const char **pstr
);

extern IIIMF_status iiimcf_attr_put_integer_value(
    IIIMCF_attr attr,
    int property,
    int number
);
extern IIIMF_status iiimcf_attr_get_integer_value(
    IIIMCF_attr attr,
    int property,
    int *pnumber
);

extern IIIMF_status iiimcf_attr_put_ptr_value(
    IIIMCF_attr attr,
    int property,
    void *ptr
);
extern IIIMF_status iiimcf_attr_get_ptr_value(
    IIIMCF_attr attr,
    int property,
    void **pptr
);

/* text */
extern IIIMF_status iiimcf_get_text_utf16string(
    IIIMCF_text text,
    const IIIMP_card16** putf16str
);
extern IIIMF_status iiimcf_get_text_length(
    IIIMCF_text text,
    int *plen
);
extern IIIMF_status iiimcf_get_char_with_feedback(
    IIIMCF_text text,
    int pos,
    IIIMP_card16 *pch,
    int *pnum_feedbacks,
    const IIIMP_card32** pfeedback_id,
    const IIIMP_card32** pfeedback
);
extern IIIMF_status iiimcf_duplicate_text(
    IIIMCF_text src,
    IIIMCF_text *pduplicated
);
extern IIIMF_status iiimcf_destroy_text(
    IIIMCF_text text
);

/* lookup choice */

extern IIIMF_status iiimcf_get_lookup_choice_configuration(
    IIIMCF_lookup_choice lookup_choice,
    int *pchoices_per_window,
    int *pnumber_of_rows,
    int *pnumber_of_columns,
    int *pdirection
);
extern IIIMF_status iiimcf_get_lookup_choice_size(
    IIIMCF_lookup_choice lookup_choice,
    int *psize,
    int *pindex_of_first_candidate,
    int *pindex_of_last_candidate,
    int *pindex_of_current_candidate
);
extern IIIMF_status iiimcf_get_lookup_choice_title(
    IIIMCF_lookup_choice lookup_choice,
    IIIMCF_text *ptitle
);
extern IIIMF_status iiimcf_get_lookup_choice_item(
    IIIMCF_lookup_choice lookup_choice,
    int idx,
    IIIMCF_text *pcandidate,
    IIIMCF_text *plabel,
    int *pflag
);

/* language */
extern IIIMF_status iiimcf_get_language_id(
    IIIMCF_language lang,
    const char **plangid
);

/* input method */
extern IIIMF_status iiimcf_get_input_method_desc(
    IIIMCF_input_method input_method,
    char **pinput_method_id,
    char **pinput_method_domain,
    int *pintput_method_hrn_len,
    IIIMP_card16** pinput_method_hrn
);
extern IIIMF_status iiimcf_get_input_method_languages(
    IIIMCF_input_method input_method,
    int *pinput_method_language_size,
    IIIMCF_language **pplangages
);

/* downloaded object */
extern IIIMF_status iiimcf_get_downloaded_object_descriptor(
    IIIMCF_downloaded_object object,
    const IIIMCF_object_descriptor **ppdesc
);
extern IIIMF_status iiimcf_get_downloaded_object_filename(
    IIIMCF_downloaded_object object,
    const IIIMP_card16 **pfilename
);
extern IIIMF_status iiimcf_get_downloaded_objects(
    IIIMCF_handle handle,
    int num_objs,
    const IIIMCF_object_descriptor **ppdesc,
    IIIMCF_downloaded_object *pobjs
);

/* version */
extern IIIMF_status iiimcf_get_version_number(
    IIIMCF_handle handle,
    int flag,
    int *pversion_number
);

/* state checking */
extern IIIMF_status iiimcf_is_UIstate_changed(
    IIIMCF_context context,
    int *pflag
);

/* info */
extern IIIMF_status iiimcf_get_supported_languages(
    IIIMCF_handle handle,
    int *pnum_langs,
    IIIMCF_language **pplangs
);
extern IIIMF_status iiimcf_get_supported_input_methods(
    IIIMCF_handle handle,
    int *pnum_input_methods,
    IIIMCF_input_method **ppinput_methods
);
extern IIIMF_status iiimcf_get_object_descriptor_list(
    IIIMCF_handle handle,
    int *pnum_object_descriptors,
    const IIIMCF_object_descriptor **ppdesc
);
extern IIIMF_status iiimcf_get_trigger_keys(
    IIIMCF_handle handle,
    int *pnum_on_keys,
    const IIIMCF_keyevent **pponkeys,
    int *pnum_off_keys,
    const IIIMCF_keyevent **ppoffkeys
);
extern IIIMF_status iiimcf_get_current_conversion_mode(
    IIIMCF_context context,
    int *pflag
);
extern IIIMF_status iiimcf_get_preedit_text(
    IIIMCF_context context,
    IIIMCF_text *ptext,
    int *pcaret_position
);
extern IIIMF_status iiimcf_get_status_text(
    IIIMCF_context context,
    IIIMCF_text *ptext
);
extern IIIMF_status iiimcf_get_lookup_choice(
    IIIMCF_context context,
    IIIMCF_lookup_choice *plookup_choice
);
extern IIIMF_status iiimcf_get_committed_text(
    IIIMCF_context context,
    IIIMCF_text *ptext
);
extern IIIMF_status iiimcf_get_aux_draw_data(
    IIIMCF_context context,
    const IIIMP_card16 *aux_name,
    IIIMP_card32 class_idx,
    int *pnum_intvals,
    const IIIMP_card32 **ppintvals,
    int *pnum_strvals,
    const IIIMP_card16 ***ppstrs
);

extern IIIMF_status iiimcf_context_get_attr(
    IIIMCF_context context,
    IIIMCF_attr *pattr
);

/* event */
extern IIIMF_status iiimcf_get_event_type(
    IIIMCF_event event,
    IIIMCF_event_type *pevent_type
);

extern IIIMF_status iiimcf_create_keyevent(
    const IIIMCF_keyevent *pkeyevent,
    IIIMCF_event *pevent
);

extern IIIMF_status iiimcf_create_trigger_notify_event(
    int flag,
    IIIMCF_event *pevent
);

extern IIIMF_status iiimcf_create_seticfocus_event(
    IIIMCF_event *pevent
);

extern IIIMF_status iiimcf_create_unseticfocus_event(
    IIIMCF_event *pevent
);

extern IIIMF_status iiimcf_create_aux_setvalues_event(
    const IIIMP_card16 *aux_name,
    IIIMP_card32 class_idx,
    int num_intvals,
    const IIIMP_card32 *pintvals,
    int num_strvals,
    const IIIMP_card16 **pstrs,
    IIIMCF_event *pevent
);

/* event value */
extern IIIMF_status iiimcf_get_keyevent_value(
    IIIMCF_event event,
    IIIMCF_keyevent *pkeyevent
);

extern IIIMF_status iiimcf_get_trigger_notify_flag(
    IIIMCF_event event,
    int *pflag
);

extern IIIMF_status iiimcf_get_aux_event_value(
    IIIMCF_event event,
    const IIIMP_card16 **paux_name,
    IIIMP_card32 *pclass_idx,
    int *pnum_intvals,
    const IIIMP_card32 **ppintvals,
    int *pnum_strvals,
    const IIIMP_card16 ***ppstrs
);

/* event flow control */
extern IIIMF_status iiimcf_forward_event(
    IIIMCF_context context,
    IIIMCF_event event
);

extern IIIMF_status iiimcf_dispatch_event(
    IIIMCF_context context,
    IIIMCF_event event
);

extern IIIMF_status iiimcf_get_next_event(
    IIIMCF_context context,
    IIIMCF_event *pevent
);

extern IIIMF_status iiimcf_peek_next_event(
    IIIMCF_context context,
    IIIMCF_event *pevent
);

extern IIIMF_status iiimcf_ignore_event(
    IIIMCF_event event
);

/* component management */

extern IIIMF_status iiimcf_register_component(
    IIIMCF_handle handle,
    const char* name,
    IIIMCF_component_interface interface,
    IIIMCF_component parent,
    IIIMCF_component* pcomp
);

extern IIIMF_status iiimcf_unregister_component(
    IIIMCF_component component
);

extern IIIMF_status iiimcf_get_component(
    IIIMCF_handle handle,
    const char *name,
    IIIMCF_component* pcomponent
);

extern IIIMF_status iiimcf_component_get_attr(
    IIIMCF_component component,
    IIIMCF_attr* pattr
);

#ifdef __cplusplus
}
#endif

#endif /* _IIIMCF_H_ */

/* Local Variables: */
/* c-file-style: "iiim-project" */
/* End: */
