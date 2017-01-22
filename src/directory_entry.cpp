#include "directory_entry.hpp"

using namespace xdg;

DirectoryEntry::DirectoryEntry(std::string const &name,
			       std::string const &icon)
  : AbstractEntry(Directory, name, icon)
{
}

DirectoryEntry::DirectoryEntry()
  : AbstractEntry(Unknown, "", "")
{
}

DirectoryEntry::~DirectoryEntry()
{
}
