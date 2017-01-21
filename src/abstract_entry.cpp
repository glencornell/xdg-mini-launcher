#include "abstract_entry.hpp"
#include "dbg.h"

using namespace xdg;

AbstractEntry::AbstractEntry(type_t t, 
			     std::string const &name,
			     std::string const &icon)
  : m_type(t),
    m_name(name),
    m_icon(icon)
{
  log_info("Type = \"%s\", Name = \"%s\", Icon = \"%s\"", cvt(m_type).c_str(), m_name.c_str(), m_icon.c_str());
}

AbstractEntry::~AbstractEntry()
{
}

AbstractEntry::AbstractEntry()
  : m_type(Unknown),
    m_name("UNDEFINED"),
    m_icon("UNDEFINED")
{
}

AbstractEntry::type_t AbstractEntry::cvt(std::string const &str)
{
  type_t rval = Unknown;
  if (str == "Application")
    rval = Application;
  else if (str == "Link")
    rval = Link;
  else if (str == "Directory")
    rval = Directory;
  return rval;
}

std::string AbstractEntry::cvt(AbstractEntry::type_t value)
{
  switch(value)
    {
    case Application:
      return "Application";
    case Link:
      return "Link";
    case Directory:
      return "Directory";
    }
  return "Unknown";
}
