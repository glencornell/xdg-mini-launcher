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


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include "wmctrl.h"

#define MAX_PROPERTY_VALUE_LEN 4096
#define MAX_DESKTOPS 1024

#ifdef DEBUG
#define p_verbose(...) fprintf(stderr, __VA_ARGS__)
#else
#define p_verbose(...) while(0)
#endif

int
client_msg (Display * disp, Window win, char *msg,
	    unsigned long data0, unsigned long data1,
	    unsigned long data2, unsigned long data3, unsigned long data4)
{
  XEvent event;
  long mask = SubstructureRedirectMask | SubstructureNotifyMask;

  event.xclient.type = ClientMessage;
  event.xclient.serial = 0;
  event.xclient.send_event = True;
  event.xclient.message_type = XInternAtom (disp, msg, False);
  event.xclient.window = win;
  event.xclient.format = 32;
  event.xclient.data.l[0] = data0;
  event.xclient.data.l[1] = data1;
  event.xclient.data.l[2] = data2;
  event.xclient.data.l[3] = data3;
  event.xclient.data.l[4] = data4;

  if (XSendEvent (disp, DefaultRootWindow (disp), False, mask, &event))
    {
      return EXIT_SUCCESS;
    }
  else
    {
      p_verbose ("Cannot send %s event.\n", msg);
      return EXIT_FAILURE;
    }
}

int
change_number_of_desktops (Display * disp, unsigned long n)
{
  return client_msg (disp, DefaultRootWindow (disp),
		     "_NET_NUMBER_OF_DESKTOPS", n, 0, 0, 0, 0);
}

int
get_number_of_desktops (Display * disp)
{
  int *number_of_desktops;
  int rval = 0;
  if ((number_of_desktops = (int *) get_property (disp, DefaultRootWindow (disp),
						  XA_CARDINAL,
						  "_NET_NUMBER_OF_DESKTOPS",
						  NULL)))
    {
      rval = *number_of_desktops;
      free(number_of_desktops);
    }
  return rval;
}

int
switch_desktop (Display * disp, unsigned long target)
{
  return client_msg (disp, DefaultRootWindow (disp), "_NET_CURRENT_DESKTOP",
		     target, 0, 0, 0, 0);
}

int
window_to_desktop (Display * disp, Window win, int desktop)
{
  unsigned long *cur_desktop = NULL;
  Window root = DefaultRootWindow (disp);

  if (desktop == -1)
    {
      if (!(cur_desktop = (unsigned long *) get_property (disp, root,
							  XA_CARDINAL,
							  "_NET_CURRENT_DESKTOP",
							  NULL)))
	{
	  if (!(cur_desktop = (unsigned long *) get_property (disp, root,
							      XA_CARDINAL,
							      "_WIN_WORKSPACE",
							      NULL)))
	    {
	      fputs ("Cannot get current desktop properties. "
		     "(_NET_CURRENT_DESKTOP or _WIN_WORKSPACE property)"
		     "\n", stderr);
	      return EXIT_FAILURE;
	    }
	}
      desktop = *cur_desktop;
    }
  free (cur_desktop);

  return client_msg (disp, win, "_NET_WM_DESKTOP", (unsigned long) desktop,
		     0, 0, 0, 0);
}

int
activate_window (Display * disp, Window win, bool switch_desktop)
{
  unsigned long *desktop;

  /* desktop ID */
  if ((desktop = (unsigned long *) get_property (disp, win,
						 XA_CARDINAL,
						 "_NET_WM_DESKTOP",
						 NULL)) == NULL)
    {
      if ((desktop = (unsigned long *) get_property (disp, win,
						     XA_CARDINAL,
						     "_WIN_WORKSPACE",
						     NULL)) == NULL)
	{
	  p_verbose ("Cannot find desktop ID of the window.\n");
	}
    }

  if (switch_desktop && desktop)
    {
      if (client_msg (disp, DefaultRootWindow (disp),
		      "_NET_CURRENT_DESKTOP",
		      *desktop, 0, 0, 0, 0) != EXIT_SUCCESS)
	{
	  p_verbose ("Cannot switch desktop.\n");
	}
      free (desktop);
    }

  client_msg (disp, win, "_NET_ACTIVE_WINDOW", 0, 0, 0, 0, 0);
  XMapRaised (disp, win);

  return EXIT_SUCCESS;
}

int
close_window (Display * disp, Window win)
{
  return client_msg (disp, win, "_NET_CLOSE_WINDOW", 0, 0, 0, 0, 0);
}

Window *
get_client_list (Display * disp, int *client_list_size)
{
  Window *client_list;
  unsigned long size = 0;

  if ((client_list = (Window *) get_property (disp, DefaultRootWindow (disp),
					      XA_WINDOW, "_NET_CLIENT_LIST",
					      &size)) == NULL)
    {
      if ((client_list =
	   (Window *) get_property (disp, DefaultRootWindow (disp),
				    XA_CARDINAL, "_WIN_CLIENT_LIST",
				    &size)) == NULL)
	{
	  p_verbose ("Cannot get client list properties. \n"
		     "(_NET_CLIENT_LIST or _WIN_CLIENT_LIST)" "\n");
	  return NULL;
	}
    }
  *client_list_size = size / sizeof(Window);

  return client_list;
}

