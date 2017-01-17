#include "x11info.hpp"
#include "application_entry.hpp"
#include "entry_factory.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
  int rval = EXIT_SUCCESS;
  xdg::DesktopEntryFactory factory;
  xdg::ApplicationEntry *a = dynamic_cast<xdg::ApplicationEntry *>(factory.create("etc/xclock.desktop"));
  xdg::ApplicationEntry *b = dynamic_cast<xdg::ApplicationEntry *>(factory.create("etc/terminal.desktop"));
  x11info::init();

  if (a == 0 || b == 0)
    {
      std::cerr << "ERROR : unable to load desktop entry" << std::endl;
      return EXIT_FAILURE;
    }

  a->exec();
  b->exec();

  sleep(20);
  delete a;
  delete b;
  
  return rval;
}
