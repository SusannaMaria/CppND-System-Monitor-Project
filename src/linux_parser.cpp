#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  float result;
  string type, unit;
  float value;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);

  std::map<std::string, float> mapMemCollection;

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> type >> value >> unit;
      type = type.substr(0, type.size() - 1);
      mapMemCollection[type] = value;
    }
  }
  // https://stackoverflow.com/questions/41224738/how-to-calculate-system-memory-usage-from-proc-meminfo-like-htop/41251290#41251290
  result = (mapMemCollection["MemTotal"] - mapMemCollection["MemFree"] -
            (mapMemCollection["Buffers"] + mapMemCollection["Cached"] +
             mapMemCollection["SReclaimable"] + mapMemCollection["Shmem"])) /
           mapMemCollection["MemTotal"];

  return result;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string suspend, idle;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> suspend >> idle;
  }
  return long(std::stof(suspend));
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<long> LinuxParser::CpuUtilization() {
  vector<long> result;

  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      if (line.rfind("cpu ", 0) == 0) {
        std::stringstream cpustream(line);
        std::istream_iterator<std::string> begin(cpustream);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        vstrings.erase(vstrings.begin());

        std::transform(vstrings.begin(), vstrings.end(),
                       std::back_inserter(result),
                       [](string s) -> long { return stol(s); });

        return result;
      }
    }
  }

  return result;
}
std::vector<std::string> split(const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  string type;
  int numprocesses;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      if (line.rfind("processes ", 0) == 0) {
        std::istringstream linestream(line);
        linestream >> type >> numprocesses;
        return numprocesses;
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  string type;
  int numprocesses;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      if (line.rfind("procs_running ", 0) == 0) {
        std::istringstream linestream(line);
        linestream >> type >> numprocesses;
        return numprocesses;
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid ) {

  std::string pidstatname =
      kProcDirectory + "/" + to_string(pid) + kCmdlineFilename;
  std::ifstream stream(pidstatname);
  string line;
  if (stream.is_open()) {
    std::getline(stream, line);
    return line;
  }
  return "";

 }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string key;
  string str_mem, str_unit;

  std::string pidstatusname =
      kProcDirectory + "/" + to_string(pid) + kStatusFilename;
  std::ifstream stream(pidstatusname);
  string line;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      if (!line.empty()){
      if (line.rfind("VmSize:", 0) == 0) {
        std::istringstream linestream(line);
        linestream >> key >> str_mem >> str_unit;
        if (str_unit=="kB"){
          str_mem = std::to_string(stol(str_mem)/1000);
        }
        
        return str_mem;
    }
    }
    }
  }
  return "";
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
int LinuxParser::Uid(int pid) {
  string key;
  string str_uid;

  std::string pidstatusname =
      kProcDirectory + "/" + to_string(pid) + kStatusFilename;
  std::ifstream stream(pidstatusname);
  string line;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      if (line.rfind("Uid:", 0) == 0) {
        std::istringstream linestream(line);
        linestream >> key >> str_uid;


        return stoi(str_uid);
      }
    }
  }
  return 0;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }

vector<string> LinuxParser::PidStat(int pid) {
  std::string pidstatname =
      kProcDirectory + "/" + to_string(pid) + kStatFilename;
  std::ifstream stream(pidstatname);
  string line;
  if (stream.is_open()) {
    std::getline(stream, line);
    std::stringstream cpustream(line);
    std::istream_iterator<std::string> begin(cpustream);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    return vstrings;
  }
  vector<string> result;
  return result;
}

void LinuxParser::UserMap(std::unordered_map<int, std::string>& usermap) {
  // susanna:x:1000:1000:Susanna,,,:/home/susanna:/bin/bash
  string line;
  string name;
  string notneeded;
  int uid;
  int gid;
  string realname;
  string homepath;
  string shell;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      auto linevec = split(line, ':');
      uid = stoi(linevec[2]);
      name = linevec[0];
      usermap[uid] = name;
       std::cout << uid << "|" << name << std::endl;
    }
  }
}