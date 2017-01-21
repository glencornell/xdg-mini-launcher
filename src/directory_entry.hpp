#pragma once

#include "abstract_entry.hpp"

namespace xdg {
  
  class DirectoryEntry : public AbstractEntry
  {
  public:
    DirectoryEntry(std::string const &name,
		   std::string const &icon);
    ~DirectoryEntry();

  private:
    DirectoryEntry();
  };

}
