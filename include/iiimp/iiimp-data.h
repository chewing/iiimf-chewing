#if !defined(IIIMP_DATA_H)
#define IIIMP_DATA_H

/* $Id: iiimp-data.h,v 1.1.1.1 2003/12/10 04:42:54 llch Exp $ */


#include <stdio.h>
#include <sys/types.h>

#if defined(linux)
#include <stdint.h>
typedef unsigned char	uchar_t;
typedef unsigned int	uint_t;
#endif /* linux */

#include <iiimp-opcode.h>


#ifdef	__cplusplus
extern "C" {
#endif

#define iiimp_MESSAGE_SIZE_MAX_4 ((1 << 24) - 1)

/* primitive data type */
typedef uint8_t			IIIMP_card7;
typedef uint8_t			IIIMP_card8;
typedef uint16_t		IIIMP_card16;
typedef uint32_t		IIIMP_card32;
typedef int8_t			IIIMP_int8;
typedef int16_t			IIIMP_int16;
typedef int32_t			IIIMP_int32;

typedef struct {
    size_t		nbyte;
    int			count;
    IIIMP_card16 *	ptr;
} IIIMP_card16_list;

typedef struct {
    size_t		nbyte;
    int			count;
    IIIMP_card32 *	ptr;
} IIIMP_card32_list;


/* composite data type */

typedef struct {
    size_t		nbyte;
    uchar_t *		ptr;
} IIIMP_byte_stream;

typedef struct iiimp_string {
    size_t			nbyte;
    size_t			len;
    IIIMP_card16 *		ptr;
    struct iiimp_string *	next;
} IIIMP_string;

typedef struct {
    size_t		nbyte;
    IIIMP_card32	id;
    IIIMP_card32	feedback;
} IIIMP_feedback_attr;

typedef struct {
    size_t			nbyte;
    int				count;
    IIIMP_feedback_attr *	ptr;
} IIIMP_feedback_attr_list;

typedef struct iiimp_char_with_feedback {
    size_t				nbyte;
    IIIMP_card16			code;
    IIIMP_feedback_attr_list *		feedback_attr;
    struct iiimp_char_with_feedback *	next;
} IIIMP_char_with_feedback;

typedef struct iiimp_operation {
    size_t			nbyte;
    IIIMP_string *		id;
    IIIMP_byte_stream		value;
    struct iiimp_operation *	next;
} IIIMP_operation;

typedef struct iiimp_text	IIIMP_text;

typedef struct iiimp_annotation_value {
    size_t				nbyte;
    IIIMP_int32				start_index;
    IIIMP_int32				end_index;
    IIIMP_int32				length;
    union {
	IIIMP_text *	text;
	IIIMP_string *	string;
    }					v;
    struct iiimp_annotation_value *	next;
} IIIMP_annotation_value;

typedef struct iiimp_annotation {
    size_t			nbyte;
    IIIMP_card32		id;
    size_t			value_nbyte;
    IIIMP_annotation_value *	value;
    struct iiimp_annotation *	next;
} IIIMP_annotation;

struct iiimp_text {
    size_t			nbyte;
    size_t			char_with_feedback_nbyte;
    IIIMP_char_with_feedback *	char_with_feedback;
    size_t			annotation_nbyte;
    IIIMP_annotation *		annotation;
    struct iiimp_text *		next;
};

typedef struct iiimp_imattribute	IIIMP_imattribute;

typedef struct {
    size_t		nbyte;
    IIIMP_string *	type;		/* Application type */
    IIIMP_string *	os_name;	/* Operating system name */
    IIIMP_string *	arch;		/* Operating system architecture */
    IIIMP_string *	version;	/* Operating system version */
    IIIMP_string *	X_display_name;	/* X display name */
    IIIMP_string *	X_server_vendor;/* X service vendor */
} IIIMP_client_descriptor;

typedef struct iiimp_object_descriptor {
    size_t		nbyte;
    int			category;	/* object category */
    size_t		size;		/* object size */
    int			id_pre;		/* predefined attribute id */
    int			id_dyn;		/* dynamically assigned id */
    IIIMP_string *	rdun;		/* reverse domain unique name */
    IIIMP_string *	hrn;		/* human readable name */
    IIIMP_string *	signature;	/* signature */
    IIIMP_string *	user;		/* object user */
    struct iiimp_object_descriptor *		next;
} IIIMP_object_descriptor;

typedef struct {
    size_t		nbyte;
    IIIMP_string *	contents;	/* contents of CCDEF */
} IIIMP_ccdef;

typedef struct iiimp_language {
    size_t			nbyte;
    IIIMP_string *		hrn;	/* human readable name */
    IIIMP_string *		id;	/* language identifier */
    struct iiimp_language *	next;
} IIIMP_language;

typedef struct {
    size_t		nbyte;
    size_t		class_names_nbyte;
    IIIMP_string *	class_names;	/* class_names */
    IIIMP_byte_stream	value;		/* jar file byte stream */
} IIIMP_jarfile_object;

typedef struct iiimp_inputmethod_descriptor {
    size_t		nbyte;
    int			id;		/* Input Method Identifier */
    IIIMP_string *	rdun;		/* reverse domain unique name */
    IIIMP_string *	hrn;		/* human readable name */
    size_t		language_nbyte;
    IIIMP_language *	language;	/* supported language list */
    struct iiimp_inputmethod_descriptor *	next;
} IIIMP_inputmethod_descriptor;

typedef struct {
    size_t		nbyte;
    IIIMP_string *	object;		/* object */
} IIIMP_binaryfile_object;

typedef union {
    void *				any;
    IIIMP_inputmethod_descriptor *	inputmethod_descriptor;
    IIIMP_object_descriptor *		object_descriptor;
    IIIMP_client_descriptor *		client_descriptor;
    IIIMP_ccdef *			ccdef;
    IIIMP_jarfile_object *		jarfile_object;
    IIIMP_binaryfile_object *		binaryfile_object;
} IIIMP_imattribute_value;

struct iiimp_imattribute {
    size_t			nbyte;
    int				id;	/* Input Method Attribute ID */
    int				id_pre;	/* predefined attribute id */
    int				id_dyn;	/* predefined attribute id */
    size_t			value_nbyte;
    IIIMP_imattribute_value	value;	/* Input Method Attribute Value */
    struct iiimp_imattribute *	next;	/* pointer to the next attribute */
};

typedef union {
    IIIMP_string *	input_language;
    IIIMP_card32_list *	character_subsets;
    IIIMP_string *	input_method_name;
    IIIMP_card16	input_method;
} IIIMP_icattribute_value;

typedef struct iiimp_icattribute IIIMP_icattribute;

struct iiimp_icattribute {
    size_t			nbyte;
    int				id;
    size_t			value_nbyte;
    IIIMP_icattribute_value	value;	/* Input Method Attribute Value */
    struct iiimp_icattribute *	next;	/* pointer to the next attribute */
};

typedef struct {
    IIIMP_int32		keycode;
    IIIMP_int32		keychar;
    IIIMP_int32		modifier;
    IIIMP_int32		time_stamp;
} IIIMP_keyevent;

typedef struct {
    size_t		nbyte;
    int			count;
    IIIMP_keyevent *	keyevent;
} IIIMP_keyevent_list;

typedef union {
    void *			any;
    IIIMP_string *		string;
    IIIMP_text *		text;
    IIIMP_keyevent_list *	keyevent_list;
} IIIMP_contents_value;

typedef struct {
    size_t			nbyte;
    IIIMP_card32		type;
    size_t			value_nbyte;
    IIIMP_contents_value	value;
} IIIMP_contents;


/* message data type */

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
} IIIMP_simple;

