/*	SCCS Id: @(#)macpopup.h	3.3	99/10/25	*/
/* Copyright (c) Nethack Develpment Team, 1999.		*/
/* NetHack may be freely redistributed.  See license for details. */

#ifndef MACPOPUP_H
# define MACPOPUP_H

/* ### mmodal.c ### */

extern void FlashButton(WindowPtr, short);
extern char queued_resp(char *resp);
extern char topl_yn_function(const char *query, const char *resp, char def);
extern int get_line_from_key_queue(char *bufp);

#define ENABLE_MAC_POPUP 0
#if ENABLE_MAC_POPUP

extern char popup_yn_function(const char *query, const char *resp, char def);
extern void popup_getlin (const char *query, char *bufp);

#endif /* ENABLE_MAC_POPUP */
#endif /* MACPOPUP_H */
