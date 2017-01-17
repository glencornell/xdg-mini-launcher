#pragma once

#include <sys/types.h>

class wmdesktop
{
public:
  static int get_first_empty_desktop(int *desktop);
  static int get_number_of_desktops();
  static void change_number_of_desktops(int size);
  static void switch_desktop(int desktop);
  static void activate_by_pid(pid_t pid);
};
