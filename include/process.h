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
  Process(int pid, long hz) : pid(pid), hz(hz), isnew(true), update(false){};
  int Pid() const;
  std::string User() const;
  std::string Command();
  float CpuUtilization() const;
  std::string Ram() const;
  long int UpTime() const;
  bool operator<(Process const& a) const;
  void Update(bool mode);
  bool Update() const;
  void CpuUtilization(float cpu_utilization);
  void IsNew(bool isnew);
  bool IsNew() const;
  void User(std::string uname);
  void UpTime(long utime);
  void DetRam();
  void PerformUpdate();

 private:
  std::string ram;
  int pid;
  long hz;
  bool isnew;
  bool update;
  std::string user;
  float cpu_utilization;
  long utime;
  std::string command;
};

#endif