char *
get_property (Display * disp, Window win,
	      Atom xa_prop_type, char *prop_name, unsigned long *size)
{
  Atom xa_prop_name;
  Atom xa_ret_type;
  int ret_format;
  unsigned long ret_nitems;
  unsigned long ret_bytes_after;
  unsigned long tmp_size;
  unsigned char *ret_prop;
  char *ret;

  xa_prop_name = XInternAtom (disp, prop_name, False);

  /* MAX_PROPERTY_VALUE_LEN / 4 explanation (XGetWindowProperty manpage):
   *
   * long_length = Specifies the length in 32-bit multiples of the
   *               data to be retrieved.
   *
   * NOTE:  see 
   * http://mail.gnome.org/archives/wm-spec-list/2003-March/msg00067.html
   * In particular:
   *
   *  When the X window system was ported to 64-bit architectures, a
   * rather peculiar design decision was made. 32-bit quantities such
   * as Window IDs, atoms, etc, were kept as longs in the client side
   * APIs, even when long was changed to 64 bits.
   *
   */
  if (XGetWindowProperty
      (disp, win, xa_prop_name, 0, MAX_PROPERTY_VALUE_LEN / 4, False,
       xa_prop_type, &xa_ret_type, &ret_format, &ret_nitems, &ret_bytes_after,
       &ret_prop) != Success)
    {
      p_verbose ("Cannot get %s property.\n", prop_name);
      return NULL;
    }

  if (xa_ret_type != xa_prop_type)
    {
      p_verbose ("Invalid type of %s property.\n", prop_name);
      XFree (ret_prop);
      return NULL;
    }

  /* null terminate the result to make string handling easier */
  tmp_size = (ret_format / 8) * ret_nitems;
  /* Correct 64 Architecture implementation of 32 bit data */
  if(ret_format==32) tmp_size *= sizeof(long)/4;
  ret = malloc (tmp_size + 1);
  memcpy (ret, ret_prop, tmp_size);
  ret[tmp_size] = '\0';

  if (size)
    {
      *size = tmp_size;
    }

  XFree (ret_prop);
  return ret;
}

Window
get_active_window (Display * disp)
{
  char *prop;
  unsigned long size;
  Window ret = (Window) 0;

  prop = get_property (disp, DefaultRootWindow (disp), XA_WINDOW,
		       "_NET_ACTIVE_WINDOW", &size);
  if (prop)
    {
      ret = *((Window *) prop);
      free (prop);
    }

  return (ret);
}

Window
get_window_by_pid (Display * disp, unsigned long pid)
{
  Window *client_list;
  int client_list_size;
  int i;
  Window rval = 0;
    
  if ((client_list = get_client_list(disp, &client_list_size)) == NULL) {
    return rval; 
  }

  for (i = 0; i < client_list_size; i++) {
    unsigned long *tmp_pid;
    
    /* pid */
    if ((tmp_pid = (unsigned long *)get_property(disp, client_list[i],
						 XA_CARDINAL, "_NET_WM_PID", NULL)))
      {
	if (*tmp_pid == pid)
	  {
	    rval = client_list[i];
	    free(tmp_pid);
	    break;
	  }
	free(tmp_pid);
      }
  }
  free(client_list);
  
  return rval;
}

int
get_first_empty_desktop (Display * disp, long * rval)
{
  Window *client_list;
  int client_list_size;
  int i;
  int windows_per_desktop[MAX_DESKTOPS] = { 0 };
  long desktop;
    
  if ((client_list = get_client_list(disp, &client_list_size)) == NULL) {
    return EXIT_FAILURE; 
  }
    
  for (i = 0; i < client_list_size; i++) {
    long *desktop_ptr;

    /* desktop ID */
    if ((desktop_ptr = (long *)get_property(disp, client_list[i],
						     XA_CARDINAL, "_NET_WM_DESKTOP", NULL)) == NULL) {
      if ((desktop_ptr = (long *)get_property(disp, client_list[i],
					      XA_CARDINAL, "_WIN_WORKSPACE", NULL)))
	{
	  if ((0 <= *desktop_ptr) && (*desktop_ptr < MAX_DESKTOPS))
	    windows_per_desktop[*desktop_ptr] = windows_per_desktop[*desktop_ptr] + 1;
	  free(desktop_ptr);
	}
    }
  }
  free(client_list);

  for (desktop = 0; desktop < MAX_DESKTOPS; desktop++)
    {
      if(windows_per_desktop[desktop] == 0)
	{
	  *rval = desktop;
	  return EXIT_SUCCESS;
	}
    }
   
  return EXIT_FAILURE;
}

