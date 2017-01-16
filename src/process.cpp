#include "process.hpp"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <iostream>

process::process() :
  m_cwd(),
  m_exec(),
  m_args(),
  m_pid(-1)
{
}

process::~process()
{
  if(m_pid > 0)
    {
      ::kill(m_pid, SIGTERM);
      ::waitpid(m_pid, 0, 0);
    }
}

void process::chdir(std::string const &path)
{
  m_cwd = path;
}

void process::start(std::string const &exec, std::vector<std::string> const &args)
{
  if (m_pid == -1)
    {
      m_exec = exec;
      m_args = args;
      m_pid = fork();
      if (m_pid == -1)
	{
	  // Error
	  std::cerr << "Error on fork(): errno = " << ::strerror(errno) << std::endl;
	}
      else if (m_pid == 0)
	{
	  // child process

	  // set path
	  if (m_cwd.length() > 0)
	    {
	      int status;
	      status = ::chdir(m_cwd.c_str());
	    }

	  // exec
	  char * c_args[args.size() + 2] = { 0 };
	  int i;
	  c_args[0] = (char *)m_cwd.c_str(); // maybe replace this with just the filename without full path
	  for (i = 1; i < args.size(); ++i)
	    c_args[i] = (char *)args[i].c_str();
	  c_args[args.size()+1] = NULL;
	  
	  int status = ::execvp(m_cwd.c_str(), c_args);
          ::exit(EXIT_FAILURE);
	}
    }
}

pid_t process::pid(void)
{
  return m_pid;
}

void process::kill(void)
{
  if (m_pid > 0)
    ::kill(m_pid, SIGTERM);
}