typedef struct {
    IIIMP_card7		opcode;
    int			byte_order;
    int			protocol_version;
    IIIMP_string *	user_name;
    IIIMP_string *	auth;
} IIIMP_connect;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_string *	language;
} IIIMP_connect_reply;

typedef IIIMP_simple	IIIMP_disconnect;

typedef IIIMP_simple	IIIMP_disconnect_reply;

typedef struct {
    IIIMP_card7			opcode;
    IIIMP_card16		im_id;
    IIIMP_keyevent_list *	trigger_on;
    IIIMP_keyevent_list *	trigger_off;
} IIIMP_register_trigger_keys;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    int			flag;
} IIIMP_trigger_notify;

typedef IIIMP_simple	IIIMP_trigger_notify_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_imattribute *	attr_list;
} IIIMP_setimvalues;

typedef IIIMP_simple	IIIMP_setimvalues_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16_list *	attr_list;
} IIIMP_getimvalues;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_imattribute *	attr_list;
} IIIMP_getimvalues_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_icattribute *	attr_list;
} IIIMP_createic;

typedef IIIMP_simple	IIIMP_createic_reply;

typedef IIIMP_simple	IIIMP_destroyic;

typedef IIIMP_simple	IIIMP_destroyic_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_icattribute *	attr_list;
} IIIMP_seticvalues;

typedef IIIMP_simple	IIIMP_seticvalues_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_card16_list *	attr_list;
} IIIMP_geticvalues;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_icattribute *	attr_list;
} IIIMP_geticvalues_reply;

typedef IIIMP_simple	IIIMP_seticfocus;
typedef IIIMP_simple	IIIMP_seticfocus_reply;
typedef IIIMP_simple	IIIMP_unseticfocus;
typedef IIIMP_simple	IIIMP_unseticfocus_reply;
typedef IIIMP_simple	IIIMP_resetic;
typedef IIIMP_simple	IIIMP_resetic_reply;
typedef IIIMP_simple	IIIMP_preedit_start;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_int32		maximum_length;
} IIIMP_preedit_start_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_int32		caret;
    IIIMP_int32		change_first;
    IIIMP_int32		change_length;
    IIIMP_contents *	preedit;
} IIIMP_preedit_draw;

typedef IIIMP_simple	IIIMP_preedit_draw_reply;
typedef IIIMP_simple	IIIMP_preedit_done;
typedef IIIMP_simple	IIIMP_preedit_done_reply;
typedef IIIMP_simple	IIIMP_status_start;
typedef IIIMP_simple	IIIMP_status_start_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_contents *	status;
} IIIMP_status_draw;

typedef IIIMP_simple	IIIMP_status_draw_reply;
typedef IIIMP_simple	IIIMP_status_done;
typedef IIIMP_simple	IIIMP_status_done_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_contents *	contents;
} IIIMP_forward_event;

typedef IIIMP_simple	IIIMP_forward_event_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_contents *	contents;
    IIIMP_operation *	operation;
} IIIMP_forward_event_with_operations;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_operation *	operation;
} IIIMP_forward_event_with_operations_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_contents *	contents;
} IIIMP_commit_string;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    int			master;
    int			choice_per_window;
    int			rows;
    int			columns;
    int			direction;
    int			label_owner;
} IIIMP_lookup_choice_start;

typedef IIIMP_simple	IIIMP_lookup_choice_start_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    int			first;
    int			last;
    int			current;
    IIIMP_text *	choice;
    IIIMP_text *	index_label;
    IIIMP_text *	title;
} IIIMP_lookup_choice_draw;

typedef IIIMP_simple	IIIMP_lookup_choice_draw_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    int			type;
    int			value;
} IIIMP_lookup_choice_process;

typedef IIIMP_simple	IIIMP_lookup_choice_process_reply;
typedef IIIMP_simple	IIIMP_lookup_choice_done;
typedef IIIMP_simple	IIIMP_lookup_choice_done_reply;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_card32	class_index;
    IIIMP_string *	input_method_name;
} IIIMP_aux_simple;

typedef struct {
    IIIMP_card7		opcode;
    IIIMP_card16	im_id;
    IIIMP_card16	ic_id;
    IIIMP_card32	class_index;
    IIIMP_string *	input_method_name;
    IIIMP_card32_list *	integer_value;
    IIIMP_string *	string_value;
} IIIMP_aux_value;

typedef IIIMP_aux_simple	IIIMP_aux_start;
typedef IIIMP_aux_simple	IIIMP_aux_start_reply;
typedef IIIMP_aux_value		IIIMP_aux_draw;
typedef IIIMP_aux_simple	IIIMP_aux_draw_reply;
typedef IIIMP_aux_simple	IIIMP_aux_done;
typedef IIIMP_aux_simple	IIIMP_aux_done_reply;
typedef IIIMP_aux_value		IIIMP_aux_setvalues;
typedef IIIMP_aux_simple	IIIMP_aux_setvalues_reply;


typedef struct {
    char	dummy[1];
} IIIMP_simple_v;

typedef struct {
    int			byte_order;
    int			protocol_version;
    IIIMP_string *	user_name;
    IIIMP_string *	auth;
} IIIMP_connect_v;

typedef struct {
    IIIMP_string *	language;
} IIIMP_connect_reply_v;

typedef IIIMP_simple_v	IIIMP_disconnect_v;

typedef IIIMP_simple_v	IIIMP_disconnect_reply_v;

typedef struct {
    IIIMP_keyevent_list *	trigger_on;
    IIIMP_keyevent_list *	trigger_off;
} IIIMP_register_trigger_keys_v;

typedef struct {
    int	flag;
} IIIMP_trigger_notify_v;

typedef IIIMP_simple_v	IIIMP_trigger_notify_reply_v;

typedef struct {
    IIIMP_imattribute *	attr_list;
} IIIMP_setimvalues_v;

typedef IIIMP_simple_v	IIIMP_setimvalues_reply_v;

typedef struct {
    IIIMP_card16_list *	attr_list;
} IIIMP_getimvalues_v;

typedef struct {
    IIIMP_imattribute *	attr_list;
} IIIMP_getimvalues_reply_v;

typedef struct {
    IIIMP_icattribute *	attr_list;
} IIIMP_createic_v;

typedef IIIMP_simple_v	IIIMP_createic_reply_v;

typedef IIIMP_simple_v	IIIMP_destroyic_v;

typedef IIIMP_simple_v	IIIMP_destroyic_reply_v;

typedef struct {
    IIIMP_icattribute *	attr_list;
} IIIMP_seticvalues_v;

typedef IIIMP_simple_v	IIIMP_seticvalues_reply_v;

typedef struct {
    IIIMP_card16_list *	attr_list;
} IIIMP_geticvalues_v;

typedef struct {
    IIIMP_icattribute *	attr_list;
} IIIMP_geticvalues_reply_v;

typedef IIIMP_simple_v	IIIMP_seticfocus_v;
typedef IIIMP_simple_v	IIIMP_seticfocus_reply_v;
typedef IIIMP_simple_v	IIIMP_unseticfocus_v;
typedef IIIMP_simple_v	IIIMP_unseticfocus_reply_v;
typedef IIIMP_simple_v	IIIMP_resetic_v;
typedef IIIMP_simple_v	IIIMP_resetic_reply_v;
typedef IIIMP_simple_v	IIIMP_preedit_start_v;

