/**
 * chewing.c - Chewing Intelligent Chinese Phonetic Language Engine
 * for IIIMF.
 *
 * Copyright (c) 2004 Jim Huang <jserv@kaffe.org>
 * Copyright (c) 2003 Chia-Liang Kao <clkao@clkao.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA, or
 * contact the author.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <chewing/chewing.h>
#include <iconv.h>

#include <X11/Xmd.h>
#ifndef CARD32BIT
#define CARD32BIT CARD32
#endif

/*
 * header files for SunIM library
 */
#include "SunIM.h"

#define CHEWING_VERSION "0.0.2"

#ifdef DEBUG
#define DEBUG_printf    printf
#define DEBUG_fflush    fflush
#else
#define DEBUG_printf(s, ...)
#define DEBUG_fflush(fp)
#endif

static iconv_t iconv_context = (iconv_t) -1;

typedef struct chewing_session {
	ChewingData chewing_data;
	ChewingOutput chewing_output;
	int conv_on;
	int focus_on;

	int preedit_start;
#if 0
	int luc_start;
	int status_start;
	long fLastUpdateLength;
	int caret_pos;
	int candidate;
#endif
} chewing_session_t;

int get_session_caret_pos(iml_session_t *s)
{
	int pos = 0;
	if (s && s->specific_data) {
		chewing_session_t *session = 
			(chewing_session_t *)s->specific_data;
		pos = session->chewing_output.chiSymbolCursor;
		if (pos < 0 || pos > 100)
			pos = 0;
	}
	return pos;
}

IMFeedbackList *create_feedback(iml_session_t *s, int size)
{
	IMFeedbackList *feedback =
		(IMFeedbackList *) s->If->m->iml_new(
			s, 
			sizeof(IMFeedbackList) * size);
	memset(feedback, 0, sizeof(IMFeedbackList) * size);

	while (size-- > 0) {
		IMFeedbackList *fbl = &(feedback[size]);
		fbl->count_feedbacks = 4;
		fbl->feedbacks = 
			(IMFeedback *)s->If->m->iml_new(
				s, fbl->count_feedbacks*sizeof(IMFeedback));
		memset(
			fbl->feedbacks, 0, 
			fbl->count_feedbacks*sizeof(IMFeedback));

		IMFeedback *fb = &(fbl->feedbacks[0]);
		IM_FEEDBACK_TYPE(fb) = IM_DECORATION_FEEDBACK;
		IM_FEEDBACK_VALUE(fb) = IMUnderline;
	}

	return feedback;
}


UTFCHAR chewing_string[] = { 0x9177, 0x97f3, 0x0 };

void status_draw(iml_session_t *s)
{
	iml_inst *lp = NULL;
	iml_inst *rrv = NULL;

	if (s == NULL || s->specific_data == NULL)
		return;
	chewing_session_t *session = (chewing_session_t *) s->specific_data;
	if ( ! session->conv_on /* || !session->focus_on */) {
		lp = s->If->m->iml_make_status_done_inst(s);
		s->If->m->iml_execute(s, &lp);
		return;
	}

	lp = s->If->m->iml_make_status_start_inst(s);
	s->If->m->iml_link_inst_tail(&rrv, lp);

	IMText *p = (IMText *) s->If->m->iml_new(s, sizeof(IMText));
	memset(p, 0, sizeof(IMText));
	p->char_length = 2;
	p->encoding = UTF16_CODESET;
	p->text.utf_chars = chewing_string;
	p->feedback = create_feedback(s, p->char_length);

	lp = s->If->m->iml_make_status_draw_inst(s, p);
	s->If->m->iml_link_inst_tail(&rrv, lp);
	s->If->m->iml_execute(s, &rrv);
}

