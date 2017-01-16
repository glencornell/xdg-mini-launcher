#include "wmdesktop.hpp"
#include "wmctrl.h"
#include "x11info.hpp"

int wmdesktop::get_first_empty_desktop(int *desktop)
{
  int rval = -1;
  long num_desktops = 0;
  
  rval = ::get_first_empty_desktop(x11info::display(), &num_desktops);
  *desktop = (int)num_desktops;
  return rval;
}

int wmdesktop::get_number_of_desktops()
{
  return ::get_number_of_desktops(x11info::display());
}

void wmdesktop::change_number_of_desktops(int size)
{
  int status;
  status = ::change_number_of_desktops (x11info::display(), (unsigned long)size);
}

void wmdesktop::switch_desktop(int desktop)
{
  ::switch_desktop (x11info::display(), (unsigned long)desktop);
}

void wmdesktop::activate_by_pid(pid_t pid)
{
  Window window;
  if((window = ::get_window_by_pid(x11info::display(), pid)))
    {
      activate_window(x11info::display(), window, true);
    }
}
