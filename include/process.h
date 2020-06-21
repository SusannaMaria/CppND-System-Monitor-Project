#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) : pid(pid), isnew(true), update(false) {}
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  void Update(bool mode);
  bool Update();
  void CpuUtilization(float cpu_utilization);
  void IsNew(bool isnew);
  bool IsNew();
  void User(std::string uname);
  void UpTime(long utime);
  void SetRam();
  // TODO: Declare any necessary private members
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