typedef struct {
    IIIMP_int32		maximum_length;
} IIIMP_preedit_start_reply_v;

typedef struct {
    IIIMP_int32		caret;
    IIIMP_int32		change_first;
    IIIMP_int32		change_length;
    IIIMP_contents *	preedit;
} IIIMP_preedit_draw_v;

typedef IIIMP_simple_v	IIIMP_preedit_draw_reply_v;
typedef IIIMP_simple_v	IIIMP_preedit_done_v;
typedef IIIMP_simple_v	IIIMP_preedit_done_reply_v;
typedef IIIMP_simple_v	IIIMP_status_start_v;
typedef IIIMP_simple_v	IIIMP_status_start_reply_v;

typedef struct {
    IIIMP_contents *	status;
} IIIMP_status_draw_v;

typedef IIIMP_simple_v	IIIMP_status_draw_reply_v;
typedef IIIMP_simple_v	IIIMP_status_done_v;
typedef IIIMP_simple_v	IIIMP_status_done_reply_v;

typedef struct {
    IIIMP_contents *	contents;
} IIIMP_forward_event_v;

typedef IIIMP_simple_v	IIIMP_forward_event_reply_v;

typedef struct {
    IIIMP_contents *	contents;
    IIIMP_operation *	operation;
} IIIMP_forward_event_with_operations_v;

typedef struct {
    IIIMP_operation *	operation;
} IIIMP_forward_event_with_operations_reply_v;

typedef struct {
    IIIMP_contents *	contents;
} IIIMP_commit_string_v;

typedef struct {
    int	master;
    int	choice_per_window;
    int	rows;
    int	columns;
    int	direction;
    int	label_owner;
} IIIMP_lookup_choice_start_v;

typedef IIIMP_simple_v	IIIMP_lookup_choice_start_reply_v;

typedef struct {
    int			first;
    int			last;
    int			current;
    IIIMP_text *	choice;
    IIIMP_text *	index_label;
    IIIMP_text *	title;
} IIIMP_lookup_choice_draw_v;

typedef IIIMP_simple_v	IIIMP_lookup_choice_draw_reply_v;

typedef struct {
    int	type;
    int	value;
} IIIMP_lookup_choice_process_v;

typedef IIIMP_simple_v	IIIMP_lookup_choice_process_reply_v;
typedef IIIMP_simple_v	IIIMP_lookup_choice_done_v;
typedef IIIMP_simple_v	IIIMP_lookup_choice_done_reply_v;

typedef struct {
    IIIMP_card32	class_index;
    IIIMP_string *	input_method_name;
} IIIMP_aux_simple_v;

typedef struct {
    IIIMP_card32	class_index;
    IIIMP_string *	input_method_name;
    IIIMP_card32_list *	integer_value;
    IIIMP_string *	string_value;
} IIIMP_aux_value_v;

typedef IIIMP_aux_simple_v	IIIMP_aux_start_v;
typedef IIIMP_aux_simple_v	IIIMP_aux_start_reply_v;
typedef IIIMP_aux_value_v	IIIMP_aux_draw_v;
typedef IIIMP_aux_simple_v	IIIMP_aux_draw_reply_v;
typedef IIIMP_aux_simple_v	IIIMP_aux_done_v;
typedef IIIMP_aux_simple_v	IIIMP_aux_done_reply_v;
typedef IIIMP_aux_value_v	IIIMP_aux_setvalues_v;
typedef IIIMP_aux_simple_v	IIIMP_aux_setvalues_reply_v;

typedef struct {
    int	number;
} IIIMP_protocol_version_v;

typedef struct {
    int		opcode;
    uint32_t	length;	/* (byte_length << 4) */
    int		im_id;
    int		ic_id;

    union {
	IIIMP_connect_v			connect;
	IIIMP_connect_reply_v		connect_reply;
	IIIMP_disconnect_v		disconnect;
	IIIMP_disconnect_reply_v	disconnect_reply;
	IIIMP_register_trigger_keys_v	register_trigger_keys;
	IIIMP_trigger_notify_v		trigger_notify;
	IIIMP_trigger_notify_reply_v	trigger_notify_reply;
	IIIMP_setimvalues_v		setimvalues;
	IIIMP_setimvalues_reply_v	setimvalues_reply;
	IIIMP_getimvalues_v		getimvalues;
	IIIMP_getimvalues_reply_v	getimvalues_reply;
	
	IIIMP_forward_event_v		forward_event;
	IIIMP_forward_event_reply_v	forward_event_reply;
	
	IIIMP_commit_string_v		commit_string;
	
	IIIMP_forward_event_with_operations_v
					forward_event_with_operations;
	IIIMP_forward_event_with_operations_reply_v
					forward_event_with_operations_reply;

	IIIMP_createic_v		createic;
	IIIMP_createic_reply_v		createic_reply;
	IIIMP_destroyic_v		destroyic;
	IIIMP_destroyic_reply_v		destroyic_reply;
	IIIMP_seticvalues_v		seticvalues;
	IIIMP_seticvalues_reply_v	seticvalues_reply;
	IIIMP_geticvalues_v		geticvalues;
	IIIMP_geticvalues_reply_v	geticvalues_reply;
	IIIMP_seticfocus_v		seticfocus;
	IIIMP_seticfocus_reply_v	seticfocus_reply;
	IIIMP_unseticfocus_v		unseticfocus;
	IIIMP_unseticfocus_reply_v	unseticfocus_reply;
	IIIMP_resetic_v			resetic;
	IIIMP_resetic_reply_v		resetic_reply;
	IIIMP_preedit_start_v		preedit_start;
	IIIMP_preedit_start_reply_v	preedit_start_reply;
	IIIMP_preedit_draw_v		preedit_draw;
	IIIMP_preedit_draw_reply_v	preedit_draw_reply;
	IIIMP_preedit_done_v		preedit_done;
	IIIMP_preedit_done_reply_v	preedit_done_reply;
	
	IIIMP_status_start_v		status_start;
	IIIMP_status_start_reply_v	status_start_reply;
	IIIMP_status_draw_v		status_draw;
	IIIMP_status_draw_reply_v	status_draw_reply;
	IIIMP_status_done_v		status_done;
	IIIMP_status_done_reply_v	status_done_reply;

	IIIMP_lookup_choice_start_v	lookup_choice_start;
	IIIMP_lookup_choice_start_reply_v
					lookup_choice_start_reply;
	IIIMP_lookup_choice_draw_v	lookup_choice_draw;
	IIIMP_lookup_choice_draw_reply_v	lookup_choice_draw_reply;
	IIIMP_lookup_choice_done_v	lookup_choice_done;
	IIIMP_lookup_choice_done_reply_v	lookup_choice_done_reply;
	IIIMP_lookup_choice_process_v	lookup_choice_process;
	IIIMP_lookup_choice_process_reply_v
					lookup_choice_process_reply;

	IIIMP_aux_simple_v		aux_simple;
	IIIMP_aux_value_v		aux_value;

	IIIMP_aux_start_v		aux_start;
	IIIMP_aux_start_reply_v		aux_start_reply;
	IIIMP_aux_draw_v		aux_draw;
	IIIMP_aux_draw_reply_v		aux_draw_reply;
	IIIMP_aux_done_v		aux_done;
	IIIMP_aux_done_reply_v		aux_done_reply;
	IIIMP_aux_setvalues_v		aux_setvalues;
	IIIMP_aux_setvalues_reply_v	aux_setvalues_reply;

	IIIMP_protocol_version_v	protocol_version;
    }		v;

} IIIMP_message;

