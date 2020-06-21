/**
 * @file process_container.cpp
 * @author Susanna Maria
 * @brief Implementation of Class which contains the logic to create and update
 * the vector of processes
 * @version 0.1
 * @date 2020-06-21
 *
 * @copyright MIT License
 *
 */
#include "process_container.h"

#include <unistd.h>

#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
using LinuxParser::ProcessStates;
using std::set;
using std::size_t;
using std::string;
using std::vector;

ProcessContainer::ProcessContainer() {
  this->hz = sysconf(_SC_CLK_TCK);
  LinuxParser::UserMap(users_);
}

/**
 * Return a container composed of the system's processes
 *
 * @return vector<Process>&
 */
vector<Process>& ProcessContainer::Processes() {
  // We want to update the vector of processes everytime it is requested
  UpdateProcesses();
  return processes_;
}

void ProcessContainer::UpdateProcesses() {
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
    prc->PerformUpdate();
  }

  sort(processes_.begin(), processes_.end());
}

/**
 * Get process by pid
 *
 * This is an update function of an vector of processes
 * implemented to reduce cpu load of monitor
 *
 * @param pid
 * @return Process*
 */
Process* ProcessContainer::getProcess(int pid) {
  for (unsigned i = 0; i < processes_.size(); i++) {
    if (processes_[i].Pid() == pid) {
      processes_[i].Update(true);
      processes_[i].IsNew(false);
      Process* ptr = &processes_[i];
      return ptr;
    }
  }
  Process newelement = Process(pid, hz);
  LinuxParser::Uid(pid);
  const int uid = LinuxParser::Uid(pid);
  auto uptr = users_.find(uid);
  string uname = uptr->second;
  newelement.User(uname);
  processes_.push_back(newelement);
  return &processes_.back();
}