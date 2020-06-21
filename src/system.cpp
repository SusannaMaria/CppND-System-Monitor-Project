/**
 * @file system.cpp
 * @author Susanna Maria, David Silver
 * @brief system handling impletionments
 * @version 1.0
 * @date 2020-06-21
 *
 * @copyright MIT License
 *
 */
#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "process_container.h"
#include "processor.h"

using LinuxParser::ProcessStates;
using std::set;
using std::size_t;
using std::string;
using std::vector;

/**
 * Return the system's CPU
 *
 * @return Processor&
 */
Processor& System::Cpu() { return cpu_; }

/**
 * Return a container composed of the system's processes
 *
 * @return vector<Process>&
 */
vector<Process>& System::Processes() { return process_container_.Processes(); }

/**
 * Return the system's kernel identifier (string)
 *
 * @return std::string
 */
std::string System::Kernel() const { return LinuxParser::Kernel(); }

/**
 * Return the system's memory utilization
 *
 * @return float
 */
float System::MemoryUtilization() const {
  return LinuxParser::MemoryUtilization();
}

/**
 * Return the operating system name
 *
 * @return std::string
 */
std::string System::OperatingSystem() const {
  return LinuxParser::OperatingSystem();
}

/**
 * Return the number of processes actively running on the system
 *
 * @return int
 */
int System::RunningProcesses() const { return LinuxParser::RunningProcesses(); }

/**
 * Return the total number of processes on the system
 *
 * @return int
 */
int System::TotalProcesses() const { return LinuxParser::TotalProcesses(); }

/**
 * Return the number of seconds since the system started running
 *
 * @return long int
 */
long int System::UpTime() const { return LinuxParser::UpTime(); }