typedef struct iiimp_data_s	IIIMP_data_s;


/* enumeration */

typedef enum {
	IIIMP_DATA_NO_ERROR		= 0,
	IIIMP_DATA_MALLOC_ERROR		= 1,
	IIIMP_DATA_INVALID		= 2,
	IIIMP_DATA_PROTOCOL_VERSION_ERROR = 3
} IIIMP_status;


/* public interface prototype */

extern IIIMP_message *	iiimp_message_unpack(
				IIIMP_data_s *		data_s,
				IIIMP_card7		opcode,
				size_t *		nbyte,
				const uchar_t **	ptr);
extern uchar_t *	iiimp_message_pack(
				IIIMP_data_s *		data_s,
				IIIMP_message *		m,
				size_t *		nbyte);

extern IIIMP_data_s *	iiimp_data_s_new(void);
extern IIIMP_data_s *	iiimp_data_s_with_protocol_version_new(int protocol_version);
extern int		iiimp_data_s_get_protocol_version(IIIMP_data_s * data_s);
extern void		iiimp_data_s_delete(IIIMP_data_s * im);

extern FILE *	iiimp_data_print_fp(IIIMP_data_s * data_s, FILE * fp);
extern uint_t	iiimp_data_print_flag(IIIMP_data_s * data_s, uint_t log_flag);
extern int	iiimp_data_status(IIIMP_data_s * im);

extern void	iiimp_message_print(IIIMP_data_s * data_s, IIIMP_message * m);

extern const char *	iiimp_opcode_string(int num);


extern uchar_t *
iiimp_simple_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    size_t *		buf_size);

extern uchar_t *
iiimp_connect_pack(
    IIIMP_data_s *	data_s,
    IIIMP_string *	user_name,
    IIIMP_string *	auth_protocol,
    size_t *		buf_size);

extern uchar_t *
iiimp_protocol_version_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    int			protocol_version,
    size_t *		buf_size);

extern uchar_t *
iiimp_connect_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_string *	language_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_register_trigger_keys_pack(
    IIIMP_data_s *		data_s,
    IIIMP_card16		im_id,
    IIIMP_keyevent_list *	trigger_on,
    IIIMP_keyevent_list *	trigger_off,
    size_t *			buf_size);

extern uchar_t *
iiimp_trigger_notify_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	flag,
    size_t *		buf_size);

extern uchar_t *
iiimp_setimvalues_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_imattribute *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_getimvalues_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16_list *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_getimvalues_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_imattribute *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_forward_event_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents,
    size_t *		buf_size);

extern uchar_t *
iiimp_commit_string_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents,
    size_t *		buf_size);

extern uchar_t *
iiimp_forward_event_with_operations_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents,
    IIIMP_operation *	operation_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_forward_event_with_operations_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_operation *	operation_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_createic_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_icattribute *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_seticvalues_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_icattribute *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_geticvalues_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16_list *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_geticvalues_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_icattribute *	attr_list,
    size_t *		buf_size);

extern uchar_t *
iiimp_preedit_start_reply_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_int32		maximum_length,
    size_t *		buf_size);

extern uchar_t *
iiimp_preedit_draw_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_int32		caret,
    IIIMP_int32		change_first,
    IIIMP_int32		change_length,
    IIIMP_contents *	preedit,
    size_t *		buf_size);

extern uchar_t *
iiimp_status_draw_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	status,
    size_t *		buf_size_return);

extern uchar_t *
iiimp_lookup_choice_start_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    int			master,
    int			choice_per_window,
    int			rows,
    int			columns,
    int			direction,
    int			label_owner,
    size_t *		buf_size);

extern uchar_t *
iiimp_lookup_choice_draw_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    int			first,
    int			last,
    int			current,
    IIIMP_text *	choice,
    IIIMP_text *	index_label,
    IIIMP_text *	title,
    size_t *		buf_size);

extern uchar_t *
iiimp_lookup_choice_process_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	type,
    IIIMP_card16	value,
    size_t *		buf_size);

extern uchar_t *
iiimp_aux_simple_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card32	class_index,
    IIIMP_string *	input_method_name,
    size_t *		buf_size);

extern uchar_t *
iiimp_aux_value_pack(
    IIIMP_data_s *	data_s,
    IIIMP_card7		code,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card32	class_index,
    IIIMP_string *	input_method_name,
    IIIMP_card32_list *	integer_value,
    IIIMP_string *	string_value,
    size_t *		buf_size);

#define iiimp_disconnect_pack(data_s, im_id, buf_size) \
		iiimp_simple_pack(data_s, IM_DISCONNECT, im_id, 0, buf_size)
#define iiimp_disconnect_reply_pack(data_s, im_id, buf_size) \
		iiimp_simple_pack(data_s, IM_DISCONNECT_REPLY, im_id, 0, buf_size)
#define iiimp_trigger_notify_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_TRIGGER_NOTIFY_REPLY, im_id, ic_id, buf_size)
#define iiimp_setimvalues_reply_pack(data_s, im_id, buf_size) \
		iiimp_simple_pack(data_s, IM_SETIMVALUES_REPLY, im_id, 0, buf_size)
#define iiimp_forward_event_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_FORWARD_EVENT_REPLY, im_id, ic_id, buf_size)
#define iiimp_createic_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_CREATEIC_REPLY, im_id, ic_id, buf_size)
#define iiimp_destroyic_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_DESTROYIC, im_id, ic_id, buf_size)
#define iiimp_destroyic_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_DESTROYIC_REPLY, im_id, ic_id, buf_size)
#define iiimp_seticvalues_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_SETICVALUES_REPLY, im_id, ic_id, buf_size)
#define iiimp_seticfocus_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_SETICFOCUS, im_id, ic_id, buf_size)
#define iiimp_seticfocus_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_SETICFOCUS_REPLY, im_id, ic_id, buf_size)
#define iiimp_unseticfocus_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_UNSETICFOCUS, im_id, ic_id, buf_size)
#define iiimp_unseticfocus_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_UNSETICFOCUS_REPLY, im_id, ic_id, buf_size)
#define iiimp_resetic_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_RESETIC, im_id, ic_id, buf_size)
#define iiimp_resetic_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_RESETIC_REPLY, im_id, ic_id, buf_size)
#define iiimp_preedit_start_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_PREEDIT_START, im_id, ic_id, buf_size)
#define iiimp_preedit_draw_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_PREEDIT_DRAW_REPLY, im_id, ic_id, buf_size)
#define iiimp_preedit_done_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_PREEDIT_DONE, im_id, ic_id, buf_size)
#define iiimp_preedit_done_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_PREEDIT_DONE_REPLY, im_id, ic_id, buf_size)
#define iiimp_status_start_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_STATUS_START, im_id, ic_id, buf_size)
#define iiimp_status_start_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_STATUS_START_REPLY, im_id, ic_id, buf_size)
#define iiimp_status_draw_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_STATUS_DRAW_REPLY, im_id, ic_id, buf_size)
#define iiimp_status_done_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_STATUS_DONE, im_id, ic_id, buf_size)
#define iiimp_status_done_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_STATUS_DONE_REPLY, im_id, ic_id, buf_size)
#define iiimp_lookup_choice_start_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_LOOKUP_CHOICE_START_REPLY, im_id, ic_id, buf_size)
#define iiimp_lookup_choice_draw_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_LOOKUP_CHOICE_DRAW_REPLY, im_id, ic_id, buf_size)
#define iiimp_lookup_choice_done_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_LOOKUP_CHOICE_DONE, im_id, ic_id, buf_size)
#define iiimp_lookup_choice_done_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_LOOKUP_CHOICE_DONE_REPLY, im_id, ic_id, buf_size)
#define iiimp_lookup_choice_process_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_simple_pack(data_s, IM_LOOKUP_CHOICE_PROCESS_REPLY, im_id, ic_id, buf_size)
#define iiimp_aux_start_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_START, im_id, ic_id, buf_size)
#define iiimp_aux_start_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_START_REPLY, im_id, ic_id, buf_size)
#define iiimp_aux_draw_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_value_pack(data_s, IM_AUX_DRAW, im_id, ic_id, buf_size)
#define iiimp_aux_draw_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_DRAW_REPLY, im_id, ic_id, buf_size)
#define iiimp_aux_done_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_DONE, im_id, ic_id, buf_size)
#define iiimp_aux_done_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_DONE_REPLY, im_id, ic_id, buf_size)
#define iiimp_aux_setvalues_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_value_pack(data_s, IM_AUX_SETVALUES, im_id, ic_id, buf_size)
#define iiimp_aux_setvalues_reply_pack(data_s, im_id, ic_id, buf_size) \
		iiimp_aux_simple_pack(data_s, IM_AUX_SETVALUES_REPLY, im_id, ic_id, buf_size)