void commit(iml_session_t *s)
{
	int len, i, buflen;
	char buf[128], *bufp = buf, *bufutfp;
	iml_inst *lp;
	iml_inst *rrv = NULL;
	IMText *p;
	chewing_session_t *session = (chewing_session_t *)s->specific_data;
	ChewingOutput *op = &session->chewing_output;

	if (!op->nCommitStr)
		return;
	p = (IMText *) s->If->m->iml_new(s, sizeof(IMText));
	memset(p, 0, sizeof(IMText));
	p->encoding = UTF16_CODESET;

	memset (buf, 0, 128);
	for ( i = 0; i < op->nCommitStr; ++i ) {
		strcat (buf, op->commitStr[i].s);
	}

	len = strlen (buf) + 0;
	buflen = (op->nCommitStr + 1) * sizeof(UTFCHAR);

	p->text.utf_chars = (UTFCHAR *) s->If->m->iml_new(s, buflen);
	memset(p->text.utf_chars, 0, buflen);
	p->char_length = op->nCommitStr;

	bufutfp = (unsigned char *)p->text.utf_chars;
	iconv (iconv_context, (char **)&bufp, &len, &bufutfp, &buflen);

	if (session->preedit_start) {
		lp = s->If->m->iml_make_preedit_erase_inst(s);
		s->If->m->iml_link_inst_tail(&rrv, lp);
	}

	lp = s->If->m->iml_make_commit_inst(s, p);
	s->If->m->iml_link_inst_tail(&rrv, lp);
	s->If->m->iml_execute(s, &rrv);

	op->keystrokeRtn = KEYSTROKE_IGNORE;
	op->nCommitStr = 0;
}

static int currentKeyboard = KB_DEFAULT;

int does_preedit_contain_text(iml_session_t *s)
{
	chewing_session_t *session = (chewing_session_t *)s->specific_data;
	ChewingOutput *op = &session->chewing_output;

	int i, len=0;
	for (i = 0; (len == 0) && (i < op->chiSymbolCursor); ++i)
		if (op->chiSymbolBuf[i].s[0])
			len = 1;
	for (i = 0; (len == 0) && (i < ZUIN_SIZE); ++i)
		if (op->zuinBuf[i].s[0])
			len = 1;
	for (i = op->chiSymbolCursor; 
			(len == 0) && (i < op->chiSymbolBufLen); ++i)
		if (op->chiSymbolBuf[i].s[0])
			len = 1;
	return len;
}

IMText *make_preedit_imtext(iml_session_t *s)
{
	int len, i, zuinlen = 0, buflen;
	char buf[128], *bufp = buf, *bufutfp;
	chewing_session_t *session = (chewing_session_t *)s->specific_data;
	ChewingOutput *op = &session->chewing_output;

	memset (buf, 0, 128);
	IMText *p = (IMText *) s->If->m->iml_new(s, sizeof(IMText));
	memset(p, 0, sizeof(IMText));

	for (i = 0; i < op->chiSymbolCursor; ++i)
		strcat (buf, op->chiSymbolBuf[i].s);
	len = strlen(buf);

	for (i = 0; i < ZUIN_SIZE; ++i) {
		strcat(buf, op->zuinBuf[i].s);
	}
	zuinlen = (strlen(buf) - len) / 2;
	for (i = op->chiSymbolCursor; i < op->chiSymbolBufLen; ++i)
		strcat (buf, op->chiSymbolBuf[i].s);
	len = strlen (buf) + 1;
	p->encoding = UTF16_CODESET;

	p->char_length = op->chiSymbolBufLen + zuinlen;
	buflen = (p->char_length + 1) * sizeof(UTFCHAR);
	p->text.utf_chars = (UTFCHAR *) s->If->m->iml_new(s, buflen);
	memset(p->text.utf_chars, 0, buflen);

	DEBUG_printf("Big5 text is %s\n", buf);
	DEBUG_printf(
		"drawing preedit (charlen = %d, big5_bytes_len = %d)\n", 
		p->char_length, len - 1);

	bufutfp = (char *) p->text.utf_chars;
	iconv(iconv_context, (char **) &bufp, &len, &bufutfp, &buflen);

	p->feedback = create_feedback(s, p->char_length);
	return p;
}

