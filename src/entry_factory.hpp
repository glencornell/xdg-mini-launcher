#pragma once

#include "abstract_entry.hpp"
#include <map>
#include <string.h>

namespace xdg
{
  class DesktopEntryFactory
  {
  public:
    DesktopEntryFactory();
    AbstractEntry *create(std::string const &file);

  private:
    static int ini_handler(void* user_data, const char* section, const char* name, const char* value);

  private:
    // data structure for containing parsed name/value pairs
    std::map<std::string, std::map<std::string, std::string > > entry_data;
  };
}
