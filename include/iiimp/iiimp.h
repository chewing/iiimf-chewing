#if !defined(IIIMP_H)
#define IIIMP_H

/* $Id: iiimp.h,v 1.1.1.1 2003/12/10 04:42:54 llch Exp $ */


#include <sys/types.h>

#include <iiimp-opcode.h>
#include <iiimp-data.h>
#include <iiimp-keycode.h>


#ifdef	__cplusplus
extern "C" {
#endif


/*
 * IIIMF public type
 */

typedef struct iiimf_im		IIIMF_im;
typedef struct iiimf_ic		IIIMF_ic;

typedef enum {
	IIIMF_ROLE_CLIENT	= 1,
	IIIMF_ROLE_SERVER	= 0
} IIIMF_role;

typedef enum {
	IIIMF_MESSAGE_HANDLER_STATUS_ERROR	= -1,
	IIIMF_MESSAGE_HANDLER_STATUS_NORMAL	= 0,
	IIIMF_MESSAGE_HANDLER_STATUS_STOP	= 1
} IIIMF_message_handler_status;

typedef struct iiimf_message_handler_entry IIIMF_message_handler_entry;


/* general return status */

typedef enum {
	IIIMF_STATUS_FAIL			= -1,
	IIIMF_STATUS_SUCCESS			= 0,

	IIIMF_STATUS_MALLOC			= 11,
	IIIMF_STATUS_ARGUMENT			= 12,
	IIIMF_STATUS_PROTOCOL_VERSION		= 13,

	IIIMF_STATUS_CONFIG			= 51,
	IIIMF_STATUS_ROLE			= 52,

	IIIMF_STATUS_OPCODE			= 101,

	IIIMF_STATUS_SEQUENCE_REQUEST		= 201,
	IIIMF_STATUS_SEQUENCE_REPLY		= 202,
	IIIMF_STATUS_SEQUENCE_ROLE		= 203,
	IIIMF_STATUS_SEQUENCE_STATE		= 204,
	IIIMF_STATUS_SEQUENCE_NEST		= 205,

	IIIMF_STATUS_IM_INVALID			= 501,
	IIIMF_STATUS_IC_INVALID			= 502,

	IIIMF_STATUS_STREAM			= 1001,
	IIIMF_STATUS_STREAM_SEND		= 1002,
	IIIMF_STATUS_STREAM_RECEIVE		= 1003,
	IIIMF_STATUS_PACKET			= 1004,
	IIIMF_STATUS_INVALID_ID			= 1005,
	IIIMF_STATUS_TIMEOUT			= 1006,
	IIIMF_STATUS_CONNECTION_CLOSED          = 2001,

	IIIMF_STATUS_IIIMCF_START		= 10000,
	IIIMF_STATUS_NO_ATTR_VALUE		= 10001,
	IIIMF_STATUS_NO_TEXT_PROPERTY		= 10002,
	IIIMF_STATUS_NO_EVENT			= 10003,
	IIIMF_STATUS_NO_PREEDIT			= 10004,
	IIIMF_STATUS_NO_LOOKUP_CHOICE		= 10005,
	IIIMF_STATUS_NO_STATUS_TEXT		= 10006,
	IIIMF_STATUS_NO_COMMITTED_TEXT		= 10007,
	IIIMF_STATUS_CLIENT_RESET_BY_PEER	= 10008,
	IIIMF_STATUS_INVALID_EVENT_TYPE		= 10009,
	IIIMF_STATUS_EVENT_NOT_FORWARDED	= 10010,
	IIIMF_STATUS_COMPONENT_DUPLICATED_NAME	= 10011,
	IIIMF_STATUS_COMPONENT_FAIL		= 10012,
	IIIMF_STATUS_NO_COMPONENT		= 10013,
	IIIMF_STATUS_STATIC_EVENT_FLOW		= 10014,
	IIIMF_STATUS_FAIL_TO_EVENT_DISPATCH	= 10015,
	IIIMF_STATUS_NO_AUX			= 10016,
	IIIMF_STATUS_NOT_TRIGGER_KEY		= 10017,
	IIIMF_STATUS_COMPONENT_INDIFFERENT	= 10018
} IIIMF_status;


/*
 * The structure iiimf_stream_proc_data shall be defined by the
 * implementor of stream procedures.
 */
typedef struct iiimf_stream_proc_data	IIIMF_stream_proc_data;

typedef struct IIIMF_stream IIIMF_stream;
typedef void* IIIMF_stream_private;

typedef IIIMF_status	(* IIIMF_stream_proc_read)(
					IIIMF_stream_private		private_data,
					void *				buf,
					size_t				nbyte);

typedef IIIMF_status	(* IIIMF_stream_proc_write)(
					IIIMF_stream_private		private_data,
					const void *			buf,
					size_t				nbyte);

typedef IIIMF_status	(* IIIMF_message_handler_call_func)(
						IIIMF_im *	im,
						IIIMP_message *	message);

typedef IIIMF_message_handler_status	(* IIIMF_message_handler)(
						IIIMF_im *	im,
						IIIMF_ic *	ic,
						IIIMP_message *	m);

typedef enum {
	IIIMF_MESSAGE_HANDLER_REGISTER_PLACE_HEAD = 0,
	IIIMF_MESSAGE_HANDLER_REGISTER_PLACE_TAIL = 1,
	IIIMF_MESSAGE_HANDLER_REGISTER_PLACE_BEFORE = 2,
	IIIMF_MESSAGE_HANDLER_REGISTER_PLACE_AFTER = 3
} IIIMF_message_handler_register_place;


/* miscellaneous function */

extern void		iiimf_perror(IIIMF_status status, const char * str);

/* stream */

extern IIIMF_status	iiimf_create_stream(IIIMF_stream_proc_read	proc_read,
					    IIIMF_stream_proc_write	proc_write,
					    IIIMF_stream_private	priv_data,
					    int 			timeout,
					    IIIMF_stream **		stream_ret);

extern void     	iiimf_stream_delete(IIIMF_stream *	stream);

extern IIIMF_status	iiimf_stream_send(IIIMF_stream *	stream,
					  IIIMP_data_s *	data_s,
					  IIIMP_message *	message);

extern IIIMF_status	iiimf_stream_receive(IIIMF_stream *	stream,
					     IIIMP_data_s *	data_s,
					     IIIMP_message **	message);

/* stream by socket */
extern IIIMF_status     iiimf_connect_socket_stream(const char *	node,
						    const char *	service,
						    int                 timeout,
						    IIIMF_stream ** stream_ret);

extern IIIMF_status	iiimf_listen_socket_stream(const char *	node,
						   const char *	service,
						   int                 timeout,
						   IIIMF_stream ** stream_ret);

extern IIIMF_status	iiimf_accept_socket_stream(IIIMF_stream *  stream,
						   IIIMF_stream ** stream_ret);

extern IIIMF_status	iiimf_delete_socket_stream(IIIMF_stream *  stream);

/* request send and receive */

extern IIIMF_status	iiimf_request_send(IIIMF_im *		im,
					   IIIMF_ic *		ic,
					   IIIMP_message *	message);

extern IIIMF_status	iiimf_request_loop(IIIMF_im * im);

extern IIIMF_status	iiimf_request_reply(IIIMF_im *		im,
					    IIIMF_ic *		ic,
					    IIIMP_message *	message);


/* IIIMF_im data */

extern IIIMF_status	iiimf_im_new(IIIMF_role		role,
				     const char *	server_node,
				     const char *	service,
				     void *		client_data,
				     IIIMF_im **	im_ret);

extern void		iiimf_im_delete(IIIMF_im * im);

extern IIIMP_data_s *	iiimf_im_data_s(IIIMF_im * im);

extern void *		iiimf_im_data_get(IIIMF_im * im);

extern void *		iiimf_im_data_set(IIIMF_im * im, void * data);

extern IIIMF_status	iiimf_im_fd_set(IIIMF_im * im, int fd);

extern IIIMF_status	iiimf_im_timeout_set(IIIMF_im * im, int fd);

extern IIIMF_status	iiimf_im_start(IIIMF_im * im);

extern IIIMF_status	iiimf_im_end(IIIMF_im * im);

extern IIIMF_status	iiimf_im_server_accept(IIIMF_im *	im,
					       void *		client_data,
					       IIIMF_im **	im_ret);

extern IIIMF_status	iiimf_im_client_type_set(
				IIIMF_im *	im,
				const char *	type);

extern IIIMF_status	iiimf_im_user_set(
				IIIMF_im *	im,
				const char *	username,
				const char *	password);

extern int		iiimf_im_id(IIIMF_im * im);


/* IIIMF_ic data */

extern IIIMF_status	iiimf_ic_new(IIIMF_im *		im,
				     void *		client_data,
				     IIIMF_ic **	ic_ret);

extern void		iiimf_ic_delete(IIIMF_ic * ic);

extern IIIMF_status	iiimf_ic_id_set(IIIMF_ic *	ic,
					int		ic_id);

extern void *		iiimf_ic_data_get(IIIMF_ic * ic);

extern void *		iiimf_ic_data_set(IIIMF_ic * ic, void * data);

extern IIIMF_status	iiimf_ic_langauage_set(IIIMF_ic *	ic,
					       const char *	language);

extern IIIMF_status	iiimf_ic_input_method_set(IIIMF_ic *	ic,
						  const char *	input_method);

extern IIIMF_status	iiimf_ic_preedit_maximum_length_set(
					IIIMF_ic *	ic,
					int		preedit_maximum_length);

extern int		iiimf_ic_id(IIIMF_ic * ic);


/* role data */

extern const char *	iiimf_role_data_client_user_name(IIIMF_im * im);

extern const char *	iiimf_role_data_client_home_dir(IIIMF_im * im);

extern const char *	iiimf_role_data_client_node(IIIMF_im * im);

extern const char *	iiimf_role_data_client_server_node(IIIMF_im * im);

extern const char *	iiimf_role_data_client_service(IIIMF_im * im);

extern IIIMF_status	iiimf_role_data_client_auth_password(
				IIIMF_im *	im,
				char **		password_ret);


/* message handler */

extern IIIMF_status	iiimf_message_handler_register(
				IIIMF_im *				im,
				int					opcode,
				IIIMF_message_handler			handler,
				const char *				name,
				IIIMF_message_handler_register_place	place,
				const char *				anchor);

extern IIIMF_status	iiimf_message_handler_unregister(
				IIIMF_im *		im,
				int			opcode,
				IIIMF_message_handler	handler);

extern IIIMF_status	iiimf_message_handler_unregister_name(
				IIIMF_im *		im,
				const char *		name);


/* data utility */
extern IIIMF_status	iiimf_data_string_ascii_new(IIIMP_data_s *	data_s,
						    const char *	ptr,
						    IIIMP_string **	ret);

extern IIIMF_status	iiimf_data_im_connect(IIIMF_im *	im,
					      IIIMP_message **	message_ret);

extern IIIMF_status	iiimf_data_client_descriptor(
				IIIMF_im *			im,
				IIIMP_client_descriptor **	data_ret);


#ifdef	__cplusplus
}
#endif

#endif /* !IIIMP_H */
