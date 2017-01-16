#pragma once

#include "abstract_entry.hpp"
#include "process.hpp"

namespace xdg {
  
  class ApplicationEntry : public AbstractEntry
  {
  public:
    static bool cvt(std::string const &str);
    static std::string cvt(bool value);
    ApplicationEntry(std::string const &name,
		     std::string const &icon,
		     std::string const &exec,
		     std::string const &path,
		     bool terminal);
    ~ApplicationEntry();

  public:
    void exec(void);
    void switch_to(void);
    void exec_or_switch_to(void);
    void kill(void);

  private:
    process *m_process;
    
    // fields derived from the desktop entry file:
    std::string m_exec;
    std::string m_path;
    bool m_terminal;

  };

}
