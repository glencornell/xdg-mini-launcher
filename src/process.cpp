#include "process.hpp"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <iostream>
#include <map>

typedef std::map<pid_t, process *> pmap_t;

// This container indexed by pid stores all actively running
// processes:
static pmap_t *managed_processes = 0;

static void signal_handler(int sig, siginfo_t *si, void *context)
{
  switch(sig)
    {
    case SIGINT:
      std::cerr << "SIGINT: mypid = " << getpid() << ", mypgid = " << getpgid(getpid()) << std::endl;
      // we're about to terminate. kill all managed processes:
      for(pmap_t::iterator it = managed_processes->begin(); it != managed_processes->end(); ++it)
	{
	  it->second->kill();
	}
      ::exit(EXIT_FAILURE);
      break;
    case SIGCHLD:
      std::cerr << "SIGCHLD: mypid = " << getpid() << ", mypgid = " << getpgid(getpid()) << std::endl;
      // the child terminated or was killed, remove it from the
      // container of managed processes:
      if(si->si_code == CLD_EXITED ||
	 si->si_code == CLD_KILLED ||
	 si->si_code == CLD_DUMPED)
	{
	  std::cerr << "   Process terminated: " << si->si_pid;
	  pmap_t::iterator i = managed_processes->find(si->si_pid);
	  if (i != managed_processes->end())
	    {
	      std::cerr << " (" << i->second->name() << ")";
	      std::cerr << "       pid = " << i->second->pid() << std::endl;
	      managed_processes->erase(i);
	      i->second->wait();
	    }
	  std::cerr << std::endl;
	}
      break;
    }
}

process::process() :
  m_cwd(),
  m_exec(),
  m_args(),
  m_pid(-1)
{
}

process::process(const process &p) :
  m_cwd(),
  m_exec(),
  m_args(),
  m_pid(-1)
{
}

process &process::operator=(const process &p)
{
}

process::~process()
{
  kill();
}

void process::chdir(std::string const &path)
{
  m_cwd = path;
}

void process::exec(std::string const &exec, std::vector<std::string> const &args)
{
  if (m_pid == -1)
    {
      m_exec = exec;
      set_name();
      m_args = args;
      m_pid = fork();
      if (m_pid == -1)
	{
	  // Error
	  std::cerr << "ERROR : fork() = " << m_pid
		    << " errno = " << ::strerror(errno)
		    << "(" << errno << ")" << std::endl;
	  ::exit(EXIT_FAILURE);
	}
      else if (m_pid == 0)
	{
	  // child process

	  // set path
	  if (m_cwd.size() > 0)
	    {
	      int status;
	      status = ::chdir(m_cwd.c_str());
	      if (status != 0)
		std::cerr << "WARNING : chdir(\"" << m_cwd << "\") = " << status
			  << " errno = " << ::strerror(errno)
			  << "(" << errno << ")" << std::endl;
	    }

	  // exec
	  char * c_args[args.size() + 2] = { 0 };
	  int i;

	  c_args[0] = (char *)m_name.c_str();
	  
	  for (i = 1; i < args.size(); ++i)
	    c_args[i] = (char *)args[i].c_str();
	  c_args[args.size()+1] = NULL;

#if 0
	  {
	    // print execvp arguments
	    std::cerr << "INFO : execvp(\"" << m_exec << "\"";
	    for (i = 0; i < args.size(); ++i)
	      std::cerr << ", \"" << args[i] << "\"";
	    std::cerr << ")" << std::endl;
	  }
#endif
	  
	  int status = ::execvp(m_exec.c_str(), c_args);
          ::exit(EXIT_FAILURE);
	}
      else
	{
	  // parent
	  if (managed_processes == 0)
	    {
	      struct sigaction sVal;

	      managed_processes = new pmap_t;
	      // Specify that we will use a signal handler that takes
	      // three arguments instead of one, which is the default.
	      sVal.sa_flags = SA_SIGINFO;

	      // Indicate which function is the signal handler.
	      sVal.sa_sigaction = signal_handler;

	      // Register for SIGINT,SIGCHLD
	      sigaction(SIGINT, &sVal, NULL);
	      sigaction(SIGCHLD, &sVal, NULL);
	    }
	  std::cerr << "INFO : fork() = " << m_pid << std::endl;
	  (*managed_processes)[m_pid] = this;
	}
    }
}

pid_t process::pid(void)
{
  return m_pid;
}

void process::set_name(void)
{
  // extract just the file name of the program:
  std::string::size_type pos = m_exec.rfind('/');
  if (pos != std::string::npos)
    ++pos;
  else
    pos = 0;
  m_name = m_exec.substr(pos);
}

std::string const &process::name(void)
{
  return m_name;
}

void process::kill(void)
{
  if (m_pid > 0)
    ::kill(m_pid, SIGTERM);
}

void process::wait(void)
{
  if(m_pid > 0)
    {
      ::waitpid(m_pid, 0, 0);
      m_pid = -1;
    }
}
