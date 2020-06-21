/**
 * @file linux_parser.h
 * @author Susanna Maria, David Silver
 * @brief Header of Linux Parser function
 * @version 1.0
 * @date 2020-06-21
 *
 * @copyright MIT License
 *
 */
#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>

namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

/**
 * CPU Stats
 *
 */
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};

/**
 * Process Stats
 *
 */
enum ProcessStates {
  pid = 0,
  comm,
  state,
  ppid,
  pgrp,
  session,
  tty_nr,
  tpgid,
  flags,
  minflt,
  cminflt,
  majflt,
  cmajflt,
  utime,
  stime,
  cutime,
  cstime,
  priority,
  nice,
  num_threads,
  itrealvalue,
  starttime,
  vsize,
  rss,
  rsslim,
  startcode,
  endcode,
  startstack,
  kstkesp,
  kstkeip,
  signal,
  blocked,
  sigignore,
  sigcatch,
  wchan,
  nswap,
  cnswap,
  exit_signal,
  processor,
  rt_priority,
  policy,
  delayacct_blkio_ticks,
  guest_time,
  cguest_time
};

std::vector<long> CpuUtilization();
std::string Command(int pid);
std::string Ram(int pid);
int Uid(int pid);
std::string User(int pid);
std::vector<std::string> PidStat(int pid);
void UserMap(std::unordered_map<int, std::string> &usermap);
};  // namespace LinuxParser

#endif