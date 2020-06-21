/**
 * @file process.cpp
 * @author Susanna Maria, David Silver
 * @brief process handling impletionmenta
 * @version 1.0
 * @date 2020-06-21
 *
 * @copyright MIT License
 * 
 */
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

/**
 * Return this process's ID
 * 
 * @return int 
 */
int Process::Pid() const{ return this->pid; }

/**
 * @brief 
 * 
 * @param uname 
 */
void Process::User(string uname) { this->user = uname; }

/**
 * Return true if process is new registered 
 * 
 * @return true 
 * @return false 
 */
bool Process::IsNew() const { return this->isnew; }

/**
 * Set process as not new
 * 
 * @param isnew 
 */
void Process::IsNew(bool isnew) { this->isnew = isnew; }

/**
 * Return this process's CPU utilization
 * 
 * @return float 
 */
float Process::CpuUtilization() const{ return this->cpu_utilization; }

/**
 * Return the command that generated this process
 * 
 * @return string 
 */
string Process::Command(){
  if (command.length() == 0) {
    this->command = LinuxParser::Command(this->pid);
  }
  return this->command;
}

/**
 * Return this process's memory utilization
 * 
 * @return string 
 */
string Process::Ram() const { return this->ram; }

/**
 * Determine process's memory utilization
 * 
 */
void Process::DetRam() { this->ram = LinuxParser::Ram(this->pid); }

/**
 * Return the user(name) that generated this process
 * 
 * @return string 
 */
string Process::User() const { return this->user; }

/**
 * Process needs to be updated
 * 
 * @return true 
 * @return false 
 */
bool Process::Update() const { return this->update; }

/**
 * Set update state of process
 * 
 * @param mode 
 */
void Process::Update(bool mode) { this->update = mode; }

/**
 * Set cpu utilization of process
 * 
 * @param cpu_utilization 
 */
void Process::CpuUtilization(float cpu_utilization) {
  this->cpu_utilization = cpu_utilization;
}

/**
 * Return the age of this process (in seconds)
 * 
 * @return long int 
 */
long int Process::UpTime() const{ return utime; }

/**
 * Overload the "less than" comparison operator for Process objects
 * 
 * @param a Second Process which will be compared
 * @return true 
 * @return false 
 */
bool Process::operator<(Process const& a) const {
  return (this->cpu_utilization > a.cpu_utilization);
}

/**
 * Set uptime of process
 * 
 * @param utime 
 */
void Process::UpTime(long utime) { this->utime = utime; }