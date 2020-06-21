/**
 * @file system.h
 * @author Susanna Maria, David Silver
 * @brief Class definiiton of System object
 * @version 1.0
 * @date 2020-06-21
 *
 * @copyright MIT License
 *
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <unordered_map>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  System();
  Processor& Cpu();
  std::vector<Process>& Processes();
  float MemoryUtilization() const;
  long UpTime() const;
  int TotalProcesses() const;
  int RunningProcesses() const;
  std::string Kernel() const;
  std::string OperatingSystem() const;

  Process* getProcess(int pid);

 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::unordered_map<int, std::string> users_;
  long hz;
};

#endif