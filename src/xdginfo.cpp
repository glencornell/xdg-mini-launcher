#include "xdginfo.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <sstream>
#include "dbg.h"

using namespace xdg;

std::vector<std::string> xdginfo::m_xdg_data_dirs;

xdginfo::xdginfo()
{
  if (m_xdg_data_dirs.size() == 0)
    {
      const char *env = 0;
      if(env = ::getenv("XDG_DATA_HOME"))
	{
	  m_xdg_data_dirs.push_back(env);
	}
      else
	{
	  if(env = ::getenv("HOME"))
	    {
	      m_xdg_data_dirs.push_back(std::string(env) + "/.local/share");
	    }
	  else
	    {
	      struct passwd *info = ::getpwuid(::getuid());
	      if (info)
		{
		  m_xdg_data_dirs.push_back(std::string(info->pw_dir) + "/.local/share");
		}
	    }
	}
      if(env = ::getenv("XDG_DATA_DIRS"))
	{
	  std::istringstream xdg_data_dirs(env);
	  std::string s;
	  while (std::getline(xdg_data_dirs, s, ':'))
	    {
	      m_xdg_data_dirs.push_back(s);
	    }
	}
      m_xdg_data_dirs.push_back(".");
    }
}

std::string &xdginfo::find(std::string &full_path,
			   std::string const &subdir,
			   std::string const &file)
{
  full_path.erase();
  for(int i = 0; i != m_xdg_data_dirs.size(); ++i)
    {
      std::string sub(subdir.size() ? std::string("/") + subdir + "/" : "/");
      std::string path(m_xdg_data_dirs[i] + sub + file);
      struct stat buf = { 0 };
      if(::stat(path.c_str(),&buf) == 0)
	{
	  if (S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode))
	    {
	      full_path = path;
	      break;
	    }
	}
    }
  return full_path;
}

