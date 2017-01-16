#ifndef WMCTRL_H_INCLUDED
#define WMCTRL_H_INCLUDED
/* 

wmctrl
A command line tool to interact with an EWMH/NetWM compatible X Window Manager.

Author, current maintainer: Tomas Styblo <tripie@cpan.org>

Copyright (C) 2003

This program is free software which I release under the GNU General Public
License. You may redistribute and/or modify this program under the terms
of that license as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

To get a copy of the GNU General Puplic License,  write to the
Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include <stdbool.h>
#include <X11/Xlib.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif				/* __cplusplus */

  int client_msg (Display * disp, Window win, char *msg,
		  unsigned long data0, unsigned long data1,
		  unsigned long data2, unsigned long data3,
		  unsigned long data4);
  int get_number_of_desktops (Display * disp);
  int change_number_of_desktops (Display * disp, unsigned long n);
  int switch_desktop (Display * disp, unsigned long target);
  int window_to_desktop (Display * disp, Window win, int desktop);
  int activate_window (Display * disp, Window win, bool switch_desktop);
  int close_window (Display * disp, Window win);
  Window *get_client_list (Display * disp, int *size);
  char *get_property (Display * disp, Window win,
		      Atom xa_prop_type, char *prop_name,
		      unsigned long *size);
  Window get_active_window (Display * disp);
  Window get_window_by_pid (Display * disp, unsigned long pid);
  int get_first_empty_desktop (Display * disp, long *desktop);

#ifdef __cplusplus
}
#endif				/* __cplusplus */

#endif				/* WMCTRL_H_INCLUDED */
