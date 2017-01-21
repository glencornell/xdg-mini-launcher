#pragma once

#include "directory_entry.hpp"
#include "ezxml.h"
#include "xdginfo.hpp"
#include <string>
#include <vector>

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
    std::vector<AbstractEntry *> m_children;
  };
}