extern IIIMP_card16_list *
iiimp_card16_list_new(
    IIIMP_data_s *		data_s,
    int				count,
    const IIIMP_card16 *	ptr);

extern IIIMP_card32_list *
iiimp_card32_list_new(
    IIIMP_data_s *		data_s,
    int				count,
    const IIIMP_card32 *	ptr);

extern IIIMP_string *
iiimp_string_new(
    IIIMP_data_s *		data_s,
    size_t			len,
    const IIIMP_card16 *	ptr);

extern IIIMP_feedback_attr_list *
iiimp_feedback_attr_list_new(
    IIIMP_data_s *		data_s,
    int				count,
    const IIIMP_feedback_attr *	ptr);

extern IIIMP_char_with_feedback *
iiimp_char_with_feedback_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		code,
    IIIMP_feedback_attr_list *	feedback_attr);

extern IIIMP_operation *
iiimp_operation_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	id,
    size_t		value_nbyte,
    uchar_t *		value);

extern IIIMP_annotation_value *
iiimp_annotation_value_text_new(
    IIIMP_data_s *	data_s,
    IIIMP_int32		start_index,
    IIIMP_int32		end_index,
    IIIMP_text *	value);

extern IIIMP_annotation_value *
iiimp_annotation_value_string_new(
    IIIMP_data_s *	data_s,
    IIIMP_int32		start_index,
    IIIMP_int32		end_index,
    IIIMP_string *	value);

extern IIIMP_annotation *
iiimp_annotation_new(
    IIIMP_data_s *		data_s,
    IIIMP_card32		id,
    IIIMP_annotation_value *	value);

extern IIIMP_text *
iiimp_text_new(
    IIIMP_data_s *		data_s,
    IIIMP_char_with_feedback *	cwf,
    IIIMP_annotation *		anno);

extern IIIMP_client_descriptor *
iiimp_client_descriptor_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	type,
    IIIMP_string *	os_name,
    IIIMP_string *	arch,
    IIIMP_string *	version,
    IIIMP_string *	X_display_name,
    IIIMP_string *	X_server_vendor);

extern IIIMP_object_descriptor *
iiimp_object_descriptor_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	category,
    IIIMP_card32	object_size,
    IIIMP_card16	id_pre,
    IIIMP_card16	id_dyn,
    IIIMP_string *	rdun,
    IIIMP_string *	hrn,
    IIIMP_string *	signature,
    IIIMP_string *	user);

extern IIIMP_ccdef *
iiimp_ccdef_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	contents);

extern IIIMP_language *
iiimp_language_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	hrn,
    IIIMP_string *	id);

extern IIIMP_jarfile_object *
iiimp_jarfile_object_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	class_names,
    size_t		value_nbyte,
    const uchar_t *	value);

extern IIIMP_inputmethod_descriptor *
iiimp_inputmethod_descriptor_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	id,
    IIIMP_string *	rdun,
    IIIMP_string *	hrn,
    IIIMP_language *	language);

extern IIIMP_binaryfile_object *
iiimp_binaryfile_object_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	object);

extern IIIMP_imattribute *
iiimp_imattribute_inputmethod_descriptor_new(
    IIIMP_data_s *			data_s,
    IIIMP_card16			id,
    IIIMP_card16			id_dyn,
    IIIMP_inputmethod_descriptor *	value);

extern IIIMP_imattribute *
iiimp_imattribute_object_descriptor_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_object_descriptor *	value);

extern IIIMP_imattribute *
iiimp_imattribute_client_descriptor_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_client_descriptor *	value);

extern IIIMP_imattribute *
iiimp_imattribute_ccdef_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	id,
    IIIMP_card16	id_dyn,
    IIIMP_ccdef *	value);

extern IIIMP_imattribute *
iiimp_imattribute_jar_gui_object_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_jarfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_jar_light_weight_engine_object_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_jarfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_binary_gui_object_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_binary_light_weight_engine_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_script_gui_object_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_imattribute *
iiimp_imattribute_script_light_weight_engine_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_icattribute *
iiimp_icattribute_input_language_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	value);

extern IIIMP_icattribute *
iiimp_icattribute_character_subsets_new(
    IIIMP_data_s *	data_s,
    IIIMP_card32_list *	value);

extern IIIMP_icattribute *
iiimp_icattribute_input_method_name_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	value);

extern IIIMP_icattribute *
iiimp_icattribute_input_method_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	value);

extern IIIMP_keyevent_list *
iiimp_keyevent_list_new(
    IIIMP_data_s *	data_s,
    int			count,
    IIIMP_keyevent *	k);

extern IIIMP_contents *
iiimp_contents_string_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	value);

extern IIIMP_contents *
iiimp_contents_text_new(
    IIIMP_data_s *	data_s,
    IIIMP_text *	value);

extern IIIMP_contents *
iiimp_contents_keyevent_list_new(
    IIIMP_data_s *		data_s,
    IIIMP_keyevent_list *	value);


/* public interface prototype - im_message_new */

extern IIIMP_message *
iiimp_simple_new(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id);

extern IIIMP_message *
iiimp_connect_new(
    IIIMP_data_s *	data_s,
    IIIMP_string *	user_name,
    IIIMP_string *	auth);

extern IIIMP_message *
iiimp_protocol_version_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    int			protocol_version);

extern IIIMP_message *
iiimp_connect_reply_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_string *	language_list);

#define iiimp_disconnect_new(data_s, im_id)	\
		iiimp_simple_new((data_s), IM_DISCONNECT, (im_id), 0)

#define iiimp_disconnect_reply_new(data_s, im_id)	\
		iiimp_simple_new((data_s), IM_DISCONNECT_REPLY, (im_id), 0)

