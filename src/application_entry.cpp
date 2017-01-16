#include "application_entry.hpp"
#include "wmdesktop.hpp"

using namespace xdg;

bool ApplicationEntry::cvt(std::string const &str)
{
  bool rval = false;
  if (str == "true")
    rval = true;
  else if (str == "false")
    rval = false;
  return rval;
}

std::string ApplicationEntry::cvt(bool value)
{
  std::string rval;
  if(value)
    rval = "true";
  else  
    rval = "false";
  return rval;
}

ApplicationEntry::ApplicationEntry(std::string const &name,
				   std::string const &icon,
				   std::string const &exec,
				   std::string const &path,
				   bool terminal)
  : AbstractEntry(Application, name, icon),
    m_process(0),
    m_exec(exec),
    m_path(path),
    m_terminal(terminal)
{
}

ApplicationEntry::~ApplicationEntry()
{
  this->kill();
}

void ApplicationEntry::exec()
{
  std::vector<std::string> arguments;
  int desktop;
  
  if(!m_process)
    {
      // if a desktop has no windows, switch to it.  Otherwise, create
      // a new desktop and switch to it.  In either case, the
      // application is intended to run in it's own workspace.
      if(wmdesktop::get_first_empty_desktop(&desktop) != EXIT_SUCCESS)
	{
	  desktop = wmdesktop::get_number_of_desktops();
	  wmdesktop::change_number_of_desktops(desktop + 1);
	}
      wmdesktop::switch_desktop((unsigned long)desktop);

      // Create a new process
      m_process = new ::process();
      m_process->chdir(m_path);
      m_process->start(m_exec, arguments);
    }
}

void ApplicationEntry::switch_to()
{
  if(m_process)
    {
      wmdesktop::activate_by_pid(m_process->pid());
    }
}

void ApplicationEntry::exec_or_switch_to() {
  exec();
  switch_to();
}

void ApplicationEntry::kill() {
  if(m_process) {
    m_process->kill();
    delete m_process;
  }
  m_process = 0;
}
