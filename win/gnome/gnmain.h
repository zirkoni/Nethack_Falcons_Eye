/*	SCCS Id: @(#)gnmain.h	3.3	2000/07/16	*/
/* Copyright (C) 1998 by Erik Andersen <andersee@debian.org> */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef GnomeHackMainWindow_h
#define GnomeHackMainWindow_h

#include <gnome.h>
#include <gtk/gtk.h>


void ghack_init_main_window( int argc, char** argv);
void ghack_main_window_add_map_window(GtkWidget* win);
void ghack_main_window_add_message_window(GtkWidget* win);
void ghack_main_window_add_status_window(GtkWidget* win);
void ghack_main_window_add_text_window(GtkWidget *);
void ghack_main_window_remove_window(GtkWidget *);
void ghack_main_window_update_inventory();
void ghack_save_game_cb(GtkWidget *widget, gpointer data);
GtkWidget* ghack_get_main_window();



#endif /* GnomeHackMainWindow_h */

