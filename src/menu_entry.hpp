#pragma once

#include "directory_entry.hpp"
#include "ezxml.h"
#include <string>
#include <list>

namespace xdg
{
  class MenuEntry : public DirectoryEntry
  {
  public:
    static MenuEntry *create(std::string const &filename);
  private:
    static MenuEntry *create(ezxml_t node);
    MenuEntry(DirectoryEntry *dir);
    MenuEntry();
  private:
    std::string m_appdir;
    std::string m_directorydir;
    std::list<AbstractEntry *> m_children;
  };
}
