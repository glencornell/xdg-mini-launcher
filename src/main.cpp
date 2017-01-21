#include "x11info.hpp"
#include "menu_entry.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
  int rval = EXIT_SUCCESS;
  xdg::MenuEntry *m = xdg::MenuEntry::create("etc/xdg-mini-launcher.menu");
  x11info::init();

  return rval;
}