extern IIIMP_message *
iiimp_register_trigger_keys_new(
    IIIMP_data_s *		data_s,
    IIIMP_card16		im_id,
    IIIMP_keyevent_list *	trigger_on,
    IIIMP_keyevent_list *	trigger_off);

extern IIIMP_message *
iiimp_trigger_notify_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	flag);

#define iiimp_trigger_notify_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_TRIGGER_NOTIFY_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_setimvalues_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_imattribute *	attr_list);

#define iiimp_setimvalues_reply_new(data_s, im_id)	\
		iiimp_simple_new((data_s), IM_SETIMVALUES_REPLY, (im_id), 0)

extern IIIMP_message *
iiimp_getimvalues_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16_list *	attr_list);

extern IIIMP_message *
iiimp_getimvalues_reply_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_imattribute *	attr_list);

extern IIIMP_message *
iiimp_forward_event_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents);

#define iiimp_forward_event_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_FORWARD_EVENT_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_commit_string_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents);

extern IIIMP_message *
iiimp_forward_event_with_operations_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	contents,
    IIIMP_operation *	operation);

extern IIIMP_message *
iiimp_forward_event_with_operations_reply_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_operation *	operation);


extern IIIMP_message *
iiimp_createic_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_icattribute *	attr_list);

#define iiimp_createic_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_CREATEIC_REPLY, \
				 (im_id), (ic_id))

#define iiimp_destroyic_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_DESTROYIC, \
				 (im_id), (ic_id))

#define iiimp_destroyic_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_DESTROYIC_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_seticvalues_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_icattribute *	attr_list);

#define iiimp_seticvalues_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_SETICVALUES_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_geticvalues_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16_list *	attr_list);

extern IIIMP_message *
iiimp_geticvalues_reply_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_icattribute *	attr_list);

#define iiimp_seticfocus_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_SETICFOCUS, \
				 (im_id), (ic_id))

#define iiimp_seticfocus_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_SETICFOCUS_REPLY, \
				 (im_id), (ic_id))

#define iiimp_unseticfocus_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_UNSETICFOCUS, \
				 (im_id), (ic_id))

#define iiimp_unseticfocus_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_UNSETICFOCUS_REPLY, \
				 (im_id), (ic_id))

#define iiimp_resetic_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_RESETIC, \
				 (im_id), (ic_id))

#define iiimp_resetic_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_RESETIC_REPLY, \
				 (im_id), (ic_id))

#define iiimp_preedit_start_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_PREEDIT_START, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_preedit_start_reply_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_int32		maximum_length);

extern IIIMP_message *
iiimp_preedit_draw_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_int32		aret,
    IIIMP_int32		change_first,
    IIIMP_int32		change_length,
    IIIMP_contents *	preedit);

#define iiimp_preedit_draw_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_PREEDIT_DRAW_REPLY, \
				 (im_id), (ic_id))

#define iiimp_preedit_done_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_PREEDIT_DONE, \
				 (im_id), (ic_id))

#define iiimp_preedit_done_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_PREEDIT_DONE_REPLY, \
				 (im_id), (ic_id))

#define iiimp_status_start_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_STATUS_START, \
				 (im_id), (ic_id))

#define iiimp_status_start_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_STATUS_START_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_status_draw_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_contents *	status);

#define iiimp_status_draw_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_STATUS_DRAW_REPLY, \
				 (im_id), (ic_id))

#define iiimp_status_done_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_STATUS_DONE, \
				 (im_id), (ic_id))

#define iiimp_status_done_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_STATUS_DONE_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_lookup_choice_start_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    int			master,
    int			choice_per_window,
    int			rows,
    int			columns,
    int			direction,
    int			label_owner);

#define iiimp_lookup_choice_start_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_LOOKUP_CHOICE_START_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_lookup_choice_draw_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    int			first,
    int			last,
    int			current,
    IIIMP_text *	choice,
    IIIMP_text *	index_label,
    IIIMP_text *	title);

#define iiimp_lookup_choice_draw_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_LOOKUP_CHOICE_DRAW_REPLY, \
				 (im_id), (ic_id))

#define iiimp_lookup_choice_done_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_LOOKUP_CHOICE_DONE, \
				 (im_id), (ic_id))

#define iiimp_lookup_choice_done_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_LOOKUP_CHOICE_DONE_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_lookup_choice_process_new(
    IIIMP_data_s *	data_s,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card16	type,
    IIIMP_card16	value);

#define iiimp_lookup_choice_process_reply_new(data_s, im_id, ic_id)	\
		iiimp_simple_new((data_s), IM_LOOKUP_CHOICE_PROCESS_REPLY, \
				 (im_id), (ic_id))

extern IIIMP_message *
iiimp_aux_simple_new(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card32	class_index,
    IIIMP_string *	input_method_name);

extern IIIMP_message *
iiimp_aux_value_new(
    IIIMP_data_s *	data_s,
    IIIMP_card7		opcode,
    IIIMP_card16	im_id,
    IIIMP_card16	ic_id,
    IIIMP_card32	class_index,
    IIIMP_string *	input_method_name,
    IIIMP_card32_list *	integer_value,
    IIIMP_string *	string_value);


#define iiimp_aux_start_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_START, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_start_reply_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_START_REPLY, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_draw_new(data_s, im_id, ic_id, class_index, input_method_name, int_val, str_val)	\
		iiimp_aux_value_new((data_s), IM_AUX_DRAW, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name), \
				     (int_val), (str_val))

#define iiimp_aux_draw_reply_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_DRAW_REPLY, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_done_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_DONE, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_done_reply_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_DONE_REPLY, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

#define iiimp_aux_setvalues_new(data_s, im_id, ic_id, class_index, input_method_name, int_val, str_val)	\
		iiimp_aux_value_new((data_s), IM_AUX_SETVALUES, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name), \
				     (int_val), (str_val))

#define iiimp_aux_setvalues_reply_new(data_s, im_id, ic_id, class_index, input_method_name)	\
		iiimp_aux_simple_new((data_s), IM_AUX_SETVALUES_REPLY, \
				     (im_id), (ic_id), \
				     (class_index), (input_method_name))

extern IIIMP_status
iiimp_card16_list_create(
    IIIMP_data_s *		data_s,
    IIIMP_card16_list **	ptr_ret,
    int				count,
    const IIIMP_card16 *	ptr);

extern IIIMP_status
iiimp_card32_list_create(
    IIIMP_data_s *		data_s,
    IIIMP_card32_list **	ptr_ret,
    int				count,
    const IIIMP_card32 *	ptr);

extern IIIMP_status
iiimp_string_create(
    IIIMP_data_s *		data_s,
    IIIMP_string **		ptr_ret,
    size_t			len,
    const IIIMP_card16 *	ptr);

extern IIIMP_status
iiimp_feedback_attr_list_create(
    IIIMP_data_s *		data_s,
    IIIMP_feedback_attr_list **	ptr_ret,
    int				count,
    const IIIMP_feedback_attr *	ptr);

extern IIIMP_status
iiimp_char_with_feedback_create(
    IIIMP_data_s *		data_s,
    IIIMP_char_with_feedback **	ptr_ret,
    IIIMP_card16		code,
    IIIMP_feedback_attr_list *	feedback_attr);

extern IIIMP_status
iiimp_operation_create(
    IIIMP_data_s *	data_s,
    IIIMP_operation **	ptr_ret,
    IIIMP_string *	id,
    size_t		value_nbyte,
    uchar_t *		value);

