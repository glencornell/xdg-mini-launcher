#include "x11info.hpp"
#include "menu_entry.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "dbg.h"

int main(int argc, char *argv[])
{
  int rval = EXIT_SUCCESS;
  std::string menu("xdg-mini-launcher.menu");
  xdg::MenuEntry *m = xdg::MenuEntry::create(menu);
  if (m)
    {
      x11info::init();
    }
  else
    {
      log_err("unable to load menu file \"%s\"", menu.c_str());
      rval = EXIT_FAILURE;
    }

  return rval;
}
