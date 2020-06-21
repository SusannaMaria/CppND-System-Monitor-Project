/**
 * @file process.h
 * @author Susanna Maria, David Silver
 * @brief header for process handling
 * @version 1.0
 * @date 2020-06-21
 *
 * @copyright MIT License
 *
 */
#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/**
 * Basic class for Process representation
 *
 */
class Process {
 public:
  Process(int pid) : pid(pid), isnew(true), update(false) {}
  int Pid() const;
  std::string User() const;                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram() const;                       // TODO: See src/process.cpp
  long int UpTime()const ;                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  void Update(bool mode);
  bool Update() const;
  void CpuUtilization(float cpu_utilization);
  void IsNew(bool isnew);
  bool IsNew() const;
  void User(std::string uname);
  void UpTime(long utime);
  void DetRam();

 private:
  std::string ram;
  int pid;
  bool isnew;
  bool update;
  std::string user;
  float cpu_utilization;
  long utime;
  std::string command;
};

#endif