void init_session_context(iml_session_t *s)
{
	int i;
	ChewingConf cf ;
	ConfigData config;
	chewing_session_t *session = (chewing_session_t*)s->specific_data;

	if (session == NULL)
		session = calloc (sizeof (chewing_session_t), 1);
	else
		memset(session, 0, sizeof(chewing_session_t)); 
	/* Indeed we should free session entirely and realloc an new one */

	/* init chewing core */
	cf.kb_type = KB_DEFAULT;
	InitChewing(&session->chewing_data, &cf) ;

	config.selectAreaLen = 40;
	config.maxChiSymbolLen = 16;
	for (i = 0; i < 9; i++)
		config.selKey[i] = i + '1';
	config.selKey[9] = '0';
	SetConfig(&session->chewing_data, &config);

	MakeOutput(&session->chewing_output, &session->chewing_data);

	s->specific_data = (void*) session;
}

void open_preedit(iml_session_t *s)
{
	iml_inst *lp = NULL;
	chewing_session_t *session = (chewing_session_t*)s->specific_data;
	if (! session->preedit_start) {
		lp = s->If->m->iml_make_preedit_start_inst(s);
		s->If->m->iml_execute(s, &lp);
	}
	session->preedit_start = True;
}

void close_preedit(iml_session_t *s)
{
	iml_inst *lp=NULL, *rrv = NULL;
	chewing_session_t *session = (chewing_session_t*) s->specific_data;
	if (session->preedit_start) {
		lp = s->If->m->iml_make_preedit_erase_inst(s);
		s->If->m->iml_link_inst_tail(&rrv, lp);
		lp = s->If->m->iml_make_preedit_done_inst(s);
		s->If->m->iml_link_inst_tail(&rrv, lp);
		s->If->m->iml_execute(s, &rrv);
	}
	session->preedit_start = False;
}

void preedit_draw(iml_session_t *s)
{
	IMText *p = NULL;
	iml_inst *lp=NULL, *rrv = NULL;

	if (!does_preedit_contain_text(s)) {
		close_preedit(s);
		return;
	}

	open_preedit(s);
	p = make_preedit_imtext(s);
	lp = s->If->m->iml_make_preedit_draw_inst(s, p);
	s->If->m->iml_link_inst_tail(&rrv, lp);
	lp = s->If->m->iml_make_preedit_caret_inst(s, get_session_caret_pos(s));
	s->If->m->iml_link_inst_tail(&rrv, lp);
	s->If->m->iml_execute(s, &rrv);
}

void open_candidate(iml_session_t *s)
{
	chewing_session_t *session = (chewing_session_t *)s->specific_data;

	//   if (!session->luc_start) {
	ChoiceInfo *pci = session->chewing_output.pci;
	IMLookupStartCallbackStruct *start = 
		(IMLookupStartCallbackStruct *)s->If->m->iml_new(
			s, sizeof(IMLookupStartCallbackStruct));
	memset(start, 0, sizeof(IMLookupStartCallbackStruct));
	start->whoIsMaster = IMIsMaster;
	start->IMPreference = (LayoutInfo *) s->If->m->iml_new(s, sizeof(LayoutInfo));
	memset(start->IMPreference, 0, sizeof(LayoutInfo));
	start->IMPreference->choice_per_window = pci->nChoicePerPage;
	start->IMPreference->ncolumns = pci->nChoicePerPage;
	start->IMPreference->nrows = 1;
	start->IMPreference->drawUpDirection = DrawUpHorizontally;
	start->IMPreference->whoOwnsLabel = IMOwnsLabel;
	start->CBPreference = NULL;
	iml_inst *lp = s->If->m->iml_make_lookup_start_inst(s, start);
	s->If->m->iml_execute(s, &lp);
	//    }
	//    session->luc_start = True;
}

void close_candidate(iml_session_t *s)
{
	//chewing_session_t *session = (chewing_session_t *)s->specific_data;

	//    if (session->luc_start) {
	iml_inst *lp = s->If->m->iml_make_lookup_done_inst(s);
	s->If->m->iml_execute(s, &lp);
	//    }
	//    session->luc_start = False;
}

