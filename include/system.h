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
#include <vector>

#include "process.h"
#include "process_container.h"
#include "processor.h"

class System {
 public:
  Processor& Cpu();
  std::vector<Process>& Processes();
  float MemoryUtilization() const;
  long UpTime() const;
  int TotalProcesses() const;
  int RunningProcesses() const;
  std::string Kernel() const;
  std::string OperatingSystem() const;

 private:
  Processor cpu_ = {};
  ProcessContainer process_container_;
};

#endif