extern IIIMP_status
iiimp_annotation_value_text_create(
    IIIMP_data_s *		data_s,
    IIIMP_annotation_value **	ptr_ret,
    IIIMP_int32			start_index,
    IIIMP_int32			end_index,
    IIIMP_text *		value);

extern IIIMP_status
iiimp_annotation_value_string_create(
    IIIMP_data_s *		data_s,
    IIIMP_annotation_value **	ptr_ret,
    IIIMP_int32			start_index,
    IIIMP_int32			end_index,
    IIIMP_string *		value);

extern IIIMP_status
iiimp_annotation_create(
    IIIMP_data_s *		data_s,
    IIIMP_annotation **		ptr_ret,
    IIIMP_card32		id,
    IIIMP_annotation_value *	value);

extern IIIMP_status
iiimp_text_create(
    IIIMP_data_s *		data_s,
    IIIMP_text **		ptr_ret,
    IIIMP_char_with_feedback *	cwf,
    IIIMP_annotation *		anno);

extern IIIMP_status
iiimp_client_descriptor_create(
    IIIMP_data_s *		data_s,
    IIIMP_client_descriptor **	ptr_ret,
    IIIMP_string *		type,
    IIIMP_string *		os_name,
    IIIMP_string *		arch,
    IIIMP_string *		version,
    IIIMP_string *		X_display_name,
    IIIMP_string *		X_server_vendor);

extern IIIMP_status
iiimp_object_descriptor_create(
    IIIMP_data_s *		data_s,
    IIIMP_object_descriptor **	ptr_ret,
    IIIMP_card16		category,
    IIIMP_card32		object_size,
    IIIMP_card16		id_pre,
    IIIMP_card16		id_dyn,
    IIIMP_string *		rdun,
    IIIMP_string *		hrn,
    IIIMP_string *		signature,
    IIIMP_string *		user);

extern IIIMP_status
iiimp_ccdef_create(
    IIIMP_data_s *	data_s,
    IIIMP_ccdef **	ptr_ret,
    IIIMP_string *	contents);

extern IIIMP_status
iiimp_language_create(
    IIIMP_data_s *	data_s,
    IIIMP_language **	ptr_ret,
    IIIMP_string *	hrn,
    IIIMP_string *	id);

extern IIIMP_status
iiimp_jarfile_object_create(
    IIIMP_data_s *		data_s,
    IIIMP_jarfile_object **	ptr_ret,
    IIIMP_string *		class_names,
    size_t			value_nbyte,
    uchar_t *			value);

extern IIIMP_status
iiimp_inputmethod_descriptor_create(
    IIIMP_data_s *			data_s,
    IIIMP_inputmethod_descriptor **	ptr_ret,
    IIIMP_card16			id,
    IIIMP_string *			rdun,
    IIIMP_string *			hrn,
    IIIMP_language *			language);

extern IIIMP_status
iiimp_binaryfile_object_create(
    IIIMP_data_s *		data_s,
    IIIMP_binaryfile_object **	ptr_ret,
    IIIMP_string *		object);

extern IIIMP_status
iiimp_imattribute_inputmethod_descriptor_create(
    IIIMP_data_s *			data_s,
    IIIMP_imattribute **		ptr_ret,
    IIIMP_card16			id,
    IIIMP_card16			id_dyn,
    IIIMP_inputmethod_descriptor *	value);

extern IIIMP_status
iiimp_imattribute_object_descriptor_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_object_descriptor *	value);

extern IIIMP_status
iiimp_imattribute_client_descriptor_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_client_descriptor *	value);

extern IIIMP_status
iiimp_imattribute_ccdef_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_ccdef *		value);

extern IIIMP_status
iiimp_imattribute_jar_gui_object_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_jarfile_object *	value);

extern IIIMP_status
iiimp_imattribute_jar_light_weight_engine_object_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_jarfile_object *	value);

