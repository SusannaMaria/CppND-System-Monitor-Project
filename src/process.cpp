#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "format.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid; }

void Process::User(string uname) { this->user = uname; }

bool Process::IsNew() { return isnew; }

void Process::IsNew(bool isnew) { this->isnew = isnew; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return this->cpu_utilization; }

// TODO: Return the command that generated this process
string Process::Command() {
  if (command.length() == 0) {
    this->command = LinuxParser::Command(this->pid);
  }
  return this->command;
}

// TODO: Return this process's memory utilization
string Process::Ram() { return this->ram; }

void Process::SetRam() { this->ram = LinuxParser::Ram(this->pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return this->user; }

bool Process::Update() { return this->update; }

void Process::Update(bool mode) { this->update = mode; }

void Process::CpuUtilization(float cpu_utilization) {
  this->cpu_utilization = cpu_utilization;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return utime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return (this->cpu_utilization > a.cpu_utilization);
}
void Process::UpTime(long utime) { this->utime = utime; }