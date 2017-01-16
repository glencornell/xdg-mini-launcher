#pragma once

#include "abstract_entry.hpp"
#include <map>
#include <string.h>

namespace xdg
{
  class DesktopEntryFactory
  {
  public:
    AbstractEntry *create(const char *file);
    
  private:
    static int ini_handler(void* user_data, const char* section, const char* name, const char* value);

  private:
    std::map<std::string, std::map<std::string, std::string > > entry_data;
  };
}
