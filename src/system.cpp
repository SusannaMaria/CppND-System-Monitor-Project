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
#include "processor.h"

using LinuxParser::ProcessStates;
using std::set;
using std::size_t;
using std::string;
using std::vector;
#include <unistd.h>

/**
 * Constructor
 *
 */
System::System() { LinuxParser::UserMap(users_); }

/**
 * Return the system's CPU
 *
 * @return Processor&
 */
Processor& System::Cpu() { return cpu_; }

/**
 * Get process by pid
 *
 * This is an update function of an vector of processes
 * implemented to reduce cpu load of monitor
 *
 * @param pid
 * @return Process*
 */
Process* System::getProcess(int pid){
  for (unsigned i = 0; i < processes_.size(); i++) {
    if (processes_[i].Pid() == pid) {
      processes_[i].Update(true);
      processes_[i].IsNew(false);
      Process* ptr = &processes_[i];
      return ptr;
    }
  }
  Process newelement = Process(pid);
  LinuxParser::Uid(pid);
  const int uid = LinuxParser::Uid(pid);
  auto uptr = users_.find(uid);
  string uname = uptr->second;
  newelement.User(uname);
  processes_.push_back(newelement);
  return &processes_.back();
}

/**
 * Return a container composed of the system's processes
 *
 * @return vector<Process>&
 */
vector<Process>& System::Processes() {
  long hz = sysconf(_SC_CLK_TCK);

  // get new list of current processes
  auto pids_ = LinuxParser::Pids();

  // Set update state of all processes to false
  for (unsigned i = 0; i < processes_.size(); i++) {
    processes_[i].Update(false);
  }

  // Update the current processes
  for (auto i : pids_) {
    // Get a new process object or an already existing object
    auto prc = getProcess(i);
    // Set update state to true
    prc->Update(true);
  }

  // Remove processes from vector which are gone
  for (auto it = processes_.begin(); it != processes_.end();) {
    if (!it->Update())
      it = processes_.erase(it);
    else
      ++it;
  }

  // Now update the remaining processes (fill the information on central place)
  for (auto i : pids_) {
    auto prc = getProcess(i);

    auto stat = LinuxParser::PidStat(i);
    long total_time =
        stol(stat[ProcessStates::utime]) + stol(stat[ProcessStates::stime]);

    long utime_sec = stol(stat[ProcessStates::utime]) / hz;

    prc->UpTime(utime_sec);
    prc->DetRam();
    long uptime = LinuxParser::UpTime();

    long used_time = uptime - (stol(stat[ProcessStates::starttime]) / hz);

    if (used_time <= 0) {
      prc->CpuUtilization(0.0);
    } else {
      float cpu_utilization = ((float)total_time / (float)(used_time * hz));
      prc->CpuUtilization(cpu_utilization);
    }
  }

  sort(processes_.begin(), processes_.end());
  return processes_;
}

/**
 * Return the system's kernel identifier (string)
 *
 * @return std::string
 */
std::string System::Kernel() const{ return LinuxParser::Kernel(); }

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
