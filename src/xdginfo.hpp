#pragma once

#include <vector>
#include <string>

namespace xdg
{
  class xdginfo
  {
  public:
    xdginfo();
    // find the full path to the given desktop entry:
    std::string &find(std::string &full_path,       // return value
		      std::string const &subdir,    // "", "application", "directory", or "icon"
		      std::string const &file);     // name of the file
  private:
    static std::vector<std::string> m_xdg_data_dirs;
  };
}