void draw_candidate(iml_session_t *s)
{
	iml_inst *lp=NULL;
	chewing_session_t *session = (chewing_session_t *)s->specific_data;
	ChewingOutput *op = &session->chewing_output;
	IMLookupDrawCallbackStruct *draw;
	ChoiceInfo *pci = op->pci;
	int i, fc = pci->pageNo * pci->nChoicePerPage;

	open_candidate(s);

	draw = (IMLookupDrawCallbackStruct *)
		s->If->m->iml_new(s, sizeof(IMLookupDrawCallbackStruct));
	memset(draw, 0, sizeof(IMLookupDrawCallbackStruct));
	draw->n_choices = pci->nTotalChoice - fc;
	if (draw->n_choices > pci->nChoicePerPage) 
		draw->n_choices = pci->nChoicePerPage;
	draw->index_of_current_candidate = draw->index_of_first_candidate = 0;
	draw->index_of_last_candidate = 
		draw->index_of_first_candidate + draw->n_choices - 1;
	draw->title = NULL;

	draw->title = (IMText *) s->If->m->iml_new(s, sizeof(IMText));
	memset(draw->title, 0, sizeof(IMText));
	draw->title->encoding = UTF16_CODESET;
	draw->title->char_length = 2;
	draw->title->text.utf_chars = 
		(UTFCHAR *) s->If->m->iml_new(
			s, 
			sizeof(IMText) * (draw->title->char_length + 1));
	memset(
		draw->title->text.utf_chars, 0, 
		sizeof(IMText) * (draw->title->char_length + 1));
	memcpy (
		draw->title->text.utf_chars, chewing_string, 
		(draw->title->char_length + 1) * sizeof(UTFCHAR));
	draw->title->feedback = create_feedback(s, draw->title->char_length);

	DEBUG_printf(
		"%d of %d choices, starting at %d\n", 
		draw->n_choices, 
		draw->n_choices, 
		draw->index_of_first_candidate);

	IMText **candidates = NULL, **labels=NULL;
	candidates = 
		(IMText **) s->If->m->iml_new(
			s, 
			draw->n_choices * sizeof(IMText *));
	memset(candidates, 0, draw->n_choices * sizeof(IMText *));
	for (i = 0; i < draw->n_choices; ++i) {
		int buflen = 0, len = 0;
		char *bufutfp = NULL;
		char *bufp = pci->totalChoiceStr[fc+i];
		DEBUG_printf("        --%d. %s\n", i+1, bufp); 
		DEBUG_fflush(stdout);

		IMText *vt = candidates[i] = 
			(IMText *)s->If->m->iml_new(s, sizeof(IMText));
		memset(vt, 0, sizeof(IMText));

		vt->encoding = UTF16_CODESET;
		len = (bufp)?(strlen(bufp)):0; 
		vt->char_length = len / 2;
		buflen = (vt->char_length + 1) * sizeof(UTFCHAR);
		vt->text.utf_chars = (UTFCHAR *)s->If->m->iml_new(s, buflen);
		memset(vt->text.utf_chars, 0, buflen);
		bufutfp = (char *)vt->text.utf_chars;
		iconv(iconv_context, (char **)&bufp, &len, &bufutfp, &buflen);
		vt->text.utf_chars[vt->char_length] = 0;
		vt->feedback = create_feedback(s, vt->char_length);
	}

	labels = (IMText **) s->If->m->iml_new(
		s, 
		draw->n_choices * sizeof(IMText *));
	memset(labels, 0, draw->n_choices * sizeof(IMText *));
	for (i = 0; i < draw->n_choices; ++i) {
		IMText *lt = labels[i] = 
			(IMText *)s->If->m->iml_new(s, sizeof(IMText));
		memset(lt, 0, sizeof(IMText));
		lt->encoding = UTF16_CODESET;
		lt->char_length = 1;
		lt->text.utf_chars = 
			(UTFCHAR *) s->If->m->iml_new(s, 2*sizeof(UTFCHAR));
		lt->text.utf_chars[0] = (UTFCHAR)(i+'1');
		lt->text.utf_chars[1] = (UTFCHAR)0;
		lt->feedback = create_feedback(s, lt->char_length);
	}

	draw->choices = (IMChoiceObject *) s->If->m->iml_new(
		s, 
		draw->n_choices * sizeof(IMChoiceObject));
	memset(draw->choices, 0, draw->n_choices * sizeof(IMChoiceObject));
	for (i = draw->max_len = 0; i < draw->n_choices; i++) {
		draw->choices[i].value = candidates[i];
		if (draw->choices[i].value->char_length > draw->max_len)
			draw->max_len = draw->choices[i].value->char_length;
		draw->choices[i].label = labels[i];
	}
	lp = s->If->m->iml_make_lookup_draw_inst(s, draw);
	s->If->m->iml_execute(s, &lp);
}

