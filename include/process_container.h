/**
 * @file process_container.h
 * @author Susanna Maria
 * @brief Class to keep vector of Processes and thier logic to create and update
 * @version 0.1
 * @date 2020-06-21
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef PROCESS_CONTAINER_H
#define PROCESS_CONTAINER_H

#include <unordered_map>
#include <vector>

#include "process.h"

class ProcessContainer {
 public:
  ProcessContainer();
  Process* getProcess(int pid);
  std::vector<Process>& Processes();
  void UpdateProcesses();

 private:
  long hz;
  std::vector<Process> processes_ = {};
  std::unordered_map<int, std::string> users_;
};

#endif