#pragma once

#include <sys/types.h>
#include <string>
#include <vector>

class process {
public:
  process();
  ~process();
  void chdir(std::string const &path);
  void start(std::string const &exec, std::vector<std::string> const &args);
  pid_t pid(void);
  void kill(void);
private:
  std::string m_cwd;
  std::string m_exec;
  std::vector<std::string> m_args;
  pid_t m_pid;
};