void handle_candidate(iml_session_t *s)
{
	if (s) {
		chewing_session_t *session = 
			(chewing_session_t *) s->specific_data;

		if (
			session && 
			(session->chewing_output.pci != NULL) && 
			(session->chewing_output.pci->nTotalChoice > 0)) {
			draw_candidate(s);
		} else {
			close_candidate (s);
		}
	}
}

void chewing_conversion_on(iml_session_t *s)
{
	if (s == NULL || s->specific_data == NULL) 
		return;

	chewing_session_t *session = (chewing_session_t *)s->specific_data;
	iml_inst *lp = s->If->m->iml_make_start_conversion_inst(s);
	s->If->m->iml_execute(s, &lp);

	session->conv_on = True;
	status_draw(s);
}

void chewing_conversion_off (iml_session_t *s)
{
	if (s == NULL || s->specific_data == NULL)
		return;

	close_candidate(s);
	close_preedit(s);
	init_session_context(s);

	iml_inst *lp = s->If->m->iml_make_end_conversion_inst(s);
	s->If->m->iml_execute(s, &lp);

	chewing_session_t *session = (chewing_session_t *)s->specific_data;
	session->conv_on = False;
	status_draw(s);
}

/* IF method implementation */

Bool if_chewing_OpenIF(iml_if_t *If)
{
	/* fix the data installation path and put it here */
	char *prefix = CHEWING_DATADIR;

	iconv_context = iconv_open("UTF-16LE", "BIG5");
	DEBUG_printf(
		"  ====> Chewing opening, iconv handle is %d ...", 
		(int) iconv_context);

	ReadTree(prefix);
	InitChar(prefix);
	InitDict(prefix);
	ReadHash(prefix);

	DEBUG_printf(" done\n");
	return True;
}

/* FIX_NEEDED! Memory Leak! But not serious */
Bool if_chewing_CloseIF(iml_if_t *If)
{
	DEBUG_printf("  ====> Chewing closing...");
	iconv_close(iconv_context);
	DEBUG_printf(" done\n");
	return True;
}

Bool if_chewing_GetIFValues(iml_if_t *If, IMArgList args, int num_args)
{
	return True;
}

Bool if_chewing_SetIFValues(iml_if_t *If, IMArgList args, int num_args)
{
	return True;
}

Bool if_chewing_OpenDesktop(
		iml_desktop_t *desktop, 
		IMArgList args, 
		int num_args)
{
	DEBUG_printf("  ====> Chewing open desktop...done!\n"); 
	DEBUG_fflush(stdout);
	return True;
}

Bool if_chewing_CloseDesktop(iml_desktop_t *desktop)
{
	DEBUG_printf("  ====> Chewing close desktop...done!\n"); 
	DEBUG_fflush(stdout);
	return True;
}

Bool if_chewing_CreateSC(iml_session_t *s, IMArgList args, int num_args)
{
	DEBUG_printf("  ====> Chewing create session..."); 
	DEBUG_fflush(stdout);

	s->specific_data = NULL;
	init_session_context(s);

	DEBUG_printf(
		"created session data %x, done!\n", 
		(unsigned int) s->specific_data); 
	DEBUG_fflush(stdout);
	return True;
}

Bool if_chewing_DestroySC(iml_session_t *s)
{
	DEBUG_printf("  ====> Chewing destroy session..."); 
	DEBUG_fflush(stdout);

	if (s->specific_data != NULL) {
		close_candidate(s);
		close_preedit(s);
		init_session_context(s);
		free(s->specific_data);
		s->specific_data = NULL;
	}
	DEBUG_printf("  done\n"); 
	DEBUG_fflush(stdout);
	return True;
}

Bool if_chewing_GetSCValues(iml_session_t *s, IMArgList args, int num_args)
{
	int i;
	IMArg *p = args;

	for (i = 0; i < num_args; i++, p++) {
		switch (p->id) {
			default:
				break;
		}
	}
	return True;
}

