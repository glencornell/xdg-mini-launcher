#include "x11info.hpp"
#include "application_entry.hpp"
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int rval = EXIT_SUCCESS;
  xdg::ApplicationEntry *a = new xdg::ApplicationEntry
    ("My App", //name
     "boat.png", //icon
     "/usr/bin/gnome-terminal", //exec
     ".", //path
     false
     );
  x11info::init();

  a->exec();

  //  delete a;
  
  return rval;
}
