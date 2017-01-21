#include "entry_factory.hpp"
#include "application_entry.hpp"
#include "directory_entry.hpp"
#include "ini.h"
#include <iostream>

using namespace xdg;

int DesktopEntryFactory::ini_handler(void* user_data,
				     const char* section,
				     const char* name,
				     const char* value)
{
  DesktopEntryFactory* f = (DesktopEntryFactory*)user_data;
  f->entry_data[section][name] = std::string(value);
  return 1;
}

DesktopEntryFactory::DesktopEntryFactory()
{
  //TODO: getenv("XDG_CONFIG_HOME")...
}

AbstractEntry *DesktopEntryFactory::create(const char *file)
{
  AbstractEntry * rval = NULL;

  if (::ini_parse(file, ini_handler, this) < 0)
    {
      std::cerr << "Unable to parse \"" << file << "\"" << std::endl;
    }
  else
    {
      std::string item = entry_data["Desktop Entry"]["Type"];
      if (item.size() != 0)
	{
	  AbstractEntry::type_t t = AbstractEntry::cvt(item);
	  switch(t)
	    {
	    case AbstractEntry::Application:
	      rval = new ApplicationEntry(entry_data["Desktop Entry"]["Name"],
					  entry_data["Desktop Entry"]["Icon"],
					  entry_data["Desktop Entry"]["Exec"],
					  entry_data["Desktop Entry"]["Path"],
					  ApplicationEntry::cvt(entry_data["Desktop Entry"]["Terminal"]));
	      break;
	    case AbstractEntry::Link:
	      std::cerr << "Desktop entries of Type=Link are not supported" << std::endl;
	      break;
	    case AbstractEntry::Directory:
	      rval = new DirectoryEntry(entry_data["Desktop Entry"]["Name"],
					entry_data["Desktop Entry"]["Icon"]);
	      break;
	    default:
	      std::cerr << "Desktop entries of Type=" << item << " are not supported" << std::endl;
	      break;
	    }
	}
    }
  entry_data.erase(entry_data.begin(), entry_data.end());
  return rval;
}