Bool if_chewing_SetSCValues (iml_session_t *s, IMArgList args, int num_args)
{
	int i;
	IMArg *p = args;
	for (i = 0; i < num_args; i++, p++) {
		switch (p->id) {
			case SC_TRIGGER_ON_NOTIFY:
				DEBUG_printf(
				"  ====> Chewing SC_TRIGGER_ON_NOTIFY \n");
				chewing_conversion_on(s);
				break;
			case SC_TRIGGER_OFF_NOTIFY:
				DEBUG_printf(
				"  ====> Chewing SC_TRIGGER_OFF_NOTIFY \n");
				chewing_conversion_off(s);
				break;
			case SC_REALIZE:
				if (s->desktop->session_count == 1) {
					DEBUG_printf(
					"  ====> Chewing SC_REALIZE: "
					"just after OpenDesktop\n");
				} else {
					DEBUG_printf(
					"  ====> Chewing SC_REALIZE: "
					"received\n");
				}
				break;
			default:
				break;
		}
	}
	return True;
}

IMText *if_chewing_ResetSC(iml_session_t *s)
{
	close_candidate(s);
	close_preedit(s);
	init_session_context(s);
	return (IMText *) NULL;
}

void if_chewing_SetSCFocus(iml_session_t *s)
{
	if (s == NULL || s->specific_data == NULL)
		return;

	DEBUG_printf("  ====> Chewing set focus..."); 
	DEBUG_fflush(stdout);

	chewing_session_t *session = (chewing_session_t *) s->specific_data;
	session->focus_on = True;

	status_draw(s);
	preedit_draw(s);
	handle_candidate(s);
	DEBUG_printf("  done\n"); 
	DEBUG_fflush(stdout);
}

void if_chewing_UnsetSCFocus(iml_session_t *s)
{
	if (s == NULL || s->specific_data == NULL)
		return;

	DEBUG_printf("  ====> Chewing lose focus..."); 
	DEBUG_fflush(stdout);

	chewing_session_t *session = (chewing_session_t *) s->specific_data;
	session->focus_on = False;

	//status_draw(s);
	close_candidate(s);
	//close_preedit(s);
	DEBUG_printf("  done\n"); 
	DEBUG_fflush(stdout);
}

