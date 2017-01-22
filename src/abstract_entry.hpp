#pragma once

#include <string>

namespace xdg {

  // The base class for all xdg desktop entry files
  
  class AbstractEntry
  {
  public:
    enum type_t { Unknown, Application, Link, Directory };
    static type_t cvt(std::string const &str);
    static std::string cvt(type_t const t);

  public:
    virtual ~AbstractEntry();
    AbstractEntry(type_t t, 
		  std::string const &name,
		  std::string const &icon);

  private:
    // Options applicable to all desktop entries:
    type_t m_type;
    std::string m_name;
    std::string m_icon;

    AbstractEntry();
  };

}
