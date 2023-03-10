/*	SCCS Id: @(#)gnaskstr.h	3.3	2000/07/16	*/
/* Copyright (C) 1998 by Erik Andersen <andersee@debian.org> */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef GnomeHackAskStringDialog_h
#define GnomeHackAskStringDialog_h


int ghack_ask_string_dialog(const char *szMessageStr,
        const char *szDefaultStr, const char *szTitleStr,
        char *buffer);

#endif /* GnomeHackAskStringDialog_h */