void if_chewing_SendEvent(iml_session_t *s, IMInputEvent *ev)
{
	chewing_session_t *session = (chewing_session_t *) s->specific_data;
	ChewingOutput *op = &session->chewing_output;
	ChewingData *pgdata = &session->chewing_data;
	IMKeyListEvent *keylistevent;
	IMKeyEventStruct *key;

	if (ev->type != IM_EventKeyList) 
		return;

	keylistevent = (IMKeyListEvent *) ev;
	key = (IMKeyEventStruct *) keylistevent->keylist;
	DEBUG_printf(
		"  ====> Chewing processing key (0X%X - 0X%X - 0X%X) ...\n", 
		key->keyCode, key->keyChar, key->modifier); 
	DEBUG_fflush(stdout);

	if ( (key->modifier & (IM_SHIFT_MASK | IM_CTRL_MASK | IM_ALT_MASK)) == IM_CTRL_MASK &&
			key->keyChar == ' ' && session->conv_on ) {
		chewing_conversion_off(s);
		return;        
	}
	if (!session->conv_on) {
		iml_inst *lp;
		lp = s->If->m->iml_make_keypress_inst(s, key);
		s->If->m->iml_execute(s, &lp);
		return;
	}

	op->keystrokeRtn = KEYSTROKE_IGNORE;
	pgdata->zuinData.kbtype = currentKeyboard;
	switch (key->keyCode) {
		case IM_VK_CAPS_LOCK:
			OnKeyCapslock(pgdata, op);
			break;

		case IM_VK_ENTER:
			OnKeyEnter(pgdata, op);
			break;

		case IM_VK_ESCAPE:
			OnKeyEsc(pgdata, op) ;
			break;

		case IM_VK_BACK_SPACE:
			OnKeyBackspace(pgdata, op);
			break;

		case IM_VK_LEFT:
			OnKeyLeft(pgdata, op);
			break;

		case IM_VK_RIGHT:
			OnKeyRight(pgdata, op);
			break;

		case IM_VK_UP:
			OnKeyUp(pgdata, op);
			break;

		case IM_VK_DOWN:
			OnKeyDown(pgdata, op);
			break;

		case IM_VK_SPACE:
			OnKeySpace(pgdata, op);
			break;

		case IM_VK_HOME:
			OnKeyHome(pgdata, op);
			break;

		case IM_VK_END:
			OnKeyEnd(pgdata, op);
			break;

		case IM_VK_PAGE_UP:
		case IM_VK_PAGE_DOWN:
			break;

		case IM_VK_TAB:
			OnKeyTab(pgdata, op);
			break;

		default:
#if 0
			if ((key->modifier & (controlKey|rightControlKey)) && 
					(inCharCode > '0' && 
					 inCharCode < '9'))
			   OnKeyCtrlNum(pgdata, inCharCode, op);

			   else if (inCharCode) {
			   	if (modifiers & alphaLock && 
						!(modifiers & shiftKey))
			   inCharCode |= 32;
#endif
			if (key->keyChar && (key->modifier & (IM_CTRL_MASK | IM_ALT_MASK)) == 0)
				OnKeyDefault(pgdata, key->keyChar, op);
			break;
	}

	DEBUG_printf("        ---->return bitmask 0x%x\n", op->keystrokeRtn); 
	DEBUG_fflush(stdout);
	if (op->keystrokeRtn & KEYSTROKE_COMMIT) {
		DEBUG_printf("    ---->commiting...\n");
		commit(s);
	}
	DEBUG_printf("        ---->update preedit...\n"); 
	DEBUG_fflush(stdout);
	preedit_draw(s);
	DEBUG_printf("        ---->handle candidate...\n"); 
	DEBUG_fflush(stdout);
	handle_candidate(s);
	DEBUG_printf("done!"); 
	DEBUG_fflush(stdout);

	/* is there any way to bell on the client? */
	/*
	   if (op->keystrokeRtn & KEYSTROKE_BELL)
	   SysBeep();
	   */

	if (op->keystrokeRtn & KEYSTROKE_IGNORE) {
		iml_inst *lp;
		lp = s->If->m->iml_make_keypress_inst(s, key);
		s->If->m->iml_execute(s, &lp);
	}

	return;
}

/* IF Method */
static if_methods_t chewing_methods = {
	if_chewing_OpenIF,
	if_chewing_CloseIF,
	if_chewing_GetIFValues,
	if_chewing_SetIFValues,
	if_chewing_OpenDesktop,
	if_chewing_CloseDesktop,
	if_chewing_CreateSC,
	if_chewing_DestroySC,
	if_chewing_GetSCValues,
	if_chewing_SetSCValues,
	if_chewing_ResetSC,
	if_chewing_SetSCFocus,
	if_chewing_UnsetSCFocus,
	if_chewing_SendEvent
};

/* 酷音輸入法 */
UTFCHAR lename_string[] = {
	0x9177, 0x97f3, 0x8f38, 0x5165, 0x6cd5, 0x0
};

static IMLEName lename = {
	"chewing", (UTFCHAR *) lename_string
};

/* 繁體中文 */
UTFCHAR locale_string[] = {
	0x7e41, 0x9ad4, 0x4e2d, 0x6587, 0x0
};
static IMLocale locales[] = {
	{ "zh_TW", (UTFCHAR *) locale_string },
	{ NULL, NULL }
};

void if_GetIfInfo (IMArgList args, int num_args)
{
	int i;

	for (i = 0; i < num_args; i++, args++) {
		switch (args->id) {
			case IF_VERSION:
				args->value = (IMArgVal) CHEWING_VERSION;
				break;
			case IF_METHOD_TABLE:
				args->value = (IMArgVal) & chewing_methods;
				break;
			case IF_LE_NAME:
				args->value = (IMArgVal) & lename;
				break;
			case IF_SUPPORTED_LOCALES:
				args->value = (IMArgVal) & locales;
				break;
			case IF_SUPPORTED_OBJECTS:
				break;
			case IF_NEED_THREAD_LOCK:
				args->value = (IMArgVal) True;
				break;
			default:
				break;
		}
	}
}

