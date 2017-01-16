#pragma once

#include <sys/types.h>
#include <stdlib.h>

namespace wmdesktop {

  int get_first_empty_desktop(int *desktop);
  int get_number_of_desktops();
  void change_number_of_desktops(int size);
  void switch_desktop(int desktop);
  void activate_by_pid(pid_t pid);
  
}
