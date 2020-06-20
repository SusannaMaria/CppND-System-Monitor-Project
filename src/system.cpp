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

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

Process* System::getProcess(int pid) {
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
  newelement.User(uname.substr(0, 6));
  processes_.push_back(newelement);
  return &processes_.back();
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  long hz = sysconf(_SC_CLK_TCK);

  auto pids_ = LinuxParser::Pids();

  for (unsigned i = 0; i < processes_.size(); i++) {
    processes_[i].Update(false);
  }

  for (auto i : pids_) {
    auto prc = getProcess(i);
    prc->Update(true);
  }

  for (auto it = processes_.begin(); it != processes_.end();) {
    if (!it->Update())
      it = processes_.erase(it);
    else
      ++it;
  }  


  for (auto i : pids_) {
    auto prc = getProcess(i);
    auto stat = LinuxParser::PidStat(i);
    long total_time =
        stol(stat[ProcessStates::utime]) + stol(stat[ProcessStates::stime]);

    long utime_sec = stol(stat[ProcessStates::utime]) / hz;

    prc->UpTime(utime_sec);
    prc->SetRam();
    long uptime = LinuxParser::UpTime();

    long used_time = uptime - (stol(stat[ProcessStates::starttime]) / hz);

    if (used_time <= 0) {
      prc->CpuUtilization(0.0);
    } else {
      float cpu_utilization = ((float)total_time / (float)(used_time * hz));
      prc->Update(true);
      prc->CpuUtilization(cpu_utilization);
    }
  }



  sort(processes_.begin(), processes_.end());
  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }

System::System() {
  LinuxParser::UserMap(users_);

  std::cout << "dkfsj" << std::endl;
}