extern IIIMP_status
iiimp_imattribute_binary_gui_object_create(
    IIIMP_data_s *			data_s,
    IIIMP_imattribute **		ptr_ret,
    IIIMP_card16			id,
    IIIMP_card16			id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_status
iiimp_imattribute_binary_light_weight_engine_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_status
iiimp_imattribute_script_gui_object_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_status
iiimp_imattribute_script_light_weight_engine_create(
    IIIMP_data_s *		data_s,
    IIIMP_imattribute **	ptr_ret,
    IIIMP_card16		id,
    IIIMP_card16		id_dyn,
    IIIMP_binaryfile_object *	value);

extern IIIMP_status
iiimp_icattribute_input_language_create(
    IIIMP_data_s *		data_s,
    IIIMP_icattribute **	ptr_ret,
    IIIMP_string *		value);

extern IIIMP_status
iiimp_icattribute_character_subsets_create(
    IIIMP_data_s *		data_s,
    IIIMP_icattribute **	ptr_ret,
    IIIMP_card32_list *		value);

extern IIIMP_status
iiimp_icattribute_input_method_name_create(
    IIIMP_data_s *		data_s,
    IIIMP_icattribute **	ptr_ret,
    IIIMP_string *		value);

extern IIIMP_status
iiimp_icattribute_input_method_create(
    IIIMP_data_s *		data_s,
    IIIMP_icattribute **	ptr_ret,
    IIIMP_card16		value);

extern IIIMP_status
iiimp_keyevent_list_create(
    IIIMP_data_s *		data_s,
    IIIMP_keyevent_list **	ptr_ret,
    int				count,
    IIIMP_keyevent *		k);

extern IIIMP_status
iiimp_contents_string_create(
    IIIMP_data_s *	data_s,
    IIIMP_contents **	ptr_ret,
    IIIMP_string *	value);

extern IIIMP_status
iiimp_contents_text_create(
    IIIMP_data_s *	data_s,
    IIIMP_contents **	ptr_ret,
    IIIMP_text *	value);

extern IIIMP_status
iiimp_contents_keyevent_list_create(
    IIIMP_data_s *		data_s,
    IIIMP_contents **		ptr_ret,
    IIIMP_keyevent_list *	value);

void	iiimp_message_delete(IIIMP_data_s * data_s, IIIMP_message * m);


/* prototype of composite data free function */

void	iiimp_card16_list_delete(IIIMP_data_s * data_s, IIIMP_card16_list * data);
void	iiimp_card32_list_delete(IIIMP_data_s * data_s, IIIMP_card32_list * data);
void	iiimp_string_delete(IIIMP_data_s * data_s, IIIMP_string * str);
void	iiimp_string_list_delete(IIIMP_data_s * data_s, IIIMP_string * str);
void	iiimp_feedback_attr_list_delete(IIIMP_data_s * data_s, IIIMP_feedback_attr_list * data);
void	iiimp_char_with_feedback_delete(IIIMP_data_s * data_s, IIIMP_char_with_feedback * cwf);
void	iiimp_char_with_feedback_list_delete(IIIMP_data_s * data_s, IIIMP_char_with_feedback * cwf);
void	iiimp_operation_delete(IIIMP_data_s * data_s, IIIMP_operation * op);
void	iiimp_operation_list_delete(IIIMP_data_s * data_s, IIIMP_operation * op);
void	iiimp_annotation_text_delete(IIIMP_data_s * data_s, IIIMP_annotation_value * anno_v);
void	iiimp_annotation_string_delete(IIIMP_data_s * data_s, IIIMP_annotation_value * anno_v);
void	iiimp_annotation_delete(IIIMP_data_s * data_s, IIIMP_annotation * anno);
void	iiimp_text_delete(IIIMP_data_s * data_s, IIIMP_text * text);
void	iiimp_text_list_delete(IIIMP_data_s * data_s, IIIMP_text * text);
void	iiimp_client_descriptor_delete(IIIMP_data_s * data_s, IIIMP_client_descriptor * cd);
void	iiimp_object_descriptor_delete(IIIMP_data_s * data_s, IIIMP_object_descriptor * od);
void	iiimp_object_descriptor_list_delete(IIIMP_data_s * data_s, IIIMP_object_descriptor * od);
void	iiimp_ccdef_delete(IIIMP_data_s * data_s, IIIMP_ccdef * ccdef);
void	iiimp_language_delete(IIIMP_data_s * data_s, IIIMP_language * language);
void	iiimp_language_list_delete(IIIMP_data_s * data_s, IIIMP_language * language);
void	iiimp_jarfile_object_delete(IIIMP_data_s * data_s, IIIMP_jarfile_object * jarfile);
void	iiimp_inputmethod_descriptor_delete(IIIMP_data_s * data_s, IIIMP_inputmethod_descriptor * im_desc);
void	iiimp_inputmethod_descriptor_list_delete(IIIMP_data_s * data_s, IIIMP_inputmethod_descriptor * im_desc);
void	iiimp_binaryfile_object_delete(IIIMP_data_s * data_s, IIIMP_binaryfile_object * bin_obj);
void	iiimp_imattribute_delete(IIIMP_data_s * data_s, IIIMP_imattribute * imattr);
void	iiimp_imattribute_list_delete(IIIMP_data_s * data_s, IIIMP_imattribute * imattr);
void	iiimp_icattribute_delete(IIIMP_data_s * data_s, IIIMP_icattribute * icattr);
void	iiimp_icattribute_list_delete(IIIMP_data_s * data_s, IIIMP_icattribute * icattr);
void	iiimp_keyevent_list_delete(IIIMP_data_s * data_s, IIIMP_keyevent_list * kel);
void	iiimp_contents_delete(IIIMP_data_s * data_s, IIIMP_contents * ptr);


/* IIIMP feedback attribute */

#define IIIMP_FEEDBACK_0_ID			(0)

#define IIIMP_FEEDBACK_0_NORMAL_VIDEO		(0)
#define IIIMP_FEEDBACK_0_REVERSE_VIDEO		(1)
#define IIIMP_FEEDBACK_0_UNDERLINE		(2)
#define IIIMP_FEEDBACK_0_HIGHLIGHT		(4)
#define IIIMP_FEEDBACK_0_PRIMARY		(8)
#define IIIMP_FEEDBACK_0_SECONDARY		(16)
#define IIIMP_FEEDBACK_0_TERTIARY		(32)


/* IIIMP annotation */

#define IIIMP_ANNOTATION_TEXT_INPUT_BEFORE_CONVERSION	(01)
#define IIIMP_ANNOTATION_READING_OF_THE_TEXT		(02)
#define IIIMP_ANNOTATION_TYPE_OF_SPEECH			(03)
#define IIIMP_ANNOTATION_TYPE_OF_CLAUSE			(04)


/* IIIMP contents */

#define IIIMP_CONTENTS_STRING	(0)
#define IIIMP_CONTENTS_TEXT	(1)
#define IIIMP_CONTENTS_KEYEVENT	(2)


/* IIIMP ic attribute */

#define IIIMP_ICATTRIBUTE_NONE			(0x00)
#define IIIMP_ICATTRIBUTE_INPUT_LANGUAGE	(0x01)
#define IIIMP_ICATTRIBUTE_CHARACTER_SUBSETS	(0x02)
#define IIIMP_ICATTRIBUTE_INPUT_METHOD_NAME	(0x03)
#define IIIMP_ICATTRIBUTE_INPUT_METHOD		(0x04)


/* IIIMP im attribute */

#define IIIMP_IMATTRIBUTE_NONE					(0x0000)
#define IIIMP_IMATTRIBUTE_INPUT_METHOD_LIST			(0x1001)
#define IIIMP_IMATTRIBUTE_OBJECT_DESCRIPTOR_LIST		(0x1010)
#define IIIMP_IMATTRIBUTE_CLIENT_DESCRIPTOR			(0x1011)
#define IIIMP_IMATTRIBUTE_CHARACTER_CONVERSION_DEFINITION_RULE	(0x1030)
#define IIIMP_IMATTRIBUTE_JAR_GUI_OBJECT			(0x1031)
#define IIIMP_IMATTRIBUTE_JAR_LIGHT_WEIGHT_ENGINE_OBJECT	(0x1032)
#define IIIMP_IMATTRIBUTE_BINARY_GUI_OBJECT			(0x1033)
#define IIIMP_IMATTRIBUTE_BINARY_LIGHT_WEIGHT_ENGINE_OBJECT	(0x1034)
#define IIIMP_IMATTRIBUTE_SCRIPT_GUI_OBJECT			(0x1035)
#define IIIMP_IMATTRIBUTE_SCRIPT_LIGHT_WEIGHT_ENGINE_OBJECT	(0x1036)


/* IIIMP IM_LOOKUP_CHOICE_START */

/* lookup choice master */
#define IM_LOOKUP_CHOICE_START_UNKNOWN_IS_MASTER	(0)
#define IM_LOOKUP_CHOICE_START_SERVER_IS_MASTER		(1)
#define IM_LOOKUP_CHOICE_START_CLIENT_IS_MASTER		(2)

/* lookup choice drawing direction */
#define IM_LOOKUP_CHOICE_START_DRAWING_UP_HORIZONTALLY	(0)
#define IM_LOOKUP_CHOICE_START_DRAWING_UP_VERTICALLY	(1)

/* lookup choice lavel owner */
#define IM_LOOKUP_CHOICE_START_SERVER_OWNS_LABEL	(0)
#define IM_LOOKUP_CHOICE_START_CLIENT_OWNS_LABEL	(1)


/* IIIMP IM_LOOKUP_CHOICE_PROCESS */

#define IM_LOOKUP_CHOICE_PROCESS_INDEX	(0)
#define IM_LOOKUP_CHOICE_PROCESS_PAGE	(1)

#define IM_LOOKUP_CHOICE_PROCESS_PAGE_NEXT_PAGE		(1)
#define IM_LOOKUP_CHOICE_PROCESS_PAGE_PREV_PAGE		(2)
#define IM_LOOKUP_CHOICE_PROCESS_PAGE_FIRST_PAGE	(3)
#define IM_LOOKUP_CHOICE_PROCESS_PAGE_LAST_PAGE		(4)


/* IIIMP IM_CONNECT */

#define IM_CONNECT_BIG_ENDIAN		(0x42)
#define IM_CONNECT_LITTLE_ENDIAN	(0x6c)


/* error status */

#define IIIMP_DATA_NO_ERROR	(0)
#define IIIMP_DATA_MALLOC_ERROR	(1)
#define IIIMP_DATA_INVALID	(2)


/* definition for debug */

#define	IIIMP_PRINT_NONE	(0x00000000)
#define	IIIMP_PRINT_QUERY	(0xffffffff)
#define	IIIMP_PRINT_JARFILE	(0x00000003)


#ifdef	__cplusplus
}
#endif

#endif /* !IIIMP_DATA_H */


/* Local Variables: */
/* c-file-style: "iiim-project" */
/